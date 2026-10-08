//---------------------------------------------------------------------------
#include "ws_flows.h"
#include "ws_strings.h"
//---------------------------------------------------------------------------
void ws_flow_run_profiler( WsDialogs &d )
{
  d.hide_main();
  ws_run_profiler();
  d.show_main();
}
//---------------------------------------------------------------------------
void ws_flow_desktop_effects( WsDialogs &d, const WsSystem &sys )
{
  const int kind = ws_effects_kind(sys);
  if( kind == ws_effects_plasma ) {
    d.hide_main();
    ws_effects_plasma_kcm();
  } else if( kind == ws_effects_trinity ) {
    int res1;
    if( ws_effects_hw_ok(sys) ) {
      const std::string hstr1a = "<p>" + d.tr(WS_STR_EFFECTS_INTRO) + "</p><p>" + d.tr(WS_STR_EFFECTS_NOTE) + "</p><p>" + d.tr(WS_STR_EFFECTS_ASK) + "</p><p><br></p>";
      res1 = d.ask3( d.tr(WS_STR_DESKTOP_EFFECTS), hstr1a, d.tr(WS_STR_TURN_ON), d.tr(WS_STR_REVERT_DEFAULTS), false );
    } else {
      const std::string hstr2a = "<p>" + d.tr(WS_STR_EFFECTS_LOW_HW) + "</p><p>" + d.tr(WS_STR_EFFECTS_ASK_ANYWAY) + "</p>";
      res1 = d.ask3( d.tr(WS_STR_WARNING), hstr2a, d.tr(WS_STR_TURN_ON), d.tr(WS_STR_REVERT_DEFAULTS), true );
    }
    if( res1 == 1 ) {
      ws_effects_enable();
      d.info( d.tr(WS_STR_DESKTOP_EFFECTS), d.tr(WS_STR_EFFECTS_ENABLED) );
    } else if( res1 == 0 ) {
      ws_effects_disable();
      d.info( d.tr(WS_STR_DESKTOP_EFFECTS), d.tr(WS_STR_EFFECTS_DISABLED) );
    }
  } else {
    d.info( d.tr(WS_STR_INFO), d.tr(WS_STR_TRINITY_PLASMA_ONLY) );
  }
  d.show_main();
}
//---------------------------------------------------------------------------
void ws_flow_autologin( WsDialogs &d, const WsSystem &sys )
{
  const int res1 = d.ask3( d.tr(WS_STR_AUTOLOGIN_CONFIG), d.tr(WS_STR_AUTOLOGIN_ASK), d.tr(WS_STR_AUTOLOGIN_ENABLE), d.tr(WS_STR_REVERT_DEFAULTS), false );
  if( res1 == 1 ) {
    if( ws_autologin( true, sys ) ) d.info( d.tr(WS_STR_AUTOLOGIN), d.tr(WS_STR_AUTOLOGIN_ENABLED) );
  } else if( res1 == 0 ) {
    if( ws_autologin( false, sys ) ) d.info( d.tr(WS_STR_AUTOLOGIN), d.tr(WS_STR_AUTOLOGIN_DISABLED) );
  }
}
//---------------------------------------------------------------------------
void ws_flow_screen_scaling( WsDialogs &d, const WsSystem &sys )
{
  d.hide_main();
  const bool ran = ws_screen_scaling(sys);
  d.show_main();
  if( ! ran ) d.warning( d.tr(WS_STR_SCREEN_SCALING), d.tr(WS_STR_SCREEN_SCALING_MISSING) );
}
//---------------------------------------------------------------------------
bool ws_flow_trinity_only( WsDialogs &d, const WsSystem &sys )
{
  if( sys.session != "trinity" ) {
    d.info( d.tr(WS_STR_INFO), d.tr(WS_STR_TRINITY_ONLY) );
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool ws_flow_browser_ready( WsDialogs &d, const WsSystem &sys )
{
  if( ws_browser_available(sys) ) return true;
  d.info( d.tr(WS_STR_INFO), d.tr(WS_STR_NO_BROWSER) );
  return false;
}
//---------------------------------------------------------------------------
void ws_flow_startmenu_done( WsDialogs &d, int type )
{
  const char *msgid = WS_STR_MENU_KICKOFF;
  if( type == ws_menu_type_bourbon ) msgid = WS_STR_MENU_BOURBON;
  else if( type == ws_menu_type_classic ) msgid = WS_STR_MENU_CLASSIC;
  else if( type == ws_menu_type_keep ) msgid = "";
  d.info( d.tr(WS_STR_STARTMENU_CONFIG), (msgid[0] == '\0') ? std::string() : d.tr(msgid) );
}
//---------------------------------------------------------------------------
