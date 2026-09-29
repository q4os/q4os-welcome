//---------------------------------------------------------------------------
#ifndef WS_DIALOGS_TQT_H
#define WS_DIALOGS_TQT_H
//---------------------------------------------------------------------------
//the shared flows' message boxes (shared/ws_dialogs.h) as KMessageBox, the translation as i18n()
#include "ws_dialogs.h"
#include <tqwidget.h>
#include <tdelocale.h>
#include <tdemessagebox.h>
//---------------------------------------------------------------------------
class WsDialogsTqt : public WsDialogs
{
public:
  WsDialogsTqt( TQWidget *parent, TQWidget *mainwin ) : p(parent), mw(mainwin) {}
  std::string tr( const char *msgid ) { return s( i18n(msgid) ); }
  int ask3( const std::string &title, const std::string &html, const std::string &yes, const std::string &no, bool warning )
  {
    const int r = warning ? KMessageBox::warningYesNoCancel( p, q(html), q(title), KGuiItem(q(yes)), KGuiItem(q(no)) )
                          : KMessageBox::questionYesNoCancel( p, q(html), q(title), KGuiItem(q(yes)), KGuiItem(q(no)) );
    if( r == KMessageBox::Yes ) return 1;
    if( r == KMessageBox::No ) return 0;
    return -1;
  }
  void info( const std::string &title, const std::string &html ) { KMessageBox::information( p, q(html), q(title) ); }
  void warning( const std::string &title, const std::string &html ) { KMessageBox::sorry( p, q(html), q(title) ); }
  void hide_main() { if( mw ) mw->hide(); }
  void show_main() { if( mw ) mw->show(); }
private:
  TQWidget *p, *mw;
  static TQString q( const std::string &t ) { return TQString::fromUtf8( t.c_str() ); }
  static std::string s( const TQString &t ) { return std::string( (const char *)t.utf8() ); }
};
//---------------------------------------------------------------------------
#endif // WS_DIALOGS_TQT_H
//---------------------------------------------------------------------------
