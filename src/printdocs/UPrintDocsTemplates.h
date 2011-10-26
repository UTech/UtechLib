//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу UPrintDocs програми нарахування зарплати
//
// Створений програмістами Компанії "Утех" 17.07.2007р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UPRINTDOCS_H
#define UPRINTDOCS_H

#include <QString>
#include <QVariant>
#include <QTextLength>
#include <QTextTable>
#include <QDate>
#include <QTextTableCell>
#include <QTextCursor>
#include <QMessageBox>
#include <QTextDocumentFragment>
#include <QTextFrameFormat>
#include "../gui/UPrintForm.h"
#include "../engine/UMath.h"
#include "../numberToStrConverter/UNumberToStringConverter.h"
//--------------------utech--------------------utech--------------------utech--------------------
struct UPlatijkyInfo
{
	QDate		date;
	QString		oderjuvach;
	QString		oderjuvachEdrpou;
	QString		oderjuvachBank;
	QString		oderjuvachMFO;
	QString		oderjuvachRahunok;
	QString		oderjuvachAdresa;
	QString		oderjuvachTel;
	QString		oderjuvachFax;
	QString		oderjuvachEmail;
	QString		pryznachennyaPlateju;
	QString		oderjuvachIPN;
	QString		oderjuvachSvidPDVNum;
	double		suma;
	QString		platnyk;
	QString		platnykEdrpou;
	QString		platnykBank;
	QString		platnykMFO;
	QString		platnykRahunok;
	QString		platijkaNum;
	QString		platnykAdresa;
	QString		platnykTel;
	QString		platnykFax;
	QString		platnykEmail;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UPrintDocsTemplates
{
    public:
        UPrintDocsTemplates();
		~UPrintDocsTemplates();
		QTextDocumentFragment createPlatijkaFragment(UPlatijkyInfo p, QTextFormat::PageBreakFlag pageBrake = QTextFormat::PageBreak_Auto);
		
		UPrintForm *printform;
    private:
		QStringList monthList;
		QStringList monthListRod;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
