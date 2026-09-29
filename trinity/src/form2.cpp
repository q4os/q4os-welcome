//---------------------------------------------------------------------------
#include <stdlib.h>
#include <unistd.h>
#include <tqlabel.h>
#include <tqpushbutton.h>
#include <tqeventloop.h>
#include <tdelocale.h>
#include <tdemessagebox.h>
#include <tdeapplication.h>
#include "form2.h"
#include <ws_actions.h>
#include <ws_strings.h>
#include "ws_dialogs_tqt.h"
#include <ws_flows.h>
//---------------------------------------------------------------------------
//the older start menu dialog (three buttons); the window uses Form3 today, this one is kept
#define BUTT1_TXT i18n(WS_STR_SWITCH_KICKOFF)
#define BUTT2_TXT i18n(WS_STR_SWITCH_BOURBON)
#define BUTT3_TXT i18n(WS_STR_REVERT_CLASSIC)
//---------------------------------------------------------------------------
TForm2 *Form2;
//---------------------------------------------------------------------------
TForm2::TForm2( TQWidget* parent, const char* name, WFlags fl )
 : TForm_ui_form2( parent,name,fl )
{
    setCaption( i18n(WS_STR_STARTMENU_CONFIG) + " - Welcome screen");
    textLabel1->setText( i18n(WS_STR_STARTMENU_ASK) );
    pushButton1->setText( BUTT1_TXT );
    pushButton2->setText( BUTT2_TXT );
    pushButton3->setText( BUTT3_TXT );
    pushButton4->setText( i18n(WS_STR_CANCEL) );
    TQFontMetrics fm( font() );
    pushButton1->setMinimumWidth( fm.width( pushButton1->text() ) + 32 );
    pushButton2->setMinimumWidth( fm.width( pushButton2->text() ) + 32 );
    pushButton3->setMinimumWidth( fm.width( pushButton3->text() ) + 32 );
    pushButton4->setMinimumWidth( fm.width( pushButton4->text() ) + 32 );
}
//---------------------------------------------------------------------------
TForm2::~TForm2()
{
}
//---------------------------------------------------------------------------
void TForm2::apply_type( TQPushButton *button, const TQString &label, int type )
{
    button->clearFocus();
    button->setDown( true );
    button->setText( i18n(WS_STR_WORKING) );
    kapp->processEvents(TQEventLoop::ExcludeUserInput);
    ws_startmenu_apply( ws_menu_structure_keep, type );
    hide();
    button->setText( label );
    button->setDown( false );
    { WsDialogsTqt d(this, nullptr); ws_flow_startmenu_done( d, type ); }
    accept();
}
//---------------------------------------------------------------------------
void TForm2::pushButton1_clicked() { apply_type( pushButton1, BUTT1_TXT, ws_menu_type_kickoff ); }
void TForm2::pushButton2_clicked() { apply_type( pushButton2, BUTT2_TXT, ws_menu_type_bourbon ); }
void TForm2::pushButton3_clicked() { apply_type( pushButton3, BUTT3_TXT, ws_menu_type_classic ); }
//---------------------------------------------------------------------------
void TForm2::pushButton4_clicked()
{
    reject();
}
//---------------------------------------------------------------------------
