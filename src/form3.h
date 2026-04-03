//---------------------------------------------------------------------------
#ifndef FORM3_H
#define FORM3_H
//---------------------------------------------------------------------------
// Checking names of source files. You can safely remove this section after successfull compilation.
#define TEST1_TForm_ui_form3
#ifdef TEST1_TForm_form3
#error Using Trinity-TQT you should name your class files *.h/cpp other then *.ui files. The best way is to name the .ui file with some prefix, ie "ui_myform.ui" and class file: "myform.cpp" to avoid such conflicts.
#endif
//---------------------------------------------------------------------------
#include "ui_form3.h"
//---------------------------------------------------------------------------
//class TQDialog;
//---------------------------------------------------------------------------
/**
 * @short Form3
 * @author $AUTHOR$ <$EMAIL$>
 * @version $VERSION$
 */
//---------------------------------------------------------------------------
class TForm3 : public TForm_ui_form3
{
    TQ_OBJECT

public:
    /*$PUBLIC_FUNCTIONS$*/
    /**
     * Default Constructor
     */
    TForm3( TQWidget* parent = 0, const char* name = 0, WFlags fl = 0 );

    /**
     * Default Destructor
     */
    ~TForm3();

public slots:
    /*$PUBLIC_SLOTS$*/

protected:
    /*$PROTECTED_FUNCTIONS$*/

protected slots:
    /*$PROTECTED_SLOTS$*/

private slots:
    /*$PRIVATE_SLOTS$*/
    void pushButton1_clicked();
//    void pushButton2_clicked();
//    void pushButton3_clicked();
    void pushButton4_clicked();
};
//---------------------------------------------------------------------------
extern TForm3 *Form3;
//---------------------------------------------------------------------------
#endif // FORM3_H
//---------------------------------------------------------------------------

