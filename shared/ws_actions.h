//---------------------------------------------------------------------------
#ifndef WS_ACTIONS_H
#define WS_ACTIONS_H
//---------------------------------------------------------------------------
//everything the Welcome screen does apart from showing it, toolkit-free, shared by the Trinity and
//the Qt frontend: what the system is (session, edition, hardware), and the actions behind the
//buttons and the menu - all of them shell commands the frontends used to carry twice
#include <string>
//---------------------------------------------------------------------------
//what the window needs to know about this system, probed once at startup
struct WsSystem
{
  std::string session; //QDSK_SESSION: "trinity", "plasma", ...
  std::string qaptdistr; //QAPTDISTR
  std::string dpkg_arch; //"amd64", ... "unknown"
  bool is_quarkos = false; //the Quark edition (its own name and background)
  std::string background; //the header image to show, "" when none is installed
  std::string hwinfo_cmd; //the hardware info tool of this session, "" when none is installed
  bool swap_button4 = false; //Plasma: the "Switch start menu" button becomes "Hardware info"
  long long int phmemsize = 0;
};
WsSystem ws_probe();
//"Q4OS" -> "Quarkos" in a shown text when this is the Quark edition
std::string ws_edition_name( const std::string &text, const WsSystem &sys );
//---------------------------------------------------------------------------
//--- the buttons ---
void ws_run_swcentre(); //Install Applications (background)
void ws_run_profiler(); //Run Desktop Profiler, through q4os-sw-profiler-common's launcher; BLOCKS until it ends
void ws_install_codecs(); //Install Proprietary Codecs (background)
//Screen scaling: the session's tool, run to its end (the caller hides the window meanwhile);
//false when no tool is installed
bool ws_screen_scaling( const WsSystem &sys );
void ws_hw_info( const WsSystem &sys ); //background
//---------------------------------------------------------------------------
//--- automatic login (asks for the password itself: tdesudo in Trinity, polkit elsewhere) ---
bool ws_autologin( bool enable, const WsSystem &sys ); //true: the password was given and the change made
bool ws_sudo_ok(); //the password was given to tdesudo: sudo works without asking now
//---------------------------------------------------------------------------
//--- desktop effects ---
enum { ws_effects_none = 0, ws_effects_trinity = 1, ws_effects_plasma = 2 };
int ws_effects_kind( const WsSystem &sys ); //what this session offers
bool ws_effects_hw_ok( const WsSystem &sys ); //enough memory for them
void ws_effects_plasma_kcm(); //Plasma: the KWin effects module, run to its end
void ws_effects_enable(); //Trinity
void ws_effects_disable(); //Trinity
//---------------------------------------------------------------------------
//--- start menu (Trinity) ---
enum { ws_menu_structure_keep = 0, ws_menu_structure_q4os = 1, ws_menu_structure_tde = 2 };
enum { ws_menu_type_keep = 0, ws_menu_type_kickoff = 1, ws_menu_type_bourbon = 2, ws_menu_type_classic = 3 };
void ws_startmenu_apply( int structure, int type );
//---------------------------------------------------------------------------
//--- the web links ---
void ws_open_docs();
void ws_open_donate();
void ws_open_patreon( const WsSystem &sys );
std::string ws_default_browser( const WsSystem &sys ); //the command that opens a URL
bool ws_browser_available( const WsSystem &sys ); //false: a URL would open in whatever else takes text/html (Kate)
//---------------------------------------------------------------------------
//--- misc ---
void ws_remove_autostart(); //"Show this dialog on startup" unchecked: both frontends' autostart entries
bool ws_debug_on(); //Q4_WELCOMESCREEN_DEBUG=1
void ws_debug( const std::string &text );
//---------------------------------------------------------------------------
#endif // WS_ACTIONS_H
//---------------------------------------------------------------------------
