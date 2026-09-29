//---------------------------------------------------------------------------
#ifndef FORM3_H
#define FORM3_H
//---------------------------------------------------------------------------
#include "ws_tr.h" //before the uic header, it calls wsTr()
#include "ui_form3.h"

#include <QDialog>
//---------------------------------------------------------------------------
//the start menu dialog: structure (Q4OS / TDE) and type (Kickoff / Bourbon / Classic) - the same
//as TForm3 of the Trinity frontend; Trinity sessions only
class TForm3 : public QDialog, private Ui::TForm_ui_form3
{
    Q_OBJECT
public:
    TForm3( QWidget* parent = nullptr );
    ~TForm3();
private slots:
    void pushButton1_clicked();
    void pushButton4_clicked();
};
//---------------------------------------------------------------------------
extern TForm3 *Form3;
//---------------------------------------------------------------------------
#endif // FORM3_H
//---------------------------------------------------------------------------
