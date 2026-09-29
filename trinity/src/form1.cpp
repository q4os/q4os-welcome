//---------------------------------------------------------------------------
#include "myconfig.h"

#include "form1.h"
#include "form2.h"
#include "form3.h"

#include <ws_actions.h>
#include <ws_strings.h>
#include "ws_dialogs_tqt.h"
#include <ws_flows.h>

#include <stdlib.h>

#include <tqcheckbox.h>
#include <tqpushbutton.h>
#include <tqtooltip.h>
#include <tqlabel.h>
#include <tqpopupmenu.h>
#include <tdelocale.h>
#include <tdemessagebox.h>
#include <tdeapplication.h>
//---------------------------------------------------------------------------
TForm1 *Form1;
//---------------------------------------------------------------------------
static TQString ws_q( const std::string &s ) { return TQString::fromUtf8( s.c_str() ); }
//---------------------------------------------------------------------------
TForm1::TForm1( TQWidget* parent, const char* name, WFlags fl ) : TForm_ui_form1( parent,name,fl )
{
  mw = parent;

  sys = ws_probe();

  //the intro, with the edition's name; the split form is kept registered for future versions
  TQString hlpstr1 = i18n(WS_STR_INTRO);
  TQString hlpstr2 = "<font size=\"4\"><p align=justify><b>" + i18n(WS_STR_INTRO_1) + "</b>, " + i18n(WS_STR_INTRO_2) + "</p><p align=justify>" + i18n(WS_STR_INTRO_3) + "</p></font>";
  hlpstr1 = ws_q( ws_edition_name( std::string(hlpstr1.utf8()), sys ) );
  pixmapLabel1->setPixmap( TQPixmap( ws_q(sys.background) ) );
  textLabel1->setText( hlpstr1 );

  pushButton3->setText( i18n(WS_STR_SCREEN_SCALING) );
  TQToolTip::add(pushButton3, "<font size=\"4\"><p>" + i18n(WS_STR_SCREEN_SCALING_TIP) + "</p></font>");

  hlpstr1 = ws_q( ws_edition_name( std::string(i18n(WS_STR_DONATE).utf8()), sys ) );
  popmenu1 = new TQPopupMenu(this);
  if(sys.session == "trinity") popmenu1->insertItem( i18n(WS_STR_DESKTOP_EFFECTS), this, DQ_SLOT(slot1()) );
  if(sys.swap_button4) {
    pushButton4->setText(i18n(WS_STR_HARDWARE_INFO));
    TQToolTip::add(pushButton4, "<font size=\"4\"><p>" + i18n(WS_STR_HARDWARE_INFO_TIP) + "</p></font>");
  } else {
    if(sys.hwinfo_cmd.length() > 1) popmenu1->insertItem( i18n(WS_STR_HARDWARE_INFO), this, DQ_SLOT(slot4()) );
  }
  popmenu1->insertItem( i18n(WS_STR_DOCUMENTS_ONLINE), this, DQ_SLOT(slot2()) );
  popmenu1->insertSeparator();
  popmenu1->insertItem( i18n(WS_STR_PATREON), this, DQ_SLOT(slot5()) );
  popmenu1->insertItem( hlpstr1, this, DQ_SLOT(slot3()) ); //Donate to Q4OS
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
  WsDialogsTqt d(this, mw);
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
  popmenu1->popup( frame5->mapToGlobal( TQPoint(pushButton20->pos().x() + pushButton20->width() - 10, pushButton20->pos().y() + pushButton20->height() - 10) ) );
}
//---------------------------------------------------------------------------
void TForm1::slot1()
{
  action_desktop_effects();
}
//---------------------------------------------------------------------------
void TForm1::slot2()
{
  WsDialogsTqt d(this, mw);
  if( ! ws_flow_browser_ready( d, sys ) ) return;
  ws_open_docs();
}
//---------------------------------------------------------------------------
void TForm1::slot3()
{
  WsDialogsTqt d(this, mw);
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
  WsDialogsTqt d(this, mw);
  if( ! ws_flow_browser_ready( d, sys ) ) return;
  ws_open_patreon(sys);
}
//---------------------------------------------------------------------------
bool TForm1::check_desktop_session()
{
  WsDialogsTqt d(this, mw);
  return ws_flow_trinity_only( d, sys );
}
//---------------------------------------------------------------------------
void TForm1::action_desktop_effects()
{
  WsDialogsTqt d(this, mw);
  ws_flow_desktop_effects( d, sys );
}
//---------------------------------------------------------------------------
void TForm1::action_screen_scaling()
{
  WsDialogsTqt d(this, mw);
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
  WsDialogsTqt d(this, mw);
  ws_flow_autologin( d, sys );
}
//---------------------------------------------------------------------------
void TForm1::action_hw_info()
{
  ws_hw_info(sys);
}
//---------------------------------------------------------------------------
