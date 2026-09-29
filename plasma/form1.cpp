//---------------------------------------------------------------------------
#include "form1.h"
#include "form2.h"
#include "form3.h"

#include <ws_actions.h>
#include <ws_strings.h>
#include "ws_dialogs_qt.h"
#include <ws_flows.h>

#include <QCheckBox>
#include <QFrame>
#include <QLabel>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
//---------------------------------------------------------------------------
TForm1 *Form1;
//---------------------------------------------------------------------------
TForm1::TForm1( QWidget* parent ) : QWidget( parent )
{
  setupUi(this);
  //a QFrame::Box loses its top line at a fractional scale factor - Plasma 5 on X11 at 125% exports
  //QT_SCREEN_SCALE_FACTORS=1.25 (owner's bookworm VM; reproduced with QT_SCREEN_SCALE_FACTORS=1.25
  //on xcb). The same 1 px line drawn by a style sheet border keeps all four edges there (tested; the
  //style's StyledPanel instead drew only the side lines), so at a fractional factor the Box frames
  //get that border in their own line colour; at whole factors nothing changes
  {
    const qreal dpr = devicePixelRatioF();
    if( dpr != qRound(dpr) ) {
      for( QFrame *f : findChildren<QFrame*>() ) {
        if( (f->frameShape() != QFrame::Box) || f->objectName().isEmpty() ) continue;
        f->setStyleSheet( QString("%1#%2 { border: %3px solid %4; }").arg( f->metaObject()->className(), f->objectName() ).arg( f->lineWidth() ).arg( f->palette().color(QPalette::WindowText).name() ) );
      }
    }
  }
  mw = parent;

  sys = ws_probe();

  //the intro, with the edition's name; the split form is kept registered for future versions
  QString hlpstr1 = wsTr(WS_STR_INTRO);
  QString hlpstr2 = "<font size=\"4\"><p align=justify><b>" + wsTr(WS_STR_INTRO_1) + "</b>, " + wsTr(WS_STR_INTRO_2) + "</p><p align=justify>" + wsTr(WS_STR_INTRO_3) + "</p></font>";
  hlpstr1 = ws_q( ws_edition_name( ws_s(hlpstr1), sys ) );
  pixmapLabel1->setPixmap( QPixmap( ws_q(sys.background) ) );
  textLabel1->setText( hlpstr1 );

  pushButton3->setText( wsTr(WS_STR_SCREEN_SCALING) );
  pushButton3->setToolTip( "<font size=\"4\"><p>" + wsTr(WS_STR_SCREEN_SCALING_TIP) + "</p></font>" );

  hlpstr1 = ws_q( ws_edition_name( ws_s(wsTr(WS_STR_DONATE)), sys ) );
  popmenu1 = new QMenu(this);
  if(sys.session == "trinity") popmenu1->addAction( wsTr(WS_STR_DESKTOP_EFFECTS), this, &TForm1::slot1 );
  if(sys.swap_button4) {
    pushButton4->setText( wsTr(WS_STR_HARDWARE_INFO) );
    pushButton4->setToolTip( "<font size=\"4\"><p>" + wsTr(WS_STR_HARDWARE_INFO_TIP) + "</p></font>" );
  } else {
    if(sys.hwinfo_cmd.length() > 1) popmenu1->addAction( wsTr(WS_STR_HARDWARE_INFO), this, &TForm1::slot4 );
  }
  popmenu1->addAction( wsTr(WS_STR_DOCUMENTS_ONLINE), this, &TForm1::slot2 );
  popmenu1->addSeparator();
  popmenu1->addAction( wsTr(WS_STR_PATREON), this, &TForm1::slot5 );
  popmenu1->addAction( hlpstr1, this, &TForm1::slot3 ); //Donate to Q4OS

  connect( pushButton1, &QPushButton::clicked, this, &TForm1::button1_click );
  connect( pushButton2, &QPushButton::clicked, this, &TForm1::button2_click );
  connect( pushButton3, &QPushButton::clicked, this, &TForm1::button3_click );
  connect( pushButton4, &QPushButton::clicked, this, &TForm1::button4_click );
  connect( pushButton5, &QPushButton::clicked, this, &TForm1::button5_click );
  connect( pushButton6, &QPushButton::clicked, this, &TForm1::button6_click );
  connect( pushButton20, &QPushButton::clicked, this, &TForm1::button20_click );
}
//---------------------------------------------------------------------------
TForm1::~TForm1()
{
  if( checkBox1->isChecked() == false ) {
    ws_remove_autostart();
  }
}
//---------------------------------------------------------------------------
void TForm1::button1_click()
{
  ws_run_swcentre();
}
//---------------------------------------------------------------------------
void TForm1::button2_click()
{
  WsDialogsQt d(this, mw);
  ws_flow_run_profiler( d );
}
//---------------------------------------------------------------------------
void TForm1::button3_click()
{
  action_screen_scaling();
}
//---------------------------------------------------------------------------
void TForm1::button4_click()
{
  if(sys.swap_button4)
    action_hw_info();
  else
    action_switch_startmenu();
}
//---------------------------------------------------------------------------
void TForm1::button5_click()
{
  action_autologin();
}
//---------------------------------------------------------------------------
void TForm1::button6_click()
{
  ws_install_codecs();
}
//---------------------------------------------------------------------------
void TForm1::button20_click()
{
  popmenu1->popup( frame5->mapToGlobal( QPoint(pushButton20->pos().x() + pushButton20->width() - 10, pushButton20->pos().y() + pushButton20->height() - 10) ) );
}
//---------------------------------------------------------------------------
void TForm1::slot1()
{
  action_desktop_effects();
}
//---------------------------------------------------------------------------
void TForm1::slot2()
{
  WsDialogsQt d(this, mw);
  if( ! ws_flow_browser_ready( d, sys ) ) return;
  ws_open_docs();
}
//---------------------------------------------------------------------------
void TForm1::slot3()
{
  WsDialogsQt d(this, mw);
  if( ! ws_flow_browser_ready( d, sys ) ) return;
  ws_open_donate();
}
//---------------------------------------------------------------------------
void TForm1::slot4()
{
  action_hw_info();
}
//---------------------------------------------------------------------------
void TForm1::slot5()
{
  WsDialogsQt d(this, mw);
  if( ! ws_flow_browser_ready( d, sys ) ) return;
  ws_open_patreon(sys);
}
//---------------------------------------------------------------------------
bool TForm1::check_desktop_session()
{
  WsDialogsQt d(this, mw);
  return ws_flow_trinity_only( d, sys );
}
//---------------------------------------------------------------------------
void TForm1::action_desktop_effects()
{
  WsDialogsQt d(this, mw);
  ws_flow_desktop_effects( d, sys );
}
//---------------------------------------------------------------------------
void TForm1::action_screen_scaling()
{
  WsDialogsQt d(this, mw);
  ws_flow_screen_scaling( d, sys );
}
//---------------------------------------------------------------------------
void TForm1::action_switch_startmenu()
{
  if( ! check_desktop_session() ) { return; }
  Form3->exec();
}
//---------------------------------------------------------------------------
void TForm1::action_autologin()
{
  WsDialogsQt d(this, mw);
  ws_flow_autologin( d, sys );
}
//---------------------------------------------------------------------------
void TForm1::action_hw_info()
{
  ws_hw_info(sys);
}
//---------------------------------------------------------------------------
