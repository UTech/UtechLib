//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу UPrintDocs програми нарахування зарплати
//
// Створений програмістами Компанії "Утех" 17.07.2007р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UPopulateTextTableCells.h"

//--------------------utech--------------------utech--------------------utech--------------------
UPopulateTextTableCells::UPopulateTextTableCells(QTextTable * textTable){
	__textTable = textTable;
}

QTextCharFormat UPopulateTextTableCells::curTextCharFormat(){
	return __textCharFormat;
}

QTextCursor UPopulateTextTableCells::cursor()
{
	return cellCursor;
}

void UPopulateTextTableCells::setTextTable(QTextTable *textTable){
	__textTable = textTable;
}

void UPopulateTextTableCells::setTextCharFormat(QTextCharFormat textCharFormat){
	__textCharFormat = textCharFormat;
}

void UPopulateTextTableCells::setAlignment(Qt::Alignment textAlihnment){
	__textAlihnment = textAlihnment;
}

void UPopulateTextTableCells::setAlignment(Qt::Alignment textAlihnment, bool forCurrent){
	__textAlihnment = textAlihnment;
	if (forCurrent) {
		__textBlockFormat.setAlignment( __textAlihnment );
		cellCursor.setBlockFormat( __textBlockFormat );
	}
}

void UPopulateTextTableCells::setTextBlockFormat(QTextBlockFormat textBlockFormat){
	__textBlockFormat = textBlockFormat;
}

void UPopulateTextTableCells::setBlockMargin(qreal left, qreal top, qreal right, qreal bottom){
	__textBlockFormat.setLeftMargin(left);
	__textBlockFormat.setTopMargin(top);
	__textBlockFormat.setRightMargin(right);
	__textBlockFormat.setBottomMargin(bottom);
}

void UPopulateTextTableCells::setFrameFormat(qreal border, QColor borderColor, QTextFrameFormat::BorderStyle style){
	__textFrameFormat.setBorder( border );
	__textFrameFormat.setBorderBrush( QBrush(borderColor) );
	__textFrameFormat.setBorderStyle( style );
}

void UPopulateTextTableCells::set(int row, int col, QString text, QTextCharFormat charFormat){
	cell = __textTable->cellAt(row, col);
	cell.setFormat(charFormat);
	cellCursor = cell.firstCursorPosition();
	__textBlockFormat.setAlignment( __textAlihnment );
	cellCursor.setBlockFormat( __textBlockFormat );
	cellCursor.insertText(text,charFormat);
}

void UPopulateTextTableCells::set(int row, int col, QString text){
	set(row,col,text,__textCharFormat);
}

void UPopulateTextTableCells::set(int row, int col, double d_val, QTextCharFormat charFormat){
	set(row, col, QString::number(d_val,'f',2).replace('.',','),charFormat);
}

void UPopulateTextTableCells::set(int row, int col, double d_val){
	set(row,col,QString::number(d_val,'f',2).replace('.',','),__textCharFormat);
}

void UPopulateTextTableCells::set(int row, int col, int i_val, QTextCharFormat charFormat){
	set(row, col, QString::number(i_val),charFormat);
}

void UPopulateTextTableCells::set(int row, int col, int i_val){
	set(row,col,QString::number(i_val),__textCharFormat);
}

void UPopulateTextTableCells::set(int row, int col, const QImage & img, QTextCharFormat charFormat)
{
	cell = __textTable->cellAt(row, col);
	cell.setFormat(charFormat);
	cellCursor = cell.firstCursorPosition();
	__textBlockFormat.setAlignment( __textAlihnment );
	cellCursor.setBlockFormat( __textBlockFormat );
	cellCursor.insertImage(img);
}

void UPopulateTextTableCells::set(int row, int col, const QImage & img)
{
	set(row, col, img, __textCharFormat);
}

void UPopulateTextTableCells::setDash(int row, int col, int i_val, QTextCharFormat charFormat){
	if (i_val != 0)
		set(row,col,QString::number(i_val),charFormat);
	else
		set(row,col,"-",charFormat);
}

void UPopulateTextTableCells::setDash(int row, int col, int i_val){
	if (i_val != 0)
		set(row,col,QString::number(i_val),__textCharFormat);
	else
		set(row,col,"-",__textCharFormat);
}

void UPopulateTextTableCells::setDash(int row, int col, double d_val, QTextCharFormat charFormat){
	if (d_val != 0)
		set(row, col, QString::number(d_val,'f',2).replace('.',','),charFormat);
	else
		set(row, col, "-",charFormat);
}

void UPopulateTextTableCells::setDash(int row, int col, double d_val){
	if (d_val != 0)
		set(row,col,QString::number(d_val,'f',2).replace('.',','),__textCharFormat);
	else
		set(row,col,"-",__textCharFormat);
}

void UPopulateTextTableCells::setDash(int row, int col, QTime time, QTextCharFormat charFormat)
{
	if (time.isValid() && time>QTime(0,0))
		set(row, col, time.toString("h:mm"),charFormat);
	else
		set(row, col, "-",charFormat);
}

void UPopulateTextTableCells::setDash(int row, int col, QTime time)
{
	if (time.isValid() && time>QTime(0,0))
		set(row, col, time.toString("h:mm"),__textCharFormat);
	else
		set(row, col, "-",__textCharFormat);
}

void UPopulateTextTableCells::insertText(QString text, QTextCharFormat charFormat)
{
	cellCursor.insertText(text,charFormat);
}

void UPopulateTextTableCells::insertText(QString text)
{
	insertText(text,__textCharFormat);
}

void UPopulateTextTableCells::insertText(double d_val, QTextCharFormat charFormat)
{
	cellCursor.insertText(QString::number(d_val,'f',2).replace('.',','),charFormat);
}

void UPopulateTextTableCells::insertText(double d_val)
{
	insertText(d_val,__textCharFormat);
}

void UPopulateTextTableCells::insertText(int i_val, QTextCharFormat charFormat)
{
	cellCursor.insertText(QString::number(i_val),charFormat);
}

void UPopulateTextTableCells::insertText(int i_val)
{
	insertText(i_val,__textCharFormat);
}

void UPopulateTextTableCells::insertImage(QImage img)
{
	cellCursor.insertImage(img);
}

void UPopulateTextTableCells::setWithFrame(int row, int col, QString text, QTextCharFormat charFormat){
	cell = __textTable->cellAt(row, col);
	cell.setFormat(charFormat);
	cellCursor = cell.firstCursorPosition();
	__textBlockFormat.setAlignment( __textAlihnment );
	cellCursor.setBlockFormat( __textBlockFormat );
	//cellCursor.insertFrame(__textFrameFormat);
	
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::PercentageLength, 100);
	
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setBorder(1);
	tableFormat.setBorderBrush(QBrush(Qt::black));
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(0);
	tableFormat.setAlignment(Qt::AlignRight);
	QTextTable *table = cellCursor.insertTable(1, 1, tableFormat);
	
	QTextBlockFormat blockFormat;
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	cell = table->cellAt(0, 0);
	cell.setFormat(charFormat);
	cellCursor = cell.firstCursorPosition();
	blockFormat.setAlignment( Qt::AlignCenter );
	cellCursor.setBlockFormat( blockFormat );
	cellCursor.insertText(text,charFormat);
}
//--------------------utech--------------------utech--------------------utech--------------------
