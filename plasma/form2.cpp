//---------------------------------------------------------------------------
#include "form1.h"
#include "form2.h"

#include <ws_actions.h>
#include <ws_strings.h>
#include "ws_dialogs_qt.h"
#include <ws_flows.h>

#include <QApplication>
#include <QLabel>
#include <QPushButton>
//---------------------------------------------------------------------------
#define BUTT1_TXT wsTr(WS_STR_SWITCH_KICKOFF)
#define BUTT2_TXT wsTr(WS_STR_SWITCH_BOURBON)
#define BUTT3_TXT wsTr(WS_STR_REVERT_CLASSIC)
//---------------------------------------------------------------------------
TForm2 *Form2;
//---------------------------------------------------------------------------
TForm2::TForm2( QWidget* parent ) : QDialog( parent )
{
    setupUi(this);
    setWindowTitle( wsTr(WS_STR_STARTMENU_CONFIG) + " - Welcome screen");
    textLabel1->setText( wsTr(WS_STR_STARTMENU_ASK) );
    pushButton1->setText( BUTT1_TXT );
    pushButton2->setText( BUTT2_TXT );
    pushButton3->setText( BUTT3_TXT );
    pushButton4->setText( wsTr(WS_STR_CANCEL) );
    QFontMetrics fm( font() );
    pushButton1->setMinimumWidth( fm.horizontalAdvance( pushButton1->text() ) + 32 );
    pushButton2->setMinimumWidth( fm.horizontalAdvance( pushButton2->text() ) + 32 );
    pushButton3->setMinimumWidth( fm.horizontalAdvance( pushButton3->text() ) + 32 );
    pushButton4->setMinimumWidth( fm.horizontalAdvance( pushButton4->text() ) + 32 );
    connect( pushButton1, &QPushButton::clicked, this, &TForm2::pushButton1_clicked );
    connect( pushButton2, &QPushButton::clicked, this, &TForm2::pushButton2_clicked );
    connect( pushButton3, &QPushButton::clicked, this, &TForm2::pushButton3_clicked );
    connect( pushButton4, &QPushButton::clicked, this, &TForm2::pushButton4_clicked );
}
//---------------------------------------------------------------------------
TForm2::~TForm2()
{
}
//---------------------------------------------------------------------------
static void apply_type( QDialog *dlg, QPushButton *button, const QString &label, int type )
{
    button->clearFocus();
    button->setDown( true );
    button->setText( wsTr(WS_STR_WORKING) );
    QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
    ws_startmenu_apply( ws_menu_structure_keep, type );
    dlg->hide();
    button->setText( label );
    button->setDown( false );
    { WsDialogsQt d(dlg, nullptr); ws_flow_startmenu_done( d, type ); }
    dlg->accept();
}
//---------------------------------------------------------------------------
void TForm2::pushButton1_clicked() { apply_type( this, pushButton1, BUTT1_TXT, ws_menu_type_kickoff ); }
void TForm2::pushButton2_clicked() { apply_type( this, pushButton2, BUTT2_TXT, ws_menu_type_bourbon ); }
void TForm2::pushButton3_clicked() { apply_type( this, pushButton3, BUTT3_TXT, ws_menu_type_classic ); }
//---------------------------------------------------------------------------
void TForm2::pushButton4_clicked()
{
    reject();
}
//---------------------------------------------------------------------------
