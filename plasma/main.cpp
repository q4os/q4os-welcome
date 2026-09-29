//---------------------------------------------------------------------------
// welcome-screen5.exu: the Plasma (plain Qt5) frontend of the Welcome screen - the same three forms
// as the Trinity frontend (trinity/src), the actions behind them in shared/ws_actions.cpp
//---------------------------------------------------------------------------
#include "form1.h"
#include "form2.h"
#include "form3.h"
#include "ws_tr.h"

#include <QApplication>
#include <QGuiApplication>
#include <QIcon>
#include <QMainWindow>
#include <QScreen>

#include <clocale>
//---------------------------------------------------------------------------
int main( int argc, char **argv )
{
  QApplication app(argc, argv);
  //Wayland has no _NET_WM_ICON: KWin takes a window's icon from the .desktop file whose name
  //matches the app id, and Qt takes the app id from here (default: the executable name, for
  //which no .desktop exists). Names the file this package installs as
  ///usr/share/applications/q4os-welcome-screen5.desktop.
  QGuiApplication::setDesktopFileName("q4os-welcome-screen5");
  setlocale(LC_ALL, "");
  bindtextdomain(WS_I18N_DOMAIN, WS_LOCALE_DIR);
  bind_textdomain_codeset(WS_I18N_DOMAIN, "UTF-8");
  app.setWindowIcon( QIcon::fromTheme("welcome-screen") );

  QMainWindow mainWin;
  mainWin.setWindowTitle( wsTr("Welcome screen") );
  Form1 = new TForm1( &mainWin ); Form1->hide();
  Form2 = new TForm2( &mainWin ); Form2->hide();
  Form3 = new TForm3( &mainWin ); Form3->hide();
  mainWin.setCentralWidget( Form1 );
  Form1->show();
  mainWin.adjustSize();
  //the Trinity window's place: centred, in the upper part of the screen
  const QRect scr = app.primaryScreen()->availableGeometry();
  mainWin.move( scr.x() + (scr.width() - mainWin.width()) / 2, scr.y() + (scr.height() - mainWin.height()) / 4 );
  mainWin.show();

  return app.exec();
}
//---------------------------------------------------------------------------
