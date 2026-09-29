//---------------------------------------------------------------------------
#include <stdlib.h>
#include <tdelocale.h>
#include <tdeaboutdata.h>
#include <tdecmdlineargs.h>
#include <tdeapplication.h>
#include "appmain.h"
#include "form1.h"
#include "form2.h"
#include "form3.h"
//---------------------------------------------------------------------------
TMainWin *MainWin;
//---------------------------------------------------------------------------
TMainWin::TMainWin()
    : TDEMainWindow()
{
    move((TDEApplication::desktop()->width() - width()) / 2, (TDEApplication::desktop()->height() - height()) / 4);
    Form1 = new TForm1( this ); Form1->hide();
    Form2 = new TForm2( this ); Form2->hide();
    Form3 = new TForm3( this ); Form3->hide();
    setCentralWidget( Form1 );
    Form1->show();
}
//---------------------------------------------------------------------------
TMainWin::~TMainWin()
{
}
//---------------------------------------------------------------------------
static const char description[] =
    I18N_NOOP("Q4OS Welcome screen");

static const char version[] = "0.1";
//---------------------------------------------------------------------------
static TDECmdLineOptions options[] =
{
    TDECmdLineLastOption
};
//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
    TDEAboutData about("welcome-screen", I18N_NOOP("Welcome screen"), version, description,
                    TDEAboutData::License_GPL, "(C) 2025 Q4OS", 0, 0, "q4os@q4os.org");
    about.addAuthor( "Q4OS", 0, "q4os@q4os.org" );
    TDECmdLineArgs::init(argc, argv, &about);
    TDECmdLineArgs::addCmdLineOptions( options );
    TDEApplication app;
    TMainWin *mainWin = 0;

    if (app.isRestored())
    {
    }
    else
    {
        TDECmdLineArgs *args = TDECmdLineArgs::parsedArgs();
        mainWin = new TMainWin();
        app.setMainWidget( mainWin );
        mainWin->show();
        args->clear();
    }

    return app.exec();
}
//---------------------------------------------------------------------------
