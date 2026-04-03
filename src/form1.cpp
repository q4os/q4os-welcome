//---------------------------------------------------------------------------
#include "myconfig.h"

//#include "appmain.h"
#include "form1.h"
#include "form2.h"
#include "form3.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>

#ifdef CC_QT5
//#include <QToolTip>
#include <QMenu>
#include <QDebug>
#include <QFile>
//#include <QProcess>
//#include <KMessageBox>
#else
#include <cmd.h>
#endif

//#include <tqvariant.h>
//#include <tqcursor.h>
//#include <tqfile.h>
#include <tqcheckbox.h>
#include <tqpushbutton.h>
#include <tqtooltip.h>
#include <tqlabel.h>
//#include <tqtextedit.h>
#include <tqpopupmenu.h>
#include <tqprocess.h>
#include <tdelocale.h>
//#include <kiconloader.h>
#include <tdemessagebox.h>
#include <tdeapplication.h>

/*#include <X11/Xutil.h>
//#include <X11/keysym.h>
#include <X11/Xatom.h>
//#include <fixx11h.h>*/

//---------------------------------------------------------------------------
TForm1 *Form1;
//---------------------------------------------------------------------------
#ifdef CC_QT5
TForm1::TForm1( QWidget* parent, Qt::WindowFlags fl ) : QWidget( parent,fl )
#else
TForm1::TForm1( TQWidget* parent, const char* name, WFlags fl ) : TForm_ui_form1( parent,name,fl )
#endif
{
#ifdef CC_QT5
  setupUi(this);
#endif

  mw = parent;

/*  if( TQString(getenv("HIDE_DECORATION")) == "1" ) {
    // Signal that we do not want any window controls to be shown at all
    Atom kde_wm_system_modal_notification;
    kde_wm_system_modal_notification = XInternAtom(tqt_xdisplay(), "_TDE_WM_MODAL_SYS_NOTIFICATION", False);
    XChangeProperty(tqt_xdisplay(), winId(), kde_wm_system_modal_notification, XA_INTEGER, 32, PropModeReplace, (unsigned char *) "TRUE", 1L);
    //setCaption(i18n("Desktop Profiler"));
  }
  TDEIconLoader &loader = *TDEGlobal::iconLoader();
  TQPixmap pixmap = loader.loadIcon( "q4oslogo", TDEIcon::NoGroup );
  setIcon(pixmap);

  setModal(true);*/
//  setFixedSize(580, 250);
  //move((TDEApplication::desktop()->width() - width()) / 2, (TDEApplication::desktop()->height() - height()) / 2);

/*
  TQFont ff( pushButton4->font() );
  TQFontMetrics fm( pushButton4->font() );
  tqDebug("text: %d, button: %d", fm.width( pushButton4->text() ), pushButton4->width());
  while( fm.width( pushButton4->text() ) >= pushButton4->width() * 1.8 ) {
    ff.setPointSize( ff.pointSize() - 0.1 );
    pushButton1->setFont( ff );
    pushButton2->setFont( ff );
    pushButton3->setFont( ff );
    pushButton4->setFont( ff );
    pushButton5->setFont( ff );
    pushButton6->setFont( ff );
    fm = pushButton4->font();
    //mw->setFixedSize(850, 464);
    tqDebug("text: %d, button: %d", fm.width( pushButton4->text() ), pushButton4->width());
  }
  textLabel1->setFont( ff );
  checkBox1->setFont( ff );
*/

//  textEdit1->setPaletteBackgroundColor( paletteBackgroundColor() );
//  pushButton20->hide();

  if(TQFile::exists("/var/lib/q4os/isquarkos.stp"))
    is_quarkos = true;
  else
    is_quarkos = false;

//is_quarkos = true;

  TQPixmap hlppxmap1; //= TQPixmap("/opt/program_files/q4os-welcome/share/background1.png")
  TQString hlpstr1 = i18n("<font size=\"4\"><p align=justify><b>Welcome to Q4OS</b>, fast and powerful desktop operating system focused on long-term stability, reliability and classic style user interface.</p><p align=justify>Q4OS is installed as a very basic and clean desktop environment with the minimal software kit. Now it's the right time to adjust your new desktop, you might want to make use of tweaking shortcuts below.</p></font>");

  TQString hlpstr2;
  //not used, but present for strings to be registered to i18n for the future versions
  hlpstr2 =
    "<font size=\"4\"><p align=justify><b>" +
    i18n("Welcome to Q4OS") +
    "</b>, " +
    i18n("fast and powerful desktop operating system focused on long-term stability, reliability and classic style user interface.") +
    "</p><p align=justify>" +
    i18n("Q4OS is installed as a very basic and clean desktop environment with the minimal software kit. Now it's the right time to adjust your new desktop, you might want to make use of tweaking shortcuts below.") +
    "</p></font>";

  if(is_quarkos) {
    hlpstr1 = hlpstr1.replace("Q4OS", "Quarkos");
    if(TQFile::exists("/opt/program_files/q4os-welcome/share/background2.png")) {
      hlppxmap1 = TQPixmap("/opt/program_files/q4os-welcome/share/background2.png");
    } else if(TQFile::exists("/mnt/tmsworkspace/a01/q4os_welcome/code_wk_copy/src/data/background2.png")) {
      hlppxmap1 = TQPixmap("/mnt/tmsworkspace/a01/q4os_welcome/code_wk_copy/src/data/background2.png"); //remove later
    }
  } else {
    if(TQFile::exists("/opt/program_files/q4os-welcome/share/background1.png")) {
      hlppxmap1 = TQPixmap("/opt/program_files/q4os-welcome/share/background1.png");
    } else if(TQFile::exists("/mnt/tmsworkspace/a01/q4os_welcome/code_wk_copy/src/data/background1.png")) {
      hlppxmap1 = TQPixmap("/mnt/tmsworkspace/a01/q4os_welcome/code_wk_copy/src/data/background1.png"); //remove later
    }
  }
  pixmapLabel1->setPixmap( hlppxmap1 );
  textLabel1->setText( hlpstr1 );

/*
//todo: try to decrease textLabel1 font size to fit in the textLabel1
//see https://forum.qt.io/topic/64188/how-to-get-the-multiline-qlabel-s-text-real-height/5
TQFont ff2( textLabel1->font() );
TQFontMetrics metrics(font());
TQRect rect = metrics.boundingRect( 0, 0, TQApplication::desktop()->width(), TQApplication::desktop()->height(), TQt::WordBreak, textLabel1->text() );
while( 3 * rect.height() >= textLabel1->height() ) {
  ff2.setPointSize( ff2.pointSize() - 1 );
  textLabel1->setFont( ff2 );
  metrics = textLabel1->font();
  rect = metrics.boundingRect( 0, 0, TQApplication::desktop()->width(), TQApplication::desktop()->height(), TQt::WordBreak, textLabel1->text() );
}
*/

  desktop_sess = getenv("QDSK_SESSION");
  qaptdistr = getenv("QAPTDISTR");

  hwinfo_cmd = "";
  if( (desktop_sess == "plasma") && (TQFile::exists("/usr/bin/cpuqinfo5.exu")) ) {
    hwinfo_cmd = "/usr/bin/cpuqinfo5.exu";
  }
  if( (desktop_sess == "trinity") && (TQFile::exists("/usr/bin/cpuqinfo.exu")) ) {
    hwinfo_cmd = "/usr/bin/cpuqinfo.exu";
  }

  hlpstr1 = i18n("Screen scaling");
  hlpstr2 = "<font size=\"4\"><p>" + i18n("Resize fonts and icons to adjust them according to the current screen resolution and make them more readable.") + "</p></font>";
  pushButton3->setText( hlpstr1 );
#ifdef CC_QT5
  pushButton3->setProperty("toolTip", QVariant(hlpstr2));
#else
  TQToolTip::add(pushButton3, hlpstr2);
#endif

  //swap button "switch start menu" to "hardware info" for plasma desktop
  swap_button4 = false;
  if((desktop_sess == "plasma") && (hwinfo_cmd.length() > 1)) {
    swap_button4 = true;
  }

  hlpstr1 = i18n("Donate to Q4OS");
  if(is_quarkos) hlpstr1 = hlpstr1.replace("Q4OS", "Quarkos");
  popmenu1 = new TQPopupMenu(this);
#ifdef CC_QT5
  if(desktop_sess == "trinity") popmenu1->addAction( i18n("Desktop effects"), this, SLOT(slot1()) );
  //popmenu1->addAction( i18n("System resources"), this, SLOT(slot6()) );
  if(swap_button4) {
    pushButton4->setText(i18n("Hardware info"));
    pushButton4->setProperty("toolTip", QVariant("<font size=\"4\"><p>" + i18n("Well arranged system hardware information.") + "</p></font>"));
  } else {
    if(hwinfo_cmd.length() > 1) popmenu1->addAction( i18n("Hardware info"), this, SLOT(slot4()) );
  }
  popmenu1->addAction( i18n("Documents online"), this, SLOT(slot2()) );
  popmenu1->addSeparator();
  popmenu1->addAction( i18n("Support us on Patreon"), this, SLOT(slot5()) ); //? modify to: "Support us on Patreon and get benefits"
  popmenu1->addAction( hlpstr1, this, SLOT(slot3()) ); //Donate to Q4OS
#else
  if(desktop_sess == "trinity") popmenu1->insertItem( i18n("Desktop effects"), this, DQ_SLOT(slot1()) );
  //popmenu1->insertItem( i18n("System resources"), this, DQ_SLOT(slot6()) );
  if(swap_button4) {
    pushButton4->setText(i18n("Hardware info"));
    TQToolTip::add(pushButton4, "<font size=\"4\"><p>" + i18n("Well arranged system hardware information.") + "</p></font>");
  } else {
    if(hwinfo_cmd.length() > 1) popmenu1->insertItem( i18n("Hardware info"), this, DQ_SLOT(slot4()) );
  }
  popmenu1->insertItem( i18n("Documents online"), this, DQ_SLOT(slot2()) );
  popmenu1->insertSeparator();
  popmenu1->insertItem( i18n("Support us on Patreon"), this, DQ_SLOT(slot5()) );
  popmenu1->insertItem( hlpstr1, this, DQ_SLOT(slot3()) ); //Donate to Q4OS
#endif
  //pushButton20->setMenu(menu);

  struct sysinfo info;
  sysinfo( &info );
  phmemsize = (size_t)info.totalram * (size_t)info.mem_unit;
/*  sse2_ok = true;
  if(system("q4hw-info --sse2 > /dev/null") != 0) {
    sse2_ok = false;
  }*/

  //get dpkg architecture
#ifdef CC_QT5
  QProcess proc1;
  proc1.setProcessChannelMode(QProcess::MergedChannels);
  proc1.start("dpkg", QStringList() << "--print-architecture");
  if( ! proc1.waitForStarted() ) {} //error handling
  if( ! proc1.waitForFinished() )
      dpkg_arch = "unknown";
  else
      dpkg_arch = proc1.readAll();
#else
  TCm2d shellcmd1;
  dpkg_arch = shellcmd1.getCmdOut("dpkg --print-architecture");
#endif
  //dpkg_arch.remove('\n');
  dpkg_arch = dpkg_arch.simplifyWhiteSpace();
  if(dpkg_arch.length() < 1) dpkg_arch = "unknown";
  qtt_debug("architecture: " + dpkg_arch);
}
//---------------------------------------------------------------------------
TForm1::~TForm1()
{
  if( checkBox1->isChecked() == false ) {
    qtt_debug("removing from autostart");
    //system("rm -f $HOME/.trinity/Autostart/q4os-welcome-screen.desktop"); //or kwriteconfig ..
    //system("rm -f $XDG_CONFIG_HOME/autostart/q4os-welcome-screen.desktop"); //or kwriteconfig ..
    TQString xdgcfgh = getenv("XDG_CONFIG_HOME");
    if(xdgcfgh.length() < 1) xdgcfgh = TQString(getenv("HOME")) + "/.config";
    FILE *hlpfl1;
    TQString hlpstr1;
    hlpstr1 = "rm -f " + xdgcfgh + "/autostart/q4os-welcome-screen.desktop";
    hlpfl1 = popen( hlpstr1.latin1(), "r" ); pclose(hlpfl1);
    hlpstr1 = "rm -f " + xdgcfgh + "/autostart/q4os-welcome-screen5.desktop";
    hlpfl1 = popen( hlpstr1.latin1(), "r" ); pclose(hlpfl1);
  }
}
//---------------------------------------------------------------------------
/*
int TForm1::check_ws_env()
{
  if( is_running("q4welcome.exu) ) {
    KMessageBox::sorry( this, "<p>Another instance of Welcome Screen is running, leaving ...<p>" );
    return(1);
  }
  if( TQString(getenv("XXXXXXXXXXX")).length() > 0 ) {
    switch( KMessageBox::questionYesNo( this, i18n("<p>Some message ...</p>"), i18n("Q4OS Setup"), i18n("Keep clean"), i18n("Run Desktop Profiler") ) ) {
    case KMessageBox::Yes :
      return(2);
      break;
    case KMessageBox::No :
      break;
    default:
      break;
    }
  }
  return(0);
}
*/
//---------------------------------------------------------------------------
void TForm1::button1_click()
{
  if( check_vboxgutils() ) { return; }
  //mw->hide();
  //system("konqueror http://www.q4os.org/some_page.html#q4apps &");
  //system("swcentre.exu --icon swcentre &");
  FILE *hlpfl1 = popen( "swcentre.exu --icon swcentre &", "w" ); pclose(hlpfl1);
  //mw->show();
}
//---------------------------------------------------------------------------
void TForm1::button2_click()
{
  if( check_vboxgutils() ) { return; }
  mw->hide();
  //system("swprofiler.exu");
  FILE *hlpfl1 = popen( "swprofiler.exu", "w" ); pclose(hlpfl1);
  mw->show();
}
//---------------------------------------------------------------------------
void TForm1::button3_click()
{
  if( check_vboxgutils() ) { return; }
  action_screen_scaling();
}
//---------------------------------------------------------------------------
void TForm1::button4_click()
{
  if( check_vboxgutils() ) { return; }
  if(swap_button4)
    action_hw_info();
  else
    action_switch_startmenu();
}
//---------------------------------------------------------------------------
void TForm1::button5_click()
{
  if( check_vboxgutils() ) { return; }
  action_autologin();
}
//---------------------------------------------------------------------------
void TForm1::button6_click()
{
/*  if( dpkg_arch == "armhf" ) {
    KMessageBox::information( this, i18n("<p>ARM CPU architecture detected. It doesn't support proprietary multimedia codecs.</p>"), i18n("Info") );
    return;
  }*/
  if( check_vboxgutils() ) { return; }
//  if( ! check_swprofiler_processed() ) { return; }
  TQString codecs_setup_file = "q4os-ipcodecs";
  /*if( qaptdistr == "buster" ) {
    codecs_setup_file = "q4os3-ipcodecs"
  }*/
  TQString cmdxx = "dash /usr/share/apps/q4os_system/bin/dwnld_instl.sh \"" + codecs_setup_file + "\" \"Multimedia Codecs\" \"Multimedia Codecs\" \"package_settings\" \"\" \"\" \"\" \"\" \"1\" &";
  system(cmdxx.latin1());
}
//---------------------------------------------------------------------------
void TForm1::button20_click()
{
  //popmenu1->popup(TQCursor::pos());
  popmenu1->popup( frame5->mapToGlobal( TQPoint(pushButton20->pos().x() + pushButton20->width() - 10, pushButton20->pos().y() + pushButton20->height() - 10) ) );
}
//---------------------------------------------------------------------------
void TForm1::slot1()
{
  action_desktop_effects();
}
//---------------------------------------------------------------------------
void TForm1::slot2()
{
  const TQString cmd1 = get_default_browser() + " \"https://www.q4os.org/documents.html\" &";
  system(cmd1.latin1());
}
//---------------------------------------------------------------------------
void TForm1::slot3()
{
  const TQString cmd1 = get_default_browser() + " \"https://www.q4os.org/dnt_donate.html\" &"; //https://www.paypal.com/donate/?hosted_button_id=EMZ39LECTE2XA
  system(cmd1.latin1());
}
//---------------------------------------------------------------------------
void TForm1::slot4()
{
  action_hw_info();
}
//---------------------------------------------------------------------------
void TForm1::slot5()
{
  action_open_patreon();
}
//---------------------------------------------------------------------------
/*
void TForm1::slot6()
{
  TQString cmd1 = "/opt/trinity/bin/konsole --title \"" + i18n("System resources") + "\" --caption \"\" --icon laptop --geometry 780x560 -e htop &";
  system(cmd1.latin1());
}
*/
/*//---------------------------------------------------------------------------
void TForm1::on_vboxgutils_action()
{
}*/
//---------------------------------------------------------------------------
bool TForm1::check_vboxgutils()
{
/*WRONG: if( is_running( "vboxgutils_wrapper.sh" ) ) {*/

  if( TQFile::exists( "/tmp/.vboxgutils-afT4g.tmp" ) ) {
    KMessageBox::information( this, i18n("<p>Virtualbox installation has been detected !</p><p>Actions are disabled during Virtualbox setup, please wait until end of the Virtualbox installation.</p>"), i18n("Info") );
    return(true);
  }
  if( TQFile::exists( "/tmp/.nvdinstl-afT4g.tmp" ) ) {
    KMessageBox::information( this, i18n("<p>NVIDIA installation has been detected !</p><p>Actions are disabled during NVIDIA setup, please wait until end of the NVIDIA installation.</p>"), i18n("Info") );
    return(true);
  }
  return(false);
}
//---------------------------------------------------------------------------
bool TForm1::check_desktop_session()
{
  if( desktop_sess != "trinity" ) {
    KMessageBox::information( this, i18n("<p>This action is available for Trinity desktop only.</p>"), i18n("Info") );
    return(false);
  }
  return(true);
}
//---------------------------------------------------------------------------
/*
bool TForm1::check_swprofiler_processed()
{
  TDEConfig q4basecfg("/etc/q4os/q4base.conf", true, false);
  q4basecfg.setGroup("DesktopProfiler");
  if(q4basecfg.readBoolEntry("needtoapply", true)) {
    KMessageBox::information( this, i18n("<p>You have applied no desktop profile yet. It's highly recommended to apply a desktop profile before installing applications.</p><p>Please run <b>Dektop Profiler</b> tool to choose and apply a profile.</p>"), i18n("Info") );
    return(false);
  }
  return(true);
}
*/
//---------------------------------------------------------------------------
bool TForm1::check_hw()
{
  if(phmemsize < 1700000000) {
    return(false);
  }
  return(true);
}
//---------------------------------------------------------------------------
void TForm1::action_desktop_effects()
{
  if((desktop_sess == "plasma") && (TQFile::exists("/usr/bin/kcmshell6"))) {
    mw->hide();
    system( "kcmshell6 kcmkwineffects" );
  } else if((desktop_sess == "plasma") && (TQFile::exists("/usr/bin/kcmshell5"))) {
    mw->hide();
    system( "kcmshell5 kcmkwineffects" );
  } else if( desktop_sess == "trinity" ) {
    int res1;
    if( check_hw() ) {
      const TQString hstr1a =
        "<p>" +
        i18n("This option is to turn smoothing and beautifying desktop effects on.") +
        "</p><p>" +
        i18n("Note, desktop effects will work flawlessly on modern hardware only, it's not recommended to use it with legacy hardware. A short system testing will be performed to ensure the hardware is ready to accept the configuration.") +
        "</p><p>" +
        i18n("Do you want to turn Desktop Effects on ?") +
        "</p><p><br></p>";
      const TQString hstr1b = i18n("Desktop effects");
      const TQString hstr1c = i18n("Turn ON");
      const TQString hstr1d = i18n("Revert to defaults");
#ifdef CC_QT5
      res1 = KMessageBox::questionYesNoCancel( this, hstr1a, hstr1b, KGuiItem(hstr1c), KGuiItem(hstr1d) );
#else
      res1 = KMessageBox::questionYesNoCancel( this, hstr1a, hstr1b, hstr1c, hstr1d );
#endif
    } else {
      const TQString hstr2a =
        "<p>" +
        i18n("Your hardware seems to be low to run desktop effects, it's not recommended to turn effects on.") +
        "</p><p>" +
        i18n("Do you really want to turn Desktop Effects on ?") +
        "</p>";
      const TQString hstr2b = i18n("Warning !");
      const TQString hstr2c = i18n("Turn ON");
      const TQString hstr2d = i18n("Revert to defaults");
#ifdef CC_QT5
      res1 = KMessageBox::warningYesNoCancel( this, hstr2a, hstr2b, KGuiItem(hstr2c), KGuiItem(hstr2d) );
#else
      res1 = KMessageBox::warningYesNoCancel( this, hstr2a, hstr2b, hstr2c, hstr2d );
#endif
    }

    FILE *hlpfl1;
    switch( res1 )  {
    case KMessageBox::Yes :
      //system("ctrl-compmgr --enable --no-relogin");
      hlpfl1 = popen( "ctrl-compmgr --enable --no-relogin", "r" ); pclose(hlpfl1);
      KMessageBox::information( this, i18n("<p>Desktop effects have been enabled. Please login again to take changes effect.</p>"), i18n("Desktop effects") );
      break;
    case KMessageBox::No :
      //system("ctrl-compmgr --disable");
      hlpfl1 = popen( "ctrl-compmgr --disable", "r" ); pclose(hlpfl1);
      KMessageBox::information( this, i18n("<p>Desktop effects have been disabled.</p>"), i18n("Desktop effects") );
      break;
    default:
      break;
    }
  } else {
    KMessageBox::information( this, i18n("<p>This action is available for Trinity and Plasma desktops only.</p>"), i18n("Info") );
  }
  mw->show();
}
//---------------------------------------------------------------------------
void TForm1::action_screen_scaling()
{
  TQString commnd1;
  if((desktop_sess == "trinity") && (TQFile::exists("/opt/trinity/bin/screenscalerp.exu"))) {
    commnd1 = "screenscalerp.exu";
  } else if((desktop_sess == "plasma") && (TQFile::exists("/usr/bin/kcmshell6"))) {
    commnd1 = "/usr/bin/kcmshell6";
  } else if((desktop_sess == "plasma") && (TQFile::exists("/usr/bin/kcmshell5"))) {
    commnd1 = "/usr/bin/kcmshell5";
  } else {
    KMessageBox::sorry(this, i18n("Screen scaling tool not found."), i18n("Screen scaling"));
    return;
  }

  mw->hide();
  //mw->setEnabled(false);
  //setEnabled ( false );

  TQProcess process;
#ifdef CC_QT5
  process.setProcessChannelMode(QProcess::MergedChannels);
  if( commnd1 != "screenscalerp.exu" ) {
    process.start(commnd1, QStringList() << "kcm_kscreen");
  } else {
    process.start(commnd1);
  }
  if( ! process.waitForStarted() ) {} //error handling
  if( ! process.waitForFinished() ) {} //error handling
#else
  process.addArgument(commnd1);
  if( commnd1 != "screenscalerp.exu" ) {
    process.addArgument("kcm_kscreen");
  }
  process.start();
  while( process.isRunning() ) {
    usleep(10000);
  }
#endif

  //setEnabled ( true );
  //mw->setEnabled(true);
  mw->show();
}
//---------------------------------------------------------------------------
void TForm1::action_switch_startmenu()
{
  if( ! check_desktop_session() ) { return; }
//  mw->hide();
//  Form2->exec();
  Form3->exec();
  return;

/*  switch( KMessageBox::questionYesNoCancel( this, i18n("<p>Do you want to switch the Start Menu ?</p>"), i18n("Start menu configuration"), i18n("Switch to Kickoff"), i18n("Revert to Classic") ) ) {
  case KMessageBox::Yes :
    system("ctrl-kmenu --kickoff");
    break;
  case KMessageBox::No :
    system("ctrl-kmenu --classic");
    KMessageBox::information( this, i18n("<p>Start Menu is now set to Classic style.<p>"), i18n("Start menu configuration") );
    break;
  default:
    break;
  }
//  mw->show();*/
}
//---------------------------------------------------------------------------
void TForm1::action_autologin()
{
//if( ! check_desktop_session() ) { return; }
//  mw->hide();

#ifdef CC_QT5
  switch( KMessageBox::questionYesNoCancel( this, i18n("<p>Do you want to enable Automatic login ?</p>"), i18n("Autologin configuration"), KGuiItem(i18n("Enable Autologin")), KGuiItem(i18n("Revert to defaults")) ) ) {
#else
  switch( KMessageBox::questionYesNoCancel( this, i18n("<p>Do you want to enable Automatic login ?</p>"), i18n("Autologin configuration"), i18n("Enable Autologin"), i18n("Revert to defaults") ) ) {
#endif
  case KMessageBox::Yes :
    if( desktop_sess == "trinity" )
      system("tdesudo --comment \"Please enter your password for verification:\" -d --noignorebutton \"ctrl-autologin --enable\"");
    if( desktop_sess == "plasma" )
      system("tdesudo --comment \"Please enter your password for verification:\" -d --noignorebutton \"ctrl-autologin --enable\" \"\" \"\" \"plasma.desktop\"");
    if( system("sudo -n echo") == 0 )
      KMessageBox::information( this, i18n("<p>Automatic login is now enabled.</p>"), i18n("Automatic login") );
    break;
  case KMessageBox::No :
    system("tdesudo --comment \"Please enter your password for verification:\" -d --noignorebutton \"ctrl-autologin --disable\"");
    if( system("sudo -n echo") == 0 )
      KMessageBox::information( this, i18n("<p>Automatic login is now disabled.</p>"), i18n("Automatic login") );
    break;
  default:
    break;
  }
//  mw->show();
}
//---------------------------------------------------------------------------
void TForm1::action_hw_info()
{
//  TQString cmd1 = "/opt/trinity/bin/konsole --title \""+ i18n("Hardware info") + "\" --caption \"\" --icon hwinfo --geometry 1260x400 --noclose -e inxi -F &";
  TQString cmd1 = hwinfo_cmd + " &";
  system(cmd1.latin1());
}
//---------------------------------------------------------------------------
void TForm1::action_open_patreon()
{
  //mw->hide();
  TQString cmd1;
  const TQString patreon_page = "https://www.patreon.com/join/q4os";
  const TQString browser = get_default_browser();
  if( (desktop_sess == "trinity") && (browser == "kfmclient openURL") ) {
    cmd1 = browser + " \"https://www.q4os.org/dnt_donate.html\" &"; //konqueror fails to open patreon page
  } else {
    cmd1 = browser + " \"" + patreon_page + "\" &";
  }
  system(cmd1.latin1());
  //mw->show();
}
//---------------------------------------------------------------------------
/*
void TForm1::popmenu_insert_item(TQPopupMenu *a_popmenu, TQString a_text, DQ_SLOT a_slot)
{
#ifdef CC_QT5
  a_popmenu1->addAction( a_text, this, a_slot );
#else
  a_popmenu1->insertItem( a_text, this, a_slot );
#endif
}
*/
//---------------------------------------------------------------------------
//todo: move this function to q4os-api
TQString TForm1::get_default_browser()
{
  //using command "xdg-settings get default-web-browser"
  TQString browsercmd = "";
#ifdef CC_QT5
  QProcess proc1;
  proc1.setProcessChannelMode(QProcess::MergedChannels);
  proc1.start("xdg-settings", QStringList() << "get" << "default-web-browser");
  if( ! proc1.waitForStarted() ) {} //error handling
  if( ! proc1.waitForFinished() )
      browsercmd = "";
  else
      browsercmd = proc1.readAll();
#else
  TCm2d shellcmd2;
  browsercmd = shellcmd2.getCmdOut("xdg-settings get default-web-browser");
#endif
  //browsercmd.remove('\n');
  browsercmd = browsercmd.simplifyWhiteSpace();
  qtt_debug("browsercmd: " + browsercmd);

  if(false) {}
  else if(browsercmd.contains("firefox-esr")) { //firefox-esr.desktop
    return("xdg-open"); }
  else if(browsercmd.contains("firefox")) {
    return("xdg-open"); }
  else if(browsercmd.contains("chromium")) {
    return("xdg-open"); }
  else if(browsercmd.contains("google-chrome")) {
    return("xdg-open"); }
  else if(browsercmd.contains("palemoon")) {
    return("xdg-open"); }

  //try to search for browser binary
  if(false) {}
  else if(TQFile::exists("/usr/bin/firefox")) {
    return("/usr/bin/firefox"); }
  else if(TQFile::exists("/usr/bin/firefox-esr")) {
    return("/usr/bin/firefox-esr"); }
  else if(TQFile::exists("/usr/bin/chromium")) {
    return("/usr/bin/chromium"); }
  else if(TQFile::exists("/usr/bin/google-chrome-stable")) {
    return("/usr/bin/google-chrome-stable"); }
  else if(TQFile::exists("/usr/bin/palemoon")) {
    return("/usr/bin/palemoon"); }

  if(desktop_sess == "trinity") {
    if(browsercmd.contains("konqueror")) {
      return("kfmclient openURL");
    }
    if(browsercmd.length() < 1) {
      return("kfmclient openURL");
    }
  }

  return("xdg-open");
}
//---------------------------------------------------------------------------
void TForm1::qtt_debug(const TQString printstr)
{
  if(TQString(getenv("Q4_WELCOMESCREEN_DEBUG")) == "1") {
#ifdef CC_QT5
    qDebug() << printstr.toLatin1();
#else
    tqDebug(printstr.latin1());
#endif
  }
}
