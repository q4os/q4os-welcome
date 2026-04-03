//---------------------------------------------------------------------------
#include <stdlib.h>
#include <unistd.h>
//#include <sys/sysinfo.h>

//#include <tqlayout.h>
#include <tqlabel.h>
#include <tqbuttongroup.h>
#include <tqradiobutton.h>
#include <tqpushbutton.h>
//#include <tqiconset.h>
#include <tqeventloop.h>

#include <tdeconfig.h>
//#include <kiconloader.h>
#include <tdelocale.h>
#include <tdemessagebox.h>
#include <tdeapplication.h>

#include "form3.h"
//---------------------------------------------------------------------------
#define BUTT1_TXT i18n( "Apply" )
//#define BUTT2_TXT i18n( "Switch to Bourbon" )
//#define BUTT3_TXT i18n( "Revert to Classic" )
//---------------------------------------------------------------------------
TForm3 *Form3;
//---------------------------------------------------------------------------
TForm3::TForm3( TQWidget* parent, const char* name, WFlags fl )
 : TForm_ui_form3( parent,name,fl )
{
    setCaption( i18n("Start menu configuration") + " - Welcome screen");

//   TQPixmap ret = TDEGlobal::iconLoader()->loadIcon("messagebox_info", TDEIcon::NoGroup, TDEIcon::SizeMedium, TDEIcon::DefaultState, 0, true);
//   pixmapLabel1->setPixmap(ret);

    textLabel1->setText( i18n("<p>Do you want to switch the Start Menu ?</p>") );
    pushButton1->setText( BUTT1_TXT );
    pushButton4->setText( i18n( "Cancel" ) );

//     //set buttonGroup2 disabled for q4os installations older then 1.4.10, as konqueror quicklaunch shortcut wouldn't be set correctly
//     TDEConfig tdcf("launcher_panelapplet_modernui_rc");
//     tdcf.setGroup("General");
//     TQString rdcf = tdcf.readEntry( "Buttons", "" );
//     //tqDebug((const char*)rdcf);
//     if( rdcf.contains("q4os_startmenu_webbrowser.desktop") ) {
//       buttonGroup2->setEnabled( false );
//     }

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
    TQString msg1;
    pushButton1->clearFocus();
    pushButton1->setDown( true );
    pushButton1->setText( i18n("Working ...") );
    kapp->processEvents(TQEventLoop::ExcludeUserInput);
    if( radioButton4->isChecked() ) {
      system("dash /usr/share/apps/q4os_system/bin/kmenu_struct.sh --q4os --no-agui");
    }
    if( radioButton5->isChecked() ) {
      system("dash /usr/share/apps/q4os_system/bin/kmenu_struct.sh --tde --no-agui");
    }
    if( radioButton1->isChecked() ) {
      msg1 = i18n("<p>Start Menu is now set to Kickoff style.</p>");
      system("ctrl-kmenu --kickoff");
    }
    if( radioButton2->isChecked() ) {
      msg1 = i18n("<p>Start Menu is now set to Bourbon style.</p>");
      system("ctrl-kmenu --bourbon");
    }
    if( radioButton3->isChecked() ) {
      msg1 = i18n("<p>Start Menu is now set to Classic style.</p>");
      system("ctrl-kmenu --classic");
    }
    usleep(400000);
    hide();
    pushButton1->setText( BUTT1_TXT );
    pushButton1->setDown( false );
    KMessageBox::information( this, msg1, i18n("Start menu configuration") );
    accept();
}
//---------------------------------------------------------------------------
void TForm3::pushButton4_clicked()
{
    reject();
}
//---------------------------------------------------------------------------

