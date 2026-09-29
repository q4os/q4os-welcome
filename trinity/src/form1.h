//---------------------------------------------------------------------------
#ifndef FORM1_H
#define FORM1_H
//---------------------------------------------------------------------------
#include "ui_form1.h"
#include <ws_actions.h>
//---------------------------------------------------------------------------
class TQPopupMenu;
class TQWidget;
//---------------------------------------------------------------------------
/**
 * @short Form1 - the Welcome screen: the intro, the six buttons and the "More options" menu
 * @author $AUTHOR$ <$EMAIL$>
 * @version $VERSION$
 */
//---------------------------------------------------------------------------
class TForm1 : public TForm_ui_form1
{
    TQ_OBJECT

public:
    TForm1( TQWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~TForm1();

private:
    bool check_desktop_session();
    void action_screen_scaling();
    void action_desktop_effects();
    void action_switch_startmenu();
    void action_autologin();
    void action_hw_info();
    TQWidget *mw;
    WsSystem sys; //what shared/ws_actions probed about this system
    TQPopupMenu *popmenu1;

private slots:
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
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif // FORM1_H
//---------------------------------------------------------------------------
