//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UDebugForm.h"

//--------------------utech--------------------utech--------------------utech--------------------
UDebugForm * UDebug::debugFormPointer = NULL;

void UDebug::createDebugForm()
{
	UDebug::debugFormPointer = new UDebugForm();
	qInstallMsgHandler(uMessageOutput);
}

void UDebug::showDebug()
{
	UDebug::debugFormPointer->showDebug();
}

void UDebug::uMessageOutput(QtMsgType type, const char *msg)
{
	switch (type) {
	case QtDebugMsg:
		UDebug::debugFormPointer->addDebugString(msg);
		break;
	case QtWarningMsg:
		UDebug::debugFormPointer->addWarningString(msg);
		break;
	case QtCriticalMsg:
		UDebug::debugFormPointer->addWarningString("\nQtCriticalMsg:\n");
		UDebug::debugFormPointer->addWarningString(msg);
		break;
    case QtFatalMsg:
		UDebug::debugFormPointer->addWarningString("\nQtFatalMsg:\n");
		UDebug::debugFormPointer->addWarningString(msg);
		abort();
	}
}



//--------------------utech--------------------utech--------------------utech--------------------
UDebugForm::UDebugForm(QWidget *parent)
        : QWidget(parent)
{
    ui.setupUi(this);
	
	connect(ui.pushButton_clear, SIGNAL(clicked ()), this, SLOT(clearActiveMessageTextEdit()));
	connect(ui.pushButton_close, SIGNAL(clicked ()), this, SLOT(hide()));
	connect(ui.checkBox_allWaysOnTop, SIGNAL(stateChanged(int)), this, SLOT(checkBox_allWaysOnTop_stateChanged()));
}
//-----slots-------------------------------------------------
void UDebugForm::addString(QString str)
{
	ui.textEditDebugInfo->append(str);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDebugForm::addDebugString(QString str)
{
	ui.textEditDebugInfo->append(str);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDebugForm::addWarningString(QString str)
{
	ui.textEditWarningInfo->append(str);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDebugForm::clearActiveMessageTextEdit()
{
	switch (ui.toolBox->currentIndex()){
		case 0:	ui.textEditDebugInfo->clear();
				break;
		case 1:	ui.textEditWarningInfo->clear();
				break;
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDebugForm::showDebug()
{
	hide();
	show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDebugForm::checkBox_allWaysOnTop_stateChanged()
{
	if (ui.checkBox_allWaysOnTop->isChecked()){
		setWindowFlags( this->windowFlags() | Qt::WindowStaysOnTopHint);
		show();
	}
	else{
		setWindowFlags( windowFlags() & (~Qt::WindowStaysOnTopHint));
		show();
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
UDebugForm::~UDebugForm()
{

}
//--------------------utech--------------------utech--------------------utech--------------------

