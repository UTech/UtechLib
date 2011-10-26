//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу UPrintDocs програми нарахування зарплати
//
// Створений програмістами Компанії "Утех" 17.07.2007р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UPOPULATETEXTTABLECELLES_H
#define UPOPULATETEXTTABLECELLES_H

#include <QString>
#include <QVariant>
#include <QTextCodec>
#include <QTextLength>
#include <QTextTable>
#include <QDate>
#include <QTextTableCell>
#include <QTextCursor>

//--------------------utech--------------------utech--------------------utech--------------------
class UPopulateTextTableCells
{
	public:
		UPopulateTextTableCells(QTextTable * textTable);
		QTextCharFormat curTextCharFormat();
		QTextCursor cursor();
		void setTextTable(QTextTable *textTable);
		void setTextCharFormat(QTextCharFormat textCharFormat);
		void setAlignment(Qt::Alignment textAlihnment);
		void setAlignment(Qt::Alignment textAlihnment, bool forCurrent);
		void setTextBlockFormat(QTextBlockFormat textBlockFormat);
		void setBlockMargin(qreal left, qreal top, qreal right, qreal bottom);
		void setFrameFormat(qreal border, QColor borderColor, QTextFrameFormat::BorderStyle style);
		void set(int row, int col, QString text, QTextCharFormat charFormat);
		void set(int row, int col, QString text);
		void set(int row, int col, double d_val, QTextCharFormat charFormat);
		void set(int row, int col, double d_val);
		void set(int row, int col, int i_val, QTextCharFormat charFormat);
		void set(int row, int col, int i_val);
		void set(int row, int col, const QImage & img, QTextCharFormat charFormat);
		void set(int row, int col, const QImage & img);
		void setDash(int row, int col, int i_val, QTextCharFormat charFormat);
		void setDash(int row, int col, int i_val);
		void setDash(int row, int col, double d_val, QTextCharFormat charFormat);
		void setDash(int row, int col, double d_val);
		void setDash(int row, int col, QTime time, QTextCharFormat charFormat);
		void setDash(int row, int col, QTime time);
		void insertText(QString text, QTextCharFormat charFormat);
		void insertText(QString text);
		void insertText(double d_val, QTextCharFormat charFormat);
		void insertText(double d_val);
		void insertText(int i_val, QTextCharFormat charFormat);
		void insertText(int i_val);
		void insertImage(QImage img);
		void setWithFrame(int row, int col, QString text, QTextCharFormat charFormat);
		
	private:
		QTextTable *__textTable;
		QTextCharFormat __textCharFormat;
		Qt::Alignment __textAlihnment;
		QTextBlockFormat __textBlockFormat;
		QTextFrameFormat __textFrameFormat;
		
		QTextTableCell cell;
		QTextCursor cellCursor;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UPopulateCell : public UPopulateTextTableCells{
  public:
	UPopulateCell(QTextTable * textTable): UPopulateTextTableCells(textTable){};
};

#endif
