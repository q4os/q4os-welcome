//---------------------------------------------------------------------------
#ifndef FORM1_H
#define FORM1_H
//---------------------------------------------------------------------------
#include "ws_tr.h" //before the uic header, it calls wsTr()
#include "ui_form1.h"
#include <ws_actions.h>

#include <QWidget>
//---------------------------------------------------------------------------
class QMenu;
//---------------------------------------------------------------------------
//the Welcome screen: the intro, the six buttons and the "More options" menu - the same form and
//behaviour as TForm1 of the Trinity frontend (trinity/src/form1.cpp)
class TForm1 : public QWidget, private Ui::TForm_ui_form1
{
    Q_OBJECT

public:
    TForm1( QWidget* parent = nullptr );
    ~TForm1();

private:
    bool check_desktop_session();
    void action_screen_scaling();
    void action_desktop_effects();
    void action_switch_startmenu();
    void action_autologin();
    void action_hw_info();
    QWidget *mw;
    WsSystem sys; //what shared/ws_actions probed about this system
    QMenu *popmenu1;

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
//---------------------------------------------------------------------------
#endif // FORM1_H
//---------------------------------------------------------------------------
