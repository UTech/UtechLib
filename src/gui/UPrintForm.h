//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UPRINTFORM_H
#define UPRINTFORM_H

#include <QWidget>
#include <QtDebug>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>

#include "../ui_headers/ui_UPrintForm.h"

//--------------------utech--------------------utech--------------------utech--------------------
class UPrintForm : public QWidget
{
        Q_OBJECT

    public:
        UPrintForm(QWidget *parent = 0, QString title = "", bool fullPage=false);
		UPrintForm(QString title = "", QSizeF dSize=QSize(-1,-1), QWidget *parent = 0);
		UPrintForm(QString title, int left, int top, int right, int bottom, QWidget *parent = 0);
		QTextDocument *document();
		QPrinter *printer();
		
		virtual ~UPrintForm();
    public slots:
		void printDoc();
		void printDocOn();
		void showPreview();
		void exportPdf();
		void closePrinform();
		void printPreview(QPrinter * printer);
    protected:
		Ui::UPrintForm ui;
		QTextDocument *doc;
		QPrinter *prnt;
		bool userSize;
		QSizeF docSize;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
