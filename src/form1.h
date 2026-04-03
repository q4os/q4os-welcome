//---------------------------------------------------------------------------
#ifndef FORM1_H
#define FORM1_H
//---------------------------------------------------------------------------
//#define CC_QT5
//---------------------------------------------------------------------------
#include "ui_form1.h"
//---------------------------------------------------------------------------
class TQPopupMenu;
class TQWidget;
//---------------------------------------------------------------------------
/**
 * @short Form1
 * @author $AUTHOR$ <$EMAIL$>
 * @version $VERSION$
 */
//---------------------------------------------------------------------------
#ifdef CC_QT5
class_qt5 TForm1 : public QWidget, private Ui::TForm_ui_form1
#else
class TForm1 : public TForm_ui_form1
#endif
{
    TQ_OBJECT

public:
    /*$PUBLIC_FUNCTIONS$*/
    /**
     * Default Constructor
     */
#ifdef CC_QT5
    TForm1( QWidget* parent = 0, Qt::WindowFlags fl = 0 );
#else
    TForm1( TQWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
#endif

    /**
     * Default Destructor
     */
    ~TForm1();

//    int check_ws_env();

public slots:
    /*$PUBLIC_SLOTS$*/

protected:
    /*$PROTECTED_FUNCTIONS$*/

protected slots:
    /*$PROTECTED_SLOTS$*/

private:
//    void on_vboxgutils_action();
    bool check_vboxgutils();
    bool check_desktop_session();
//    bool check_swprofiler_processed();
    bool check_hw();
    void action_screen_scaling();
    void action_desktop_effects();
    void action_switch_startmenu();
    void action_autologin();
    void action_hw_info();
    void action_open_patreon();
    //void popmenu_insert_item(TQPopupMenu *a_popmenu, TQString a_text, SLOT a_slot);
    TQString get_default_browser();
    void qtt_debug(const TQString);
    TQWidget *mw;
    TQString dpkg_arch;
    TQString desktop_sess;
    TQString qaptdistr;
    bool is_quarkos = false;
    bool swap_button4 = false; //swap button "switch start menu" to "hardware info" for plasma desktop
    long int phmemsize;
//    bool sse2_ok;
    TQString hwinfo_cmd;
    TQPopupMenu *popmenu1;

private slots:
    /*$PRIVATE_SLOTS$*/
    void button1_click();
    void button2_click();
    void button3_click();
    void button4_click();
    void button5_click();
    void button6_click();
    void button20_click();
    void slot1();
    void slot2();
    void slot3();
    void slot4();
    void slot5();
    //void slot6();
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif // FORM1_H
//---------------------------------------------------------------------------
