//---------------------------------------------------------------------------
#include <stdlib.h>
#include <unistd.h>
//#include <sys/sysinfo.h>

//#include <tqlayout.h>
#include <tqlabel.h>
#include <tqpushbutton.h>
//#include <tqiconset.h>
#include <tqeventloop.h>

//#include <kiconloader.h>
#include <tdelocale.h>
#include <tdemessagebox.h>
#include <tdeapplication.h>

#include "form2.h"
//---------------------------------------------------------------------------
#define BUTT1_TXT i18n( "Switch to Kickoff" )
#define BUTT2_TXT i18n( "Switch to Bourbon" )
#define BUTT3_TXT i18n( "Revert to Classic" )
//---------------------------------------------------------------------------
TForm2 *Form2;
//---------------------------------------------------------------------------
TForm2::TForm2( TQWidget* parent, const char* name, WFlags fl )
 : TForm_ui_form2( parent,name,fl )
{
    setCaption( i18n("Start menu configuration") + " - Welcome screen");

//   TQPixmap ret = TDEGlobal::iconLoader()->loadIcon("messagebox_info", TDEIcon::NoGroup, TDEIcon::SizeMedium, TDEIcon::DefaultState, 0, true);
//   pixmapLabel1->setPixmap(ret);

    textLabel1->setText( i18n("<p>Do you want to switch the Start Menu ?</p>") );
    pushButton1->setText( BUTT1_TXT );
    pushButton2->setText( BUTT2_TXT );
    pushButton3->setText( BUTT3_TXT );
    pushButton4->setText( i18n( "Cancel" ) );

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
void TForm2::pushButton1_clicked()
{
    pushButton1->clearFocus();
    pushButton1->setDown( true );
    pushButton1->setText( i18n("Working ...") );
    kapp->processEvents(TQEventLoop::ExcludeUserInput);
    system("ctrl-kmenu --kickoff");
    usleep(400000);
    hide();
    pushButton1->setText( BUTT1_TXT );
    pushButton1->setDown( false );
    KMessageBox::information( this, i18n("<p>Start Menu is now set to Kickoff style.</p>"), i18n("Start menu configuration") );
    accept();
}
//---------------------------------------------------------------------------
void TForm2::pushButton2_clicked()
{
    pushButton2->clearFocus();
    pushButton2->setDown( true );
    pushButton2->setText( i18n("Working ...") );
    kapp->processEvents(TQEventLoop::ExcludeUserInput);
    system("ctrl-kmenu --bourbon");
    usleep(400000);
    hide();
    pushButton2->setText( BUTT2_TXT );
    pushButton2->setDown( false );
    KMessageBox::information( this, i18n("<p>Start Menu is now set to Bourbon style.</p>"), i18n("Start menu configuration") );
    accept();
}
//---------------------------------------------------------------------------
void TForm2::pushButton3_clicked()
{
    pushButton3->clearFocus();
    pushButton3->setDown( true );
    pushButton3->setText( i18n("Working ...") );
    kapp->processEvents(TQEventLoop::ExcludeUserInput);
    system("ctrl-kmenu --classic");
    usleep(400000);
    hide();
    pushButton3->setText( BUTT3_TXT );
    pushButton3->setDown( false );
    KMessageBox::information( this, i18n("<p>Start Menu is now set to Classic style.</p>"), i18n("Start menu configuration") );
    accept();
}
//---------------------------------------------------------------------------
void TForm2::pushButton4_clicked()
{
    reject();
}
//---------------------------------------------------------------------------
