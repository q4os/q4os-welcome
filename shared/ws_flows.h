//---------------------------------------------------------------------------
#ifndef WS_FLOWS_H
#define WS_FLOWS_H
//---------------------------------------------------------------------------
//What the Welcome screen's buttons and dialogs say and ask, and what an answer does - shared, so
//the TQt and the Qt frontend differ only in their widgets
#include "ws_dialogs.h"
#include "ws_actions.h"
//---------------------------------------------------------------------------
void ws_flow_run_profiler( WsDialogs &d ); //the window hidden while the profiler runs
void ws_flow_desktop_effects( WsDialogs &d, const WsSystem &sys ); //the KWin module, the TDE question, or "not here"
void ws_flow_autologin( WsDialogs &d, const WsSystem &sys );
void ws_flow_screen_scaling( WsDialogs &d, const WsSystem &sys );
bool ws_flow_trinity_only( WsDialogs &d, const WsSystem &sys ); //false (message shown) outside Trinity
bool ws_flow_browser_ready( WsDialogs &d, const WsSystem &sys ); //false (message shown) with no web browser
//a start menu type applied (ws_menu_type_*): the confirmation
void ws_flow_startmenu_done( WsDialogs &d, int type );
//---------------------------------------------------------------------------
#endif // WS_FLOWS_H
//---------------------------------------------------------------------------
