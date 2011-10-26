//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу UPostupForm програми нарахування зарплати
//
// Створений програмістами Компанії "Утех" 17.07.2007р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UPostupForm.h"

//--------------------utech--------------------utech--------------------utech--------------------
UPostupForm::UPostupForm(QWidget *parent, int count)
        : QWidget(parent)
{
    ui.setupUi(this);
	ui.labelPostup->setVisible(false);
	
	ui.progressBar->setMinimum ( 0 );
	ui.progressBar->setMaximum ( count );
	ui.progressBar->setValue(0);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPostupForm::incPos()
{
	ui.progressBar->setValue(ui.progressBar->value()+1);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPostupForm::inc_pos()
{
	incPos();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPostupForm::showLable(bool b)
{
	ui.labelPostup->setVisible(b);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPostupForm::setPostupLabel(QString label)
{
	ui.labelPostup->setText(label);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPostupForm::setNumPos(int count)
{
	ui.progressBar->setMaximum ( count );
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPostupForm::setCurrentPos(int pos)
{
	ui.progressBar->setValue(pos);
}
//--------------------utech--------------------utech--------------------utech--------------------
UPostupForm::~UPostupForm()
{

}
//--------------------utech--------------------utech--------------------utech--------------------
