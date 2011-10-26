//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу UPrintDocs програми нарахування зарплати
//
// Створений програмістами Компанії "Утех" 17.07.2007р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UPrintDocsTemplates.h"

#include "../engine/UPopulateTextTableCells.h"

//--------------------utech--------------------utech--------------------utech--------------------
UPrintDocsTemplates::UPrintDocsTemplates()
{
	monthList 	<< "січень"
				<< "лютий"
				<< "березень"
				<< "квітень"
				<< "травень"
				<< "червень"
				<< "липень"
				<< "серпень"
				<< "вересень"
				<< "жовтень"
				<< "листопад"
				<< "грудень";
	monthListRod 	<< "січня"
				<< "лютого"
				<< "березня"
				<< "квітня"
				<< "травня"
				<< "червня"
				<< "липня"
				<< "серпня"
				<< "вересня"
				<< "жовтня"
				<< "листопада"
				<< "грудня";
}
//--------------------utech--------------------utech--------------------utech--------------------
QTextDocumentFragment UPrintDocsTemplates::createPlatijkaFragment(UPlatijkyInfo p, QTextFormat::PageBreakFlag pageBrake)
{
	QTextDocument * doc = new QTextDocument();
	QTextCursor cursor(doc), cellCursor;
	QTextBlockFormat blockFormat;
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	QTextTable *table;

	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_bu;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignBottom);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignBottom);
	textCharFormat.setFontPointSize( 12 );
	textCharFormat_bold.setFontPointSize( 12 );
	textCharFormat_bu = textCharFormat_bold;
	textCharFormat_bu.setFontUnderline(true);
	
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.setBlockFormat( blockFormat );
	
	//Створення таблиці для надпису 0410001
	constraints << QTextLength(QTextLength::FixedLength, 100);
	
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setBorder(1);
	tableFormat.setBorderBrush(QBrush(Qt::black));
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(2);
	tableFormat.setAlignment(Qt::AlignRight);
	table = cursor.insertTable(1, 1, tableFormat);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	cell = table->cellAt(0, 0);
	cell.setFormat(textCharFormat);
	cellCursor = cell.firstCursorPosition();
	blockFormat.setAlignment( Qt::AlignCenter );
	cellCursor.setBlockFormat( blockFormat );
	cellCursor.insertText("0410001",textCharFormat);
	cursor.movePosition(QTextCursor::End);
	
	blockFormat.setAlignment( Qt::AlignHCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertText("ПЛАТІЖНЕ  ДОРУЧЕННЯ № "+p.platijkaNum, textCharFormat);
	blockFormat.setAlignment( Qt::AlignHCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertText("від \""+QString::number(p.date.day()).leftJustified(2,'0')+"\" "+monthListRod.at(p.date.month()-1)+" "+QString::number(p.date.year())+"р.", textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.insertBlock(blockFormat);
	cursor.insertText("Одержано банком", textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertText("\"____\"___________"+QString::number(p.date.year())+"р.", textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//Створення таблиці для основної інформації платіжки
	constraints.clear();
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 110);
	constraints << QTextLength(QTextLength::FixedLength, 180);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 20);
	constraints << QTextLength(QTextLength::FixedLength, 130);
	constraints << QTextLength(QTextLength::FixedLength, 110);
	
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setBorder(0);
	tableFormat.setBorderBrush(QBrush(Qt::lightGray));
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(0);
	tableFormat.setAlignment(Qt::AlignLeft);
	table = cursor.insertTable(9, 7, tableFormat);
	UPopulateCell tableCell(table);
	
	tableCell.setBlockMargin(1, 0, 1, 0);
	
	textCharFormat.setFontPointSize( 11 );
	textCharFormat_bold.setFontPointSize( 11 );
	textCharFormat_bu.setFontPointSize( 11 );
	//Платник
	table->mergeCells(0,0,1,7);
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(0,0,"Платник: ", textCharFormat);
	tableCell.insertText(p.platnyk, textCharFormat_bold);
	
	//Код ЄДРПОУ
	table->mergeCells(1,2,1,5);
	tableCell.set(1,0,"Код: ", textCharFormat);
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.setFrameFormat(1, Qt::black, QTextFrameFormat::BorderStyle_Solid);
	tableCell.setWithFrame(1,1,p.platnykEdrpou, textCharFormat_bold);
	
	//Банк Платника
	table->mergeCells(2,0,2,3);
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(2,0,"Банк платника\n", textCharFormat);
	tableCell.insertText(p.platnykBank, textCharFormat_bu);
	
	//Код банку
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(2,3,"Код банку", textCharFormat);
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.setWithFrame(3,3,p.platnykMFO, textCharFormat_bold);
	
	//ДЕБЕТ рах. №
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(2,5,"ДЕБЕТ рах. №", textCharFormat);
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.setWithFrame(3,5,p.platnykRahunok, textCharFormat_bold);
	
	//Сума
	table->mergeCells(3,6,6,1);
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(2,6,"Сума", textCharFormat);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignBottom);
	tableCell.setWithFrame(3,6,"\n\n\n"+m_to_str_2(p.suma)+"\n\n\n", textCharFormat_bold);
	
	//Отримувач
	table->mergeCells(5,0,1,6);
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(5,0,"Отримувач: ", textCharFormat);
	tableCell.insertText(p.oderjuvach, textCharFormat_bold);
	
	//Код ЄДРПОУ
	table->mergeCells(6,2,1,4);
	tableCell.set(6,0,"Код: ", textCharFormat);
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.setWithFrame(6,1,p.oderjuvachEdrpou, textCharFormat_bold);
	
	//Банк Одержувача
	table->mergeCells(7,0,2,3);
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(7,0,"Банк отримувача\n", textCharFormat);
	tableCell.insertText(p.oderjuvachBank, textCharFormat_bu);
	
	//Код банку
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(7,3,"Код банку", textCharFormat);
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.setWithFrame(8,3,p.oderjuvachMFO, textCharFormat_bold);
	
	//ДЕБЕТ рах. №
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(7,5,"КРЕДИТ рах. №", textCharFormat);
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.setWithFrame(8,5,p.oderjuvachRahunok, textCharFormat_bold);
	
	cursor.movePosition(QTextCursor::End);
	
	cursor.insertBlock(blockFormat);
	
	//Сума словами
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertText("Сума словами: ", textCharFormat);
	cursor.insertText(numberToString(m_to_str_2(p.suma)), textCharFormat_bold);
	 
	//Призначення платежу:
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertText("Призначення платежу: ", textCharFormat);
	cursor.insertText(p.pryznachennyaPlateju, textCharFormat_bold);
	
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//Створення таблиці для підписів і печатки
	constraints.clear();
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 110);
	constraints << QTextLength(QTextLength::FixedLength, 220);
	constraints << QTextLength(QTextLength::FixedLength, 300);

	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setBorder(0);
	tableFormat.setBorderBrush(QBrush(Qt::white));
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setAlignment(Qt::AlignLeft);
	table = cursor.insertTable(1, 4, tableFormat);
	tableCell.setTextTable(table);
	
	tableCell.setBlockMargin(1, 0, 1, 0);
	
	//Місце печатки
	tableCell.setAlignment(Qt::AlignCenter);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	tableCell.set(0,0,"М.П.\n", textCharFormat);
	
	//Підпис
	tableCell.setAlignment(Qt::AlignRight);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignBottom);
	tableCell.set(0,1,"Підписи\n\n", textCharFormat);
	
	//Лінійки для підписів
	tableCell.setAlignment(Qt::AlignLeft);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignBottom);
	tableCell.set(0,2,"____________________\n\n____________________", textCharFormat);
	
	//Проведено банком
	tableCell.setAlignment(Qt::AlignCenter);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignBottom);
	tableCell.set(0,3,"Проведено банком\n\n“____”___________200_ р.\n\nПідпис банку", textCharFormat);
	
	QTextDocumentFragment fragment(doc);
	
	cursor.movePosition(QTextCursor::End);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertHtml("<hr>");
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	cursor.insertFragment(fragment);
	QTextDocumentFragment resFragment(doc);
	
	//Створення рамки для пари платіжок і занесення туди платіжок
	doc->clear();
	constraints.clear();
	constraints << QTextLength(QTextLength::PercentageLength, 100);
	
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setBorder(0);
	tableFormat.setBorderBrush(QBrush(Qt::white));
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(0);
	tableFormat.setAlignment(Qt::AlignLeft);
	tableFormat.setPageBreakPolicy(pageBrake);
	table = cursor.insertTable(1, 1, tableFormat);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	cell = table->cellAt(0, 0);
	cell.setFormat(textCharFormat);
	cursor = cell.firstCursorPosition();
	cursor.insertFragment(resFragment);
	
	QTextDocumentFragment resultFragment(doc);
	
	delete doc;
	return resultFragment;
}
//--------------------utech--------------------utech--------------------utech--------------------
UPrintDocsTemplates::~UPrintDocsTemplates()
{

}
//--------------------utech--------------------utech--------------------utech--------------------
