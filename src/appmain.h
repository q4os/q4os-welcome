//---------------------------------------------------------------------------
#ifndef APPMAIN_H
#define APPMAIN_H
//---------------------------------------------------------------------------
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
//---------------------------------------------------------------------------
//#define CC_QT5
//---------------------------------------------------------------------------
#include <tdemainwindow.h>

#ifdef CC_QT5
// KDE headers
#include <KAboutData>
#include <KLocalizedString>

// Qt headers
#include <QApplication>
#include <QDesktopWidget>
#include <QCommandLineParser>
#include <QIcon>
#include <QLoggingCategory>
#endif
//---------------------------------------------------------------------------
//class TDEMainWindow;
//---------------------------------------------------------------------------
/**
 * @short Application Main Window
 * @author Q4OS <q4os@q4os.org>
 * @version 0.1
 */
class TMainWin : public TDEMainWindow
{
    TQ_OBJECT

public:
    /**
     * Default Constructor
     */
    TMainWin();

    /**
     * Default Destructor
     */
    virtual ~TMainWin();
};
//---------------------------------------------------------------------------
extern TMainWin *MainWin;
//---------------------------------------------------------------------------
#endif // APPMAIN_H
//---------------------------------------------------------------------------
