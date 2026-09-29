//---------------------------------------------------------------------------
#include "ws_actions.h"
#include "ws_paths.h"

#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>
//---------------------------------------------------------------------------
static std::string ws_getenv( const char *name )
{
  const char *v = getenv(name);
  return (v == NULL) ? std::string() : std::string(v);
}
//---------------------------------------------------------------------------
static bool ws_file_exists( const std::string &path )
{
  struct stat st;
  return (! path.empty()) && (stat( path.c_str(), &st ) == 0);
}
//---------------------------------------------------------------------------
//TQString::simplifyWhiteSpace()
static std::string ws_simplify( const std::string &s )
{
  std::istringstream iss( s );
  std::string word, out;
  while( iss >> word ) {
    if( ! out.empty() ) out += ' ';
    out += word;
  }
  return out;
}
//---------------------------------------------------------------------------
static std::string ws_cmd_out( const std::string &cmd )
{
  std::string out;
  FILE *pipe1 = popen( cmd.c_str(), "r" );
  if( pipe1 == NULL ) return out;
  char buf[1024];
  size_t nread;
  while( (nread = fread(buf, 1, sizeof(buf), pipe1)) > 0 ) out.append(buf, nread);
  pclose(pipe1);
  return out;
}
//---------------------------------------------------------------------------
static bool ws_contains( const std::string &s, const char *what )
{
  return s.find(what) != std::string::npos;
}
//---------------------------------------------------------------------------
//a command put in the background, without waiting (system() with a trailing "&")
static void ws_background( const std::string &cmd )
{
  system( (cmd + " &").c_str() );
}
//---------------------------------------------------------------------------
WsSystem ws_probe()
{
  WsSystem sys;
  sys.is_quarkos = ws_file_exists("/var/lib/q4os/isquarkos.stp");
  sys.session = ws_getenv("QDSK_SESSION");
  sys.qaptdistr = ws_getenv("QAPTDISTR");

  const std::string bg = std::string(WS_SHARE_DIR) + (sys.is_quarkos ? "background2.png" : "background1.png");
  sys.background = ws_file_exists(bg) ? bg : "";

  sys.hwinfo_cmd = "";
  if( (sys.session == "plasma") && ws_file_exists("/usr/bin/cpuqinfo5.exu") ) sys.hwinfo_cmd = "/usr/bin/cpuqinfo5.exu";
  if( (sys.session == "trinity") && ws_file_exists("/usr/bin/cpuqinfo.exu") ) sys.hwinfo_cmd = "/usr/bin/cpuqinfo.exu";
  //swap button "switch start menu" to "hardware info" for plasma desktop
  sys.swap_button4 = (sys.session == "plasma") && (sys.hwinfo_cmd.length() > 1);

  struct sysinfo info;
  sysinfo( &info );
  sys.phmemsize = (long long int)((size_t)info.totalram * (size_t)info.mem_unit);

  sys.dpkg_arch = ws_simplify( ws_cmd_out("dpkg --print-architecture") );
  if( sys.dpkg_arch.length() < 1 ) sys.dpkg_arch = "unknown";
  ws_debug("architecture: " + sys.dpkg_arch);
  return sys;
}
//---------------------------------------------------------------------------
std::string ws_edition_name( const std::string &text, const WsSystem &sys )
{
  if( ! sys.is_quarkos ) return text;
  std::string out = text;
  size_t pos = 0;
  while( (pos = out.find("Q4OS", pos)) != std::string::npos ) {
    out.replace( pos, 4, "Quarkos" );
    pos += 7;
  }
  return out;
}
//---------------------------------------------------------------------------
void ws_run_swcentre()
{
  //through q4os-swcentre-common's session-aware launcher (the Trinity or the Qt frontend)
  FILE *hlpfl1 = popen( WS_SWCENTRE_CMD " &", "w" ); if( hlpfl1 ) pclose(hlpfl1);
}
//---------------------------------------------------------------------------
void ws_run_profiler()
{
  FILE *hlpfl1 = popen( WS_PROFILER_CMD, "w" ); if( hlpfl1 ) pclose(hlpfl1);
}
//---------------------------------------------------------------------------
void ws_install_codecs()
{
  const std::string codecs_setup_file = "q4os-ipcodecs";
  system( ("dash " WS_SCRIPTS_DIR "dwnld_instl.sh \"" + codecs_setup_file + "\" \"Multimedia Codecs\" \"Multimedia Codecs\" \"package_settings\" \"\" \"\" \"\" \"\" \"1\" &").c_str() );
}
//---------------------------------------------------------------------------
bool ws_screen_scaling( const WsSystem &sys )
{
  std::string commnd1;
  if( (sys.session == "trinity") && ws_file_exists("/opt/trinity/bin/screenscalerp.exu") ) {
    commnd1 = "screenscalerp.exu";
  } else if( (sys.session == "plasma") && ws_file_exists("/usr/bin/kcmshell6") ) {
    commnd1 = "/usr/bin/kcmshell6";
  } else if( (sys.session == "plasma") && ws_file_exists("/usr/bin/kcmshell5") ) {
    commnd1 = "/usr/bin/kcmshell5";
  } else {
    return false;
  }
  if( commnd1 == "screenscalerp.exu" ) {
    system( commnd1.c_str() );
    return true;
  }
  //kcmshell keeps running after its window closed once the scale was changed, so waiting for its
  //exit would keep the Welcome window hidden for good; wait 30 s at most, as the Qt frontend's
  //QProcess::waitForFinished() did before the split, and leave kcmshell running on its own
  const pid_t pid = fork();
  if( pid == 0 ) {
    execl( commnd1.c_str(), commnd1.c_str(), "kcm_kscreen", (char *)NULL );
    _exit(127);
  }
  if( pid < 0 ) return true;
  for( int ix = 0; ix < 300; ++ix ) {
    if( waitpid( pid, NULL, WNOHANG ) != 0 ) return true; //exited (or not our child any more)
    usleep(100000);
  }
  return true;
}
//---------------------------------------------------------------------------
void ws_hw_info( const WsSystem &sys )
{
  if( sys.hwinfo_cmd.empty() ) return;
  ws_background( sys.hwinfo_cmd );
}
//---------------------------------------------------------------------------
void ws_autologin( bool enable, const WsSystem &sys )
{
  if( enable ) {
    if( sys.session == "trinity" )
      system("tdesudo --comment \"Please enter your password for verification:\" -d --noignorebutton \"ctrl-autologin --enable\"");
    if( sys.session == "plasma" )
      system("tdesudo --comment \"Please enter your password for verification:\" -d --noignorebutton \"ctrl-autologin --enable\" \"\" \"\" \"plasma.desktop\"");
  } else {
    system("tdesudo --comment \"Please enter your password for verification:\" -d --noignorebutton \"ctrl-autologin --disable\"");
  }
}
//---------------------------------------------------------------------------
bool ws_sudo_ok()
{
  return system("sudo -n echo") == 0;
}
//---------------------------------------------------------------------------
int ws_effects_kind( const WsSystem &sys )
{
  if( (sys.session == "plasma") && (ws_file_exists("/usr/bin/kcmshell6") || ws_file_exists("/usr/bin/kcmshell5")) ) return ws_effects_plasma;
  if( sys.session == "trinity" ) return ws_effects_trinity;
  return ws_effects_none;
}
//---------------------------------------------------------------------------
bool ws_effects_hw_ok( const WsSystem &sys )
{
  return sys.phmemsize >= 1700000000LL;
}
//---------------------------------------------------------------------------
void ws_effects_plasma_kcm()
{
  if( ws_file_exists("/usr/bin/kcmshell6") ) system( "kcmshell6 kcmkwineffects" );
  else system( "kcmshell5 kcmkwineffects" );
}
//---------------------------------------------------------------------------
void ws_effects_enable()
{
  FILE *hlpfl1 = popen( "ctrl-compmgr --enable --no-relogin", "r" ); if( hlpfl1 ) pclose(hlpfl1);
}
//---------------------------------------------------------------------------
void ws_effects_disable()
{
  FILE *hlpfl1 = popen( "ctrl-compmgr --disable", "r" ); if( hlpfl1 ) pclose(hlpfl1);
}
//---------------------------------------------------------------------------
void ws_startmenu_apply( int structure, int type )
{
  if( structure == ws_menu_structure_q4os ) system("dash " WS_SCRIPTS_DIR "kmenu_struct.sh --q4os --no-agui");
  if( structure == ws_menu_structure_tde ) system("dash " WS_SCRIPTS_DIR "kmenu_struct.sh --tde --no-agui");
  if( type == ws_menu_type_kickoff ) system("ctrl-kmenu --kickoff");
  if( type == ws_menu_type_bourbon ) system("ctrl-kmenu --bourbon");
  if( type == ws_menu_type_classic ) system("ctrl-kmenu --classic");
  usleep(400000);
}
//---------------------------------------------------------------------------
void ws_open_docs()
{
  //the browser command is looked up without the session's konqueror preference: xdg-open/browser
  WsSystem nosess;
  ws_background( ws_default_browser(nosess) + " \"https://www.q4os.org/documents.html\"" );
}
//---------------------------------------------------------------------------
void ws_open_donate()
{
  WsSystem nosess;
  ws_background( ws_default_browser(nosess) + " \"https://www.q4os.org/dnt_donate.html\"" );
}
//---------------------------------------------------------------------------
void ws_open_patreon( const WsSystem &sys )
{
  const std::string patreon_page = "https://www.patreon.com/join/q4os";
  const std::string browser = ws_default_browser(sys);
  if( (sys.session == "trinity") && (browser == "kfmclient openURL") ) {
    ws_background( browser + " \"https://www.q4os.org/dnt_donate.html\"" ); //konqueror fails to open patreon page
  } else {
    ws_background( browser + " \"" + patreon_page + "\"" );
  }
}
//---------------------------------------------------------------------------
//todo: move this function to q4os-api
std::string ws_default_browser( const WsSystem &sys )
{
  //using command "xdg-settings get default-web-browser"
  const std::string browsercmd = ws_simplify( ws_cmd_out("xdg-settings get default-web-browser") );
  ws_debug("browsercmd: " + browsercmd);

  if( ws_contains(browsercmd, "firefox-esr") ) return "xdg-open"; //firefox-esr.desktop
  if( ws_contains(browsercmd, "firefox") ) return "xdg-open";
  if( ws_contains(browsercmd, "chromium") ) return "xdg-open";
  if( ws_contains(browsercmd, "google-chrome") ) return "xdg-open";
  if( ws_contains(browsercmd, "palemoon") ) return "xdg-open";

  //try to search for browser binary
  if( ws_file_exists("/usr/bin/firefox") ) return "/usr/bin/firefox";
  if( ws_file_exists("/usr/bin/firefox-esr") ) return "/usr/bin/firefox-esr";
  if( ws_file_exists("/usr/bin/chromium") ) return "/usr/bin/chromium";
  if( ws_file_exists("/usr/bin/google-chrome-stable") ) return "/usr/bin/google-chrome-stable";
  if( ws_file_exists("/usr/bin/palemoon") ) return "/usr/bin/palemoon";

  if( sys.session == "trinity" ) {
    if( ws_contains(browsercmd, "konqueror") ) return "kfmclient openURL";
    if( browsercmd.length() < 1 ) return "kfmclient openURL";
  }

  return "xdg-open";
}
//---------------------------------------------------------------------------
//a known browser binary, Konqueror under Trinity, or any application registered for https links;
//a Basic Plasma has none of them, and xdg-open then hands the page to the text/html handler - Kate,
//which showed the donation page's HTML source (a87 QA)
bool ws_browser_available( const WsSystem &sys )
{
  if( ws_default_browser(sys) != "xdg-open" ) return true;
  return ! ws_simplify( ws_cmd_out("xdg-mime query default x-scheme-handler/https 2>/dev/null") ).empty();
}
//---------------------------------------------------------------------------
void ws_remove_autostart()
{
  ws_debug("removing from autostart");
  std::string xdgcfgh = ws_getenv("XDG_CONFIG_HOME");
  if( xdgcfgh.length() < 1 ) xdgcfgh = ws_getenv("HOME") + "/.config";
  FILE *hlpfl1;
  hlpfl1 = popen( ("rm -f " + xdgcfgh + "/autostart/q4os-welcome-screen.desktop").c_str(), "r" ); if( hlpfl1 ) pclose(hlpfl1);
  hlpfl1 = popen( ("rm -f " + xdgcfgh + "/autostart/q4os-welcome-screen5.desktop").c_str(), "r" ); if( hlpfl1 ) pclose(hlpfl1);
}
//---------------------------------------------------------------------------
bool ws_debug_on()
{
  return ws_getenv("Q4_WELCOMESCREEN_DEBUG") == "1";
}
//---------------------------------------------------------------------------
void ws_debug( const std::string &text )
{
  if( ws_debug_on() ) fprintf( stderr, "%s\n", text.c_str() );
}
//---------------------------------------------------------------------------
