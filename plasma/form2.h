//---------------------------------------------------------------------------
#ifndef FORM2_H
#define FORM2_H
//---------------------------------------------------------------------------
#include "ws_tr.h" //before the uic header, it calls wsTr()
#include "ui_form2.h"

#include <QDialog>
//---------------------------------------------------------------------------
//the older start menu dialog (three buttons); the window uses Form3 today, this one is kept - the
//same as TForm2 of the Trinity frontend
class TForm2 : public QDialog, private Ui::TForm_ui_form2
{
    Q_OBJECT
public:
    TForm2( QWidget* parent = nullptr );
    ~TForm2();
private slots:
    void pushButton1_clicked();
    void pushButton2_clicked();
    void pushButton3_clicked();
    void pushButton4_clicked();
};
//---------------------------------------------------------------------------
extern TForm2 *Form2;
//---------------------------------------------------------------------------
#endif // FORM2_H
//---------------------------------------------------------------------------
