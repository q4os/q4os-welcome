//---------------------------------------------------------------------------
#include <stdlib.h>

#include <tqdir.h>
#include <tdelocale.h>
//#include <kiconloader.h>
#include <tdeaboutdata.h>
#include <tdecmdlineargs.h>
#include <tdemessagebox.h>
#include <tdeapplication.h>

#include "appmain.h"
#include "form1.h"
#include "form2.h"
#include "form3.h"
// ... etc ... include form headers here ...

/*#include <X11/Xutil.h>
//#include <X11/keysym.h>
#include <X11/Xatom.h>
//#include <fixx11h.h>*/
//---------------------------------------------------------------------------
TMainWin *MainWin;
//---------------------------------------------------------------------------
TMainWin::TMainWin()
    : TDEMainWindow()
//WStyle_StaysOnTop:(WFlags)WX11BypassWM
{
    //if(! getenv("Q4DPI")) setFixedSize(614, 464);
    move((TDEApplication::desktop()->width() - width()) / 2, (TDEApplication::desktop()->height() - height()) / 4);

/*    TDEIconLoader &loader = *TDEGlobal::iconLoader();
    TQPixmap pixmap = loader.loadIcon( "q4oslogo", TDEIcon::NoGroup );
    setIcon(pixmap);*/

//         // Signal that we do not want any window controls to be shown at all
//         Atom kde_wm_system_modal_notification;
//         kde_wm_system_modal_notification = XInternAtom(qt_xdisplay(), "_KDE_WM_MODAL_SYS_NOTIFICATION", False);
//         XChangeProperty(qt_xdisplay(), winId(), kde_wm_system_modal_notification, XA_INTEGER, 32, PropModeReplace, (unsigned char *) "TRUE", 1L);
//         setCaption(i18n("TEST"));

    Form1 = new TForm1( this ); Form1->hide();
    Form2 = new TForm2( this ); Form2->hide();
    Form3 = new TForm3( this ); Form3->hide();
//    // ... etc ... create static forms here ...
    setCentralWidget( Form1 );

//    kapp->setMainWidget( Form1 );
    Form1->show();
}
//---------------------------------------------------------------------------
TMainWin::~TMainWin()
{
//tqDebug("DELETE MAINWIN !");
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static const char description[] =
    I18N_NOOP("Q4OS Welcome screen");

static const char version[] = "0.1";
//---------------------------------------------------------------------------
#ifndef CC_QT5
static TDECmdLineOptions options[] =
{
//    { "+[URL]", I18N_NOOP( "Document to open" ), 0 },
    TDECmdLineLastOption
};
#endif
//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
// // do not show welcome screen while vboxgutils shows own
//   TQString hstr1 = TQString::fromLocal8Bit(getenv("HOME"));
//   TQDir hlpdir(hstr1 + "/.vboxgutils");
//   if (hlpdir.exists()) {
//     if( system("LC_ALL=\"\" LANG=C dpkg -s \"virtualbox-guest-extq\" 2>&1 | grep \"install ok installed\" > /dev/null") != 0 ) {
//       return(10);
//     }
//   }

#ifdef CC_QT5
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("welcome-screen");
    KAboutData about( QStringLiteral("welcome-screen"), i18n("Welcome screen"), version, i18n(description),
                    KAboutLicense::GPL, "(C) 2025 Q4OS", "", "https://q4os.org" );
    about.addAuthor( "Q4OS", "", "q4os@q4os.org", "https://q4os.org" );
    about.setOrganizationDomain("q4os.org");
    about.setDesktopFileName(QStringLiteral("q4os-welcome-screen5"));
    KAboutData::setApplicationData(about);
    app.setWindowIcon(QIcon::fromTheme(QStringLiteral("welcome-screen")));
    QCommandLineParser parser;
    //parser.addHelpOption();
    //parser.addVersionOption();
    about.setupCommandLine(&parser);
    parser.process(app);
    about.processCommandLine(&parser);

    KMainWin *mainWin = new KMainWin();
    //app.setMainWidget( mainWin );
    mainWin->show();
#else
    TDEAboutData about("welcome-screen", I18N_NOOP("Welcome screen"), version, description,
                    TDEAboutData::License_GPL, "(C) 2025 Q4OS", 0, 0, "q4os@q4os.org");
    about.addAuthor( "Q4OS", 0, "q4os@q4os.org" );
    TDECmdLineArgs::init(argc, argv, &about);
    TDECmdLineArgs::addCmdLineOptions( options );
    TDEApplication app;
    TMainWin *mainWin = 0;

    if (app.isRestored())
    {
//        RESTORE(TMainWin());
    }
    else
    {
        // no session.. just start up normally
        TDECmdLineArgs *args = TDECmdLineArgs::parsedArgs();

        /// @todo do something with the command line args here

        mainWin = new TMainWin();
        app.setMainWidget( mainWin );
        mainWin->show();

//         Form1 = new TForm1( NULL, "Form1" );
// //        Form2 = new TForm2( NULL, "Form2" );
//         if(Form1->check_welcomescreen_env() != 0) {
//           return 100;
//         }
// //        Form2->initialize();
//         app.setMainWidget( Form1 );
//         Form1->show();

        args->clear();
    }
#endif

    // mainWin has WDestructiveClose flag by default, so it will delete itself.
    return app.exec();
}
//---------------------------------------------------------------------------
