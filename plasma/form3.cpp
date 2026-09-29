//---------------------------------------------------------------------------
#include "form1.h"
#include "form3.h"

#include <ws_actions.h>
#include <ws_strings.h>
#include "ws_dialogs_qt.h"
#include <ws_flows.h>

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
//---------------------------------------------------------------------------
#define BUTT1_TXT wsTr(WS_STR_APPLY)
//---------------------------------------------------------------------------
TForm3 *Form3;
//---------------------------------------------------------------------------
TForm3::TForm3( QWidget* parent ) : QDialog( parent )
{
    setupUi(this);
    setWindowTitle( wsTr(WS_STR_STARTMENU_CONFIG) + " - Welcome screen");
    textLabel1->setText( wsTr(WS_STR_STARTMENU_ASK) );
    pushButton1->setText( BUTT1_TXT );
    pushButton4->setText( wsTr(WS_STR_CANCEL) );
    QFontMetrics fm( font() );
    pushButton1->setMinimumWidth( fm.horizontalAdvance( pushButton1->text() ) + 32 );
    pushButton4->setMinimumWidth( fm.horizontalAdvance( pushButton4->text() ) + 32 );
    connect( pushButton1, &QPushButton::clicked, this, &TForm3::pushButton1_clicked );
    connect( pushButton4, &QPushButton::clicked, this, &TForm3::pushButton4_clicked );
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
    pushButton1->setText( wsTr(WS_STR_WORKING) );
    QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
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
    { WsDialogsQt d(this, nullptr); ws_flow_startmenu_done( d, type ); }
    accept();
}
//---------------------------------------------------------------------------
void TForm3::pushButton4_clicked()
{
    reject();
}
//---------------------------------------------------------------------------
