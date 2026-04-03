//---------------------------------------------------------------------------
#ifndef FORM2_H
#define FORM2_H
//---------------------------------------------------------------------------
// Checking names of source files. You can safely remove this section after successfull compilation.
#define TEST1_TForm_ui_form2
#ifdef TEST1_TForm_form2
#error Using Trinity-TQT you should name your class files *.h/cpp other then *.ui files. The best way is to name the .ui file with some prefix, ie "ui_myform.ui" and class file: "myform.cpp" to avoid such conflicts.
#endif
//---------------------------------------------------------------------------
#include "ui_form2.h"
//---------------------------------------------------------------------------
//class TQWidget;
//---------------------------------------------------------------------------
/**
 * @short Form2
 * @author $AUTHOR$ <$EMAIL$>
 * @version $VERSION$
 */
//---------------------------------------------------------------------------
class TForm2 : public TForm_ui_form2
{
    TQ_OBJECT

public:
    /*$PUBLIC_FUNCTIONS$*/
    /**
     * Default Constructor
     */
    TForm2( TQWidget* parent = 0, const char* name = 0, WFlags fl = 0 );

    /**
     * Default Destructor
     */
    ~TForm2();

public slots:
    /*$PUBLIC_SLOTS$*/

protected:
    /*$PROTECTED_FUNCTIONS$*/

protected slots:
    /*$PROTECTED_SLOTS$*/

private slots:
    /*$PRIVATE_SLOTS$*/
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

