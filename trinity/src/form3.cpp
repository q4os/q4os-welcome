//---------------------------------------------------------------------------
#include <stdlib.h>
#include <unistd.h>
#include <tqlabel.h>
#include <tqbuttongroup.h>
#include <tqradiobutton.h>
#include <tqpushbutton.h>
#include <tqeventloop.h>
#include <tdelocale.h>
#include <tdemessagebox.h>
#include <tdeapplication.h>
#include "form3.h"
#include <ws_actions.h>
#include <ws_strings.h>
#include "ws_dialogs_tqt.h"
#include <ws_flows.h>
//---------------------------------------------------------------------------
#define BUTT1_TXT i18n(WS_STR_APPLY)
//---------------------------------------------------------------------------
TForm3 *Form3;
//---------------------------------------------------------------------------
TForm3::TForm3( TQWidget* parent, const char* name, WFlags fl )
 : TForm_ui_form3( parent,name,fl )
{
    setCaption( i18n(WS_STR_STARTMENU_CONFIG) + " - Welcome screen");
    textLabel1->setText( i18n(WS_STR_STARTMENU_ASK) );
    pushButton1->setText( BUTT1_TXT );
    pushButton4->setText( i18n(WS_STR_CANCEL) );
    TQFontMetrics fm( font() );
    pushButton1->setMinimumWidth( fm.width( pushButton1->text() ) + 32 ); //todo: set button width as max of BUTT1_TXT and i18n(BUTT1_TXT)
    pushButton4->setMinimumWidth( fm.width( pushButton4->text() ) + 32 );
}
//---------------------------------------------------------------------------
TForm3::~TForm3()
{
}
//---------------------------------------------------------------------------
void TForm3::pushButton1_clicked()
{
    pushButton1->clearFocus();
    pushButton1->setDown( true );
    pushButton1->setText( i18n(WS_STR_WORKING) );
    kapp->processEvents(TQEventLoop::ExcludeUserInput);
    int structure = ws_menu_structure_keep;
    if( radioButton4->isChecked() ) structure = ws_menu_structure_q4os;
    if( radioButton5->isChecked() ) structure = ws_menu_structure_tde;
    int type = ws_menu_type_keep;
    if( radioButton1->isChecked() ) type = ws_menu_type_kickoff;
    if( radioButton2->isChecked() ) type = ws_menu_type_bourbon;
    if( radioButton3->isChecked() ) type = ws_menu_type_classic;
    ws_startmenu_apply( structure, type );
    hide();
    pushButton1->setText( BUTT1_TXT );
    pushButton1->setDown( false );
    { WsDialogsTqt d(this, nullptr); ws_flow_startmenu_done( d, type ); }
    accept();
}
//---------------------------------------------------------------------------
void TForm3::pushButton4_clicked()
{
    reject();
}
//---------------------------------------------------------------------------
