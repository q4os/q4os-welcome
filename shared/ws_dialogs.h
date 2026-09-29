//---------------------------------------------------------------------------
#ifndef WS_DIALOGS_H
#define WS_DIALOGS_H
//---------------------------------------------------------------------------
//The message boxes, the translation and the main window of a frontend, as the shared flows
//(ws_flows) use them: each frontend implements this once (trinity/src/ws_dialogs_tqt.h,
//plasma/ws_dialogs_qt.h). Texts are UTF-8, html ones rich text.
#include <string>
//---------------------------------------------------------------------------
class WsDialogs
{
public:
  virtual ~WsDialogs() {}
  virtual std::string tr( const char *msgid ) = 0; //the "welcome-screen" catalog
  //Yes / No / Cancel: 1, 0, -1
  virtual int ask3( const std::string &title, const std::string &html, const std::string &yes, const std::string &no, bool warning ) = 0;
  virtual void info( const std::string &title, const std::string &html ) = 0;
  virtual void warning( const std::string &title, const std::string &html ) = 0;
  virtual void hide_main() = 0; //the Welcome window, while a tool it started runs
  virtual void show_main() = 0;
};
//---------------------------------------------------------------------------
#endif // WS_DIALOGS_H
//---------------------------------------------------------------------------
