//---------------------------------------------------------------------------
#ifndef WS_DIALOGS_QT_H
#define WS_DIALOGS_QT_H
//---------------------------------------------------------------------------
//the shared flows' message boxes (shared/ws_dialogs.h) as QMessageBox, the translation as wsTr()
#include "ws_dialogs.h"
#include "ws_tr.h"
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
//---------------------------------------------------------------------------
class WsDialogsQt : public WsDialogs
{
public:
  WsDialogsQt( QWidget *parent, QWidget *mainwin ) : p(parent), mw(mainwin) {}
  std::string tr( const char *msgid ) override { return ws_s( wsTr(msgid) ); }
  int ask3( const std::string &title, const std::string &html, const std::string &yes, const std::string &no, bool warning ) override
  {
    QMessageBox box( warning ? QMessageBox::Warning : QMessageBox::Question, ws_q(title), ws_q(html), QMessageBox::NoButton, p );
    QPushButton *y = box.addButton( ws_q(yes), QMessageBox::YesRole );
    QPushButton *n = box.addButton( ws_q(no), QMessageBox::NoRole );
    box.addButton( QMessageBox::Cancel );
    box.setDefaultButton( y );
    box.exec();
    if( box.clickedButton() == y ) return 1;
    if( box.clickedButton() == n ) return 0;
    return -1;
  }
  void info( const std::string &title, const std::string &html ) override { QMessageBox::information( p, ws_q(title), ws_q(html) ); }
  void warning( const std::string &title, const std::string &html ) override { QMessageBox::warning( p, ws_q(title), ws_q(html) ); }
  void hide_main() override { if( mw ) mw->hide(); }
  void show_main() override { if( mw ) mw->show(); }
private:
  QWidget *p, *mw;
};
//---------------------------------------------------------------------------
#endif // WS_DIALOGS_QT_H
//---------------------------------------------------------------------------
