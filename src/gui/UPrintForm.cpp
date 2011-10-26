//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include <QFileDialog>
#include <QFileInfo>

#include "UPrintForm.h"

//------------------------------------------------------------
UPrintForm::UPrintForm(QWidget *parent, QString title, bool fullPage)
        : QWidget(parent)
{
    ui.setupUi(this);
	userSize = fullPage;
	
	doc = ui.textEdit->document();
	prnt = new QPrinter();
	if (userSize)
		prnt->setPageMargins ( 5, 4, 2, 1, QPrinter::Millimeter );
	else
		prnt->setPageMargins ( 10, 10, 10, 10, QPrinter::Millimeter );
	
	setWindowTitle( ui.textEdit->parentWidget()->windowTitle() + title);
	
	connect(ui.pushButton_cancel, SIGNAL(clicked ()), this, SLOT(closePrinform()));
	connect(ui.pushButton_print, SIGNAL(clicked ()), this, SLOT(printDoc()));
	connect(ui.pushButton_print_on, SIGNAL(clicked ()), this, SLOT(printDocOn()));
	connect(ui.pushButton_printPreview, SIGNAL(clicked()), this, SLOT(showPreview()));
	connect(ui.pushButton_exportInPdf, SIGNAL(clicked()), this, SLOT(exportPdf()));
}
//------------------------------------------------------------
UPrintForm::UPrintForm(QString title, QSizeF dSize, QWidget *parent)
        : QWidget(parent)
{
	ui.setupUi(this);
	
	docSize = dSize;
	if (docSize.isValid())
		userSize = true;
	else
		userSize = false;
	
	if (userSize)
		doc->setPageSize(docSize);
	
	prnt = new QPrinter();
	prnt->setPageMargins ( 4, 3, 4, 7, QPrinter::Millimeter );
	
	setWindowTitle( ui.textEdit->parentWidget()->windowTitle() + title);
	
	connect(ui.pushButton_cancel, SIGNAL(clicked ()), this, SLOT(closePrinform()));
	connect(ui.pushButton_print, SIGNAL(clicked ()), this, SLOT(printDoc()));
	connect(ui.pushButton_print_on, SIGNAL(clicked ()), this, SLOT(printDocOn()));
	connect(ui.pushButton_printPreview, SIGNAL(clicked()), this, SLOT(showPreview()));
	connect(ui.pushButton_exportInPdf, SIGNAL(clicked()), this, SLOT(exportPdf()));
}
//------------------------------------------------------------
UPrintForm::UPrintForm(QString title, int left, int top, int right, int bottom, QWidget *parent)
        : QWidget(parent)
{
	ui.setupUi(this);
	
	userSize = false;
	prnt = new QPrinter();
	prnt->setPageMargins ( left, top, right, bottom, QPrinter::Millimeter );
	
	setWindowTitle( ui.textEdit->parentWidget()->windowTitle() + title);
	
	connect(ui.pushButton_cancel, SIGNAL(clicked ()), this, SLOT(closePrinform()));
	connect(ui.pushButton_print, SIGNAL(clicked ()), this, SLOT(printDoc()));
	connect(ui.pushButton_print_on, SIGNAL(clicked ()), this, SLOT(printDocOn()));
	connect(ui.pushButton_printPreview, SIGNAL(clicked()), this, SLOT(showPreview()));
	connect(ui.pushButton_exportInPdf, SIGNAL(clicked()), this, SLOT(exportPdf()));
}
//------------------------------------------------------------
QTextDocument *UPrintForm::document()
{
	return ui.textEdit->document();
}
//-----slots-------------------------------------------------
void UPrintForm::printDoc()
{
	doc = ui.textEdit->document();
	doc->print(prnt);
}
//------------------------------------------------------------
void UPrintForm::printDocOn()
{
	doc = ui.textEdit->document();
	QPrintDialog *dlg = new QPrintDialog(prnt, this);
	if (dlg->exec() != QDialog::Accepted)
		return;
	doc->print(prnt);
}
//------------------------------------------------------------
void UPrintForm::showPreview()
{
	QPrintPreviewDialog preview(prnt, this);
	connect(&preview, SIGNAL(paintRequested(QPrinter *)), this, SLOT(printPreview(QPrinter *)));
	preview.exec();
}
//------------------------------------------------------------
void UPrintForm::exportPdf()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Експорт в pdf формат", prnt->docName(), "*.pdf");
	if (!fileName.isEmpty()) {
		if (QFileInfo(fileName).suffix().isEmpty())
			fileName.append(".pdf");
		prnt->setOutputFormat(QPrinter::PdfFormat);
		prnt->setOutputFileName(fileName);
		ui.textEdit->document()->print(prnt);
		
		prnt->setOutputFileName(0);
		prnt->setOutputFormat(QPrinter::NativeFormat);
	}
}
//------------------------------------------------------------
void UPrintForm::printPreview(QPrinter * printer)
{
	ui.textEdit->print(prnt);
}
//------------------------------------------------------------
void UPrintForm::closePrinform()
{
	close();
}
//------------------------------------------------------------
QPrinter *UPrintForm::printer()
{
	return prnt;
}
//------------------------------------------------------------
UPrintForm::~UPrintForm()
{
	delete prnt;
}
//------------------------------------------------------------
