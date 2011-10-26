//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UTableWidgetSqlExt.h"

#include "UStandardDelegate.h"

//--------------------utech--------------------utech--------------------utech--------------------
UTableWidgetSqlExt::UTableWidgetSqlExt(QTableWidget *tWidget, QString sqlTName, QString connectionName)
	: QObject(tWidget)
{
	uSortingEnabled = false;
	tableWidget = tWidget;
	sqlTableName = sqlTName;
	conName = connectionName;
	uDbType = dataType(conName);
	driverCanFatchLastInsertId = QSqlDatabase::database(conName).driver()->hasFeature(QSqlDriver::LastInsertId);
	
	tableWidget->setRowCount(0);
	tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	clearSqlFilter();
	clearSqlOrderBy();
}
//--------------------utech--------------------utech--------------------utech--------------------
QString UTableWidgetSqlExt::__sqlEscStr(QVariant v)
{
	QVariant::Type vType = v.type();
	switch (uDbType){
		case USql::UDB2:
			if ( (vType==QVariant::Bool) || (vType==QVariant::Double) || (vType==QVariant::Int) || (vType==QVariant::UInt)  || (vType==QVariant::ULongLong))
				return v.toString().replace(',','.');
			else
				return "'"+v.toString()+"'";
			break;
		case USql::UIBASE:
			if ( (vType==QVariant::Bool) || (vType==QVariant::Double) || (vType==QVariant::Int) || (vType==QVariant::UInt)  || (vType==QVariant::ULongLong))
				return v.toString().replace(',','.');
			else
				return "'"+v.toString()+"'";
			break;
		case USql::UMYSQL:
			if ( (vType==QVariant::Bool) || (vType==QVariant::Double) || (vType==QVariant::Int) || (vType==QVariant::UInt)  || (vType==QVariant::ULongLong))
				return v.toString().replace(',','.');
			else
				return "'"+v.toString().replace('\'',"\\\'")+"'";
			break;
		case USql::UOCI:
			if ( (vType==QVariant::Bool) || (vType==QVariant::Double) || (vType==QVariant::Int) || (vType==QVariant::UInt)  || (vType==QVariant::ULongLong))
				return v.toString().replace(',','.');
			else
				return "'"+v.toString()+"'";
			break;
		case USql::UODBC:
			if ( (vType==QVariant::Bool) || (vType==QVariant::Double) || (vType==QVariant::Int) || (vType==QVariant::UInt)  || (vType==QVariant::ULongLong))
				return v.toString().replace(',','.');
			else
				return "'"+v.toString()+"'";
			break;
		case USql::UPSQL:
			if ( (vType==QVariant::Bool) || (vType==QVariant::Double) || (vType==QVariant::Int) || (vType==QVariant::UInt)  || (vType==QVariant::ULongLong))
				return v.toString().replace(',','.');
			else
				return "'"+v.toString()+"'";
			break;
		case USql::USQLITE:
			if ( (vType==QVariant::Bool) || (vType==QVariant::Double) || (vType==QVariant::Int) || (vType==QVariant::UInt)  || (vType==QVariant::ULongLong))
				return v.toString().replace(',','.');
			else
				return "'"+v.toString().replace('\'',"\'\'")+"'";
			break;
		case USql::USQLITE2:
			if ( (vType==QVariant::Bool) || (vType==QVariant::Double) || (vType==QVariant::Int) || (vType==QVariant::UInt)  || (vType==QVariant::ULongLong))
				return v.toString().replace(',','.');
			else
				return "'"+v.toString().replace('\'',"\'\'")+"'";
			break;
		case USql::UTDS:
			if ( (vType==QVariant::Bool) || (vType==QVariant::Double) || (vType==QVariant::Int) || (vType==QVariant::UInt)  || (vType==QVariant::ULongLong))
				return v.toString().replace(',','.');
			else
				return "'"+v.toString()+"'";
			break;
		default:
			if ( (vType==QVariant::Bool) || (vType==QVariant::Double) || (vType==QVariant::Int) || (vType==QVariant::UInt)  || (vType==QVariant::ULongLong))
				return v.toString().replace(',','.');
			else
				return "'"+v.toString()+"'";
			break;
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
USql::UDatabaseType UTableWidgetSqlExt::dataType(QString conName)
{
	QString driverName;
	if (QSqlDatabase::contains(conName))
		driverName = QSqlDatabase::database(conName).driverName().toUpper();
	else
		driverName = QSqlDatabase::database().driverName().toUpper();
	if (driverName=="QDB2"){
		return USql::UDB2;
	}
	else if (driverName=="QIBASE"){
		return USql::UIBASE;
	}
	else if (driverName=="QMYSQL"){
		return USql::UMYSQL;
	}
	else if (driverName=="QOCI"){
		return USql::UOCI;
	}
	else if (driverName=="QODBC"){
		return USql::UODBC;
	}
	else if (driverName=="QPSQL"){
		return USql::UPSQL;
	}
	else if (driverName=="QSQLITE"){
		return USql::USQLITE;
	}
	else if (driverName=="QSQLITE2"){
		return USql::USQLITE2;
	}
	else if (driverName=="QTDS"){
		return USql::UTDS;
	}
	else
		return USql::UINVALIDDB;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::populateTable()
{
	disconnect(tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(saveItem(QTableWidgetItem *)));
	disconnect(tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(setTwExtSorting(int)));
	tableWidget->blockSignals(true);
	tableWidget->selectionModel()->blockSignals(true);
	
	int prevId = -1;
	int prevCol = 1;
	if (tableWidget->rowCount()>0){
		prevId = tableWidget->item(tableWidget->currentRow(),0)->data(Qt::EditRole).toInt();
		prevCol = tableWidget->currentColumn();
	}
	QSqlQuery query;
	query.setForwardOnly(true);
	int row=0;
	bool rowSelected = false;
	query.exec("SELECT count(*) FROM "+sqlTableName+whereFiltrStr);
	query.next();
	int rowCount = query.value(0).toInt();
	tableWidget->setRowCount(rowCount);
	if (!rowCount)
		goto zeroRowCount;
	query.exec("SELECT * FROM "+sqlTableName+whereFiltrStr+orderByStr);
	while (query.next()){
		populateTableRow(row, query.record());
		if (query.record().value(columnName(0)).toInt() == prevId){
			tableWidget->setCurrentCell(row, prevCol);
			tableWidget->scrollToItem(tableWidget->item(row, prevCol));
			rowSelected = true;
		}
		row++;
	}
	if (rowCount != 0){
		tableWidget->resizeRowsToContents();
		if (!rowSelected){
			tableWidget->setCurrentCell(0, prevCol);
			tableWidget->scrollToItem(tableWidget->item(0, prevCol));
		}
	}
zeroRowCount:
	tableWidget->selectionModel()->blockSignals(false);
	tableWidget->blockSignals(false);
	connect(tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(saveItem(QTableWidgetItem *)));
	if (uSortingEnabled){
		connect(tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(setTwExtSorting(int)));
		twSortOrderAsc = true;
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::populateTableRow(int row, QSqlRecord record)
{
	int colCount = tableWidget->columnCount();
	for (int col=0; col<colCount; col++)
		populateTableItem(row, col, &record);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::populateTableItem(int row, int col, QSqlRecord * record)
{
	QString cName = columnName(col);
	QTableWidgetItem *item = new QTableWidgetItem();
	item->setData(Qt::EditRole, record->value(cName));
	//при потребі задання вирівнювання
	if (colAlignmentHash.contains(cName))
		item->setTextAlignment(colAlignmentHash.value(cName));
	else
		item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	// при потребі задання прапорців
	if (colItemFlagsHash.contains(cName))
		item->setFlags(colItemFlagsHash.value(cName));
	//при потребі задання  кольору фону
	if (colBgColorHash.contains(cName))
		item->setBackground(QBrush(colBgColorHash.value(cName)));
	tableWidget->setItem(row, col, item);
}
//--------------------utech--------------------utech--------------------utech--------------------
/*
void UTableWidgetSqlExt::saveItem(QTableWidgetItem * item)
{
	if (columnName(item->column()).isEmpty())
		return;
	QSqlQuery query;
	int id = tableWidget->item(item->row(), 0)->data(Qt::EditRole).toInt();
	QVariant var = item->data(Qt::EditRole);
	query.exec("UPDATE "+sqlTableName+" \
			SET "+columnName(item->column())+"="+__sqlEscStr(var)+" \
			WHERE "+columnName(0)+"="+QString::number(id));
	query.exec("SELECT "+columnName(item->column())+" FROM "+sqlTableName+" WHERE "+columnName(0)+"="+QString::number(id));
	query.next();
	item->setData(Qt::EditRole, query.value(0));
	emit tableItemEdited(item);
}
*/
void UTableWidgetSqlExt::saveItem(QTableWidgetItem * item)
{
	if (columnName(item->column()).isEmpty())
		return;
	QSqlQuery query;
	int id = tableWidget->item(item->row(), 0)->data(Qt::EditRole).toInt();
	QVariant var = item->data(Qt::EditRole);
	if (columnName(item->column()).compare(columnName(0), Qt::CaseInsensitive)){ //не ідентифікаторне поле
		query.exec("UPDATE "+sqlTableName+" \
				SET "+columnName(item->column())+"="+__sqlEscStr(var)+" \
				WHERE "+columnName(0)+"="+QString::number(id));
		query.exec("SELECT "+columnName(item->column())+" FROM "+sqlTableName+" WHERE "+columnName(0)+"="+QString::number(id));
		query.next();
		item->setData(Qt::EditRole, query.value(0));
		emit tableItemEdited(item);
	}
	else{ //зміна поля ідентифікатора
		disconnect(tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(saveItem(QTableWidgetItem *)));
		if (!var.canConvert<int>())
			goto SET_OLD_ID_VALUE;
		query.exec("SELECT true FROM "+sqlTableName+" WHERE "+columnName(0)+"="+var.toString());
		if (query.next()){
			qDebug() << "Table " << sqlTableName << ": value " << var.toInt() << " of key column  " << columnName(0) <<  "already exists";
			goto SET_OLD_ID_VALUE;
		}
		bool updOk = query.exec("UPDATE "+sqlTableName+" \
				SET "+columnName(item->column())+"="+var.toString()+" \
				WHERE "+columnName(0)+"="+QString::number(id));
		if (updOk){
			tableWidget->item(item->row(), 0)->setData(Qt::EditRole, var);
			emit tableItemEdited(item);
		}
		else
			goto SET_OLD_ID_VALUE;
			
		connect(tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(saveItem(QTableWidgetItem *)));
	}
	
	return;
	
SET_OLD_ID_VALUE:
	item->setData( Qt::EditRole, tableWidget->item(item->row(), 0)->data(Qt::EditRole)); //встановлення старого значення
	connect(tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(saveItem(QTableWidgetItem *)));
	return;
}
//--------------------utech--------------------utech--------------------utech--------------------
bool UTableWidgetSqlExt::addRow(QString insertQuery)
{
	QSqlQuery query;
	bool doneOk = true;
	int rowId=0;
	if (uDbType == USql::UMYSQL){
		if (insertQuery.size()>11)
			doneOk = query.exec(insertQuery);
		else
			doneOk = query.exec("INSERT INTO "+sqlTableName+" () VALUES ()");
		if (!doneOk){
			qDebug() << "bool UTableWidgetSqlExt::addRow(QString insertQuery) queryError: " << query.lastQuery();
			return false;
		}
		query.exec("SELECT last_insert_id()");
		query.next();
		rowId = query.value(0).toInt();
	}
	else if ((uDbType == USql::USQLITE) || (uDbType == USql::USQLITE2)){
		if (insertQuery.size()>11)
			doneOk = query.exec(insertQuery);
		else
			doneOk = query.exec("INSERT INTO "+sqlTableName+" ("+columnName(0)+") VALUES (null)");
		if (!doneOk){
			qDebug() << "bool UTableWidgetSqlExt::addRow(QString insertQuery) queryError: " << query.lastQuery();
			return false;
		}
		query.exec("SELECT last_insert_rowid()");
		query.next();
		rowId = query.value(0).toInt();
	}
	else if (uDbType == USql::UODBC){
		if (insertQuery.size()>11)
			doneOk = query.exec(insertQuery);
		else
			doneOk = query.exec("INSERT INTO "+sqlTableName+" ("+columnName(1)+") VALUES (null)");
		if (!doneOk){
			qDebug() << "bool UTableWidgetSqlExt::addRow(QString insertQuery) queryError: " << query.lastQuery();
			return false;
		}
		query.exec("SELECT @@identity");
		query.next();
		rowId = query.value(0).toInt();
	}
	else if (driverCanFatchLastInsertId){
		if (insertQuery.size()>11)
			doneOk = query.exec(insertQuery);
		else
			doneOk = query.exec("INSERT INTO "+sqlTableName+" ("+columnName(1)+") VALUES (null)");
		if (!doneOk){
			qDebug() << "bool UTableWidgetSqlExt::addRow(QString insertQuery) queryError: " << query.lastQuery();
			return false;
		}
		rowId = query.lastInsertId().toInt();
	}
	else{
		query.exec("SELECT max("+columnName(0)+") FROM "+sqlTableName);
		query.next();
		rowId = query.value(0).toInt();
		doneOk = query.exec("INSERT INTO "+sqlTableName+" ("+columnName(0)+") VALUES ("+QString::number(rowId)+")");
		if (!doneOk){
			qDebug() << "bool UTableWidgetSqlExt::addRow(QString insertQuery) queryError: " << query.lastQuery();
			return false;
		}
	}
	
	query.exec("SELECT * FROM "+sqlTableName+" WHERE "+columnName(0)+"="+QString::number(rowId));
	query.next();
	int row = tableWidget->rowCount();
	
	disconnect(tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(saveItem(QTableWidgetItem *)));
	tableWidget->setRowCount(row+1);
	populateTableRow(row, query.record());
	tableWidget->resizeRowToContents(row);
	
	QTableWidgetItem * currentItem;
	for (int col=0; col<tableWidget->columnCount(); col++){
		if (!tableWidget->isColumnHidden(col)){
			currentItem = tableWidget->item(row, col);
			tableWidget->setCurrentItem(currentItem);
			tableWidget->scrollToItem(currentItem);
			tableWidget->editItem(currentItem);
			break;
		}
	}
	
	connect(tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(saveItem(QTableWidgetItem *)));
	return true;
}
//--------------------utech--------------------utech--------------------utech--------------------
bool UTableWidgetSqlExt::deleteRow()
{
	if (!tableWidget->rowCount())
		return false;
	QSqlQuery query;
	int id = tableWidget->item(tableWidget->currentRow(), 0)->data(Qt::EditRole).toInt();
	bool doneOk = query.exec("DELETE FROM "+sqlTableName+" WHERE "+columnName(0)+"="+QString::number(id));
	
	if (!doneOk)
		return false;
	tableWidget->removeRow(tableWidget->currentRow());
	return true;
}
//--------------------utech--------------------utech--------------------utech--------------------
bool UTableWidgetSqlExt::deleteSelectedRows()
{
	if (!tableWidget->rowCount())
		return false;
	int selRow = tableWidget->currentRow();
	bool doneOkAll = true;
	QModelIndexList lst = tableWidget->selectionModel()->selectedRows(0);
	QSqlQuery query;
	QList<int> idList;
	foreach(QModelIndex ind, lst){
		int row = ind.row();
		int id = tableWidget->item(row, 0)->data(Qt::EditRole).toInt();
		bool doneOkCur = query.exec("DELETE FROM "+sqlTableName+" WHERE "+columnName(0)+"="+QString::number(id));
		if (doneOkCur)
			idList << id;
		else
			doneOkAll = false;
	}
	for (int row=0; row<tableWidget->rowCount(); row++){
		int id = tableWidget->item(row, 0)->data(Qt::EditRole).toInt();
		if (idList.contains(id)){
			if (selRow == row)
				selRow--;
			if (selRow < 0)
				selRow = 0;
			tableWidget->removeRow(row);
			--row;
			idList.removeOne(id);
		}
	}
	if (tableWidget->rowCount() <= selRow)
		selRow = tableWidget->rowCount()-1;
	if (tableWidget->rowCount() != 0)
		tableWidget->setCurrentCell(selRow, 0);
	return doneOkAll;
}
//--------------------utech--------------------utech--------------------utech--------------------
QString UTableWidgetSqlExt::sqlFilter()
{
	return whereFiltrStr;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::setSqlFilter(QString str)
{
	str = str.trimmed();
	if (str.size()<1){
		whereFiltrStr = "";
		return;
	}
	if (str.contains("where", Qt::CaseInsensitive))
		whereFiltrStr = " "+str;
	else
		whereFiltrStr = " WHERE "+str;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::clearSqlFilter()
{
	whereFiltrStr = "";
}
//--------------------utech--------------------utech--------------------utech--------------------
QString UTableWidgetSqlExt::sqlOrderBy()
{
	return orderByStr;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::setSqlOrderBy(QString str)
{
	str = str.trimmed();
	if (str.size()<1){
		orderByStr = "";
		return;
	}
	if (str.contains("order by", Qt::CaseInsensitive))
		orderByStr = " "+str;
	else
		orderByStr = " ORDER BY "+str;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::clearSqlOrderBy()
{
	orderByStr = "";
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::setItemDelegateForColumn(QString columnName, QItemDelegate *iDelegate)
{
	tableWidget->setItemDelegateForColumn(columnNumber(columnName), iDelegate);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::setItemDelegateForColumn(int columnPos, QItemDelegate *iDelegate)
{
	tableWidget->setItemDelegateForColumn(columnPos, iDelegate);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::setColumnHidden(QString columnName, bool hide)
{
	tableWidget->setColumnHidden(columnNumber(columnName), hide);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::setColumnHidden(int column, bool hide)
{
	tableWidget->setColumnHidden(column, hide);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::setItemData(int row, QString colName, QVariant val)
{
	int col = columnNumber(colName);
	if (col<0)
		return;
	tableWidget->item(row, col)->setData(Qt::EditRole, val);
}
//--------------------utech--------------------utech--------------------utech--------------------
int UTableWidgetSqlExt::columnNumber(QString columnName)
{
	QRegExp regExp(columnName, Qt::CaseInsensitive);
	return colNamesList.indexOf(regExp);
}
//--------------------utech--------------------utech--------------------utech--------------------
QString UTableWidgetSqlExt::columnName(int columnNumber)
{
	if (columnNumber>=0 && columnNumber<colNamesList.size())
		return colNamesList[columnNumber];
	else
		return QString();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::setColumnWidth(QString columnName, int width)
{
	int col=0;
	foreach (QString colName, colNamesList){
		if (!QString::compare(colName, columnName, Qt::CaseInsensitive))
			tableWidget->setColumnWidth(col, width);
		col++;
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::setColumnWidth(int columnPos, int width)
{
	tableWidget->setColumnWidth(columnPos, width);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::setCurrentItemData(QString columnName, QVariant val)
{
	if (tableWidget->rowCount() == 0)
		return;
	if (!tableWidget->selectionModel()->hasSelection())
		return;
	setItemData(tableWidget->currentRow(), columnName, val);
}
//--------------------utech--------------------utech--------------------utech--------------------
QVariant UTableWidgetSqlExt::currentItemData(QString columnName)
{
	if (tableWidget->rowCount() == 0)
		return QVariant();
	if (!tableWidget->selectionModel()->hasSelection())
		return QVariant();
	int col = columnNumber(columnName);
	if (col < 0 || col >= tableWidget->columnCount())
		return QVariant();
	return tableWidget->item(tableWidget->currentRow(), col)->data(Qt::EditRole);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::clearColAlignmentHash()
{
	colAlignmentHash.clear();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::addColAlignment(QString colName, Qt::Alignment al)
{
	//colAlignmentHash.remove(colName);
	colAlignmentHash.insert(colName, al);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::clearColItemFlagsHash()
{
	colItemFlagsHash.clear();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::addColItemFlags(QString colName, Qt::ItemFlags f)
{
	colItemFlagsHash.insert(colName, f);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::clearColBgColorHash()
{
	colBgColorHash.clear();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::addColBgColor(QString colName, QColor cl)
{
	colBgColorHash.insert(colName, cl);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::setSortingEnabled(bool sortingEnabled)
{
	uSortingEnabled = sortingEnabled;
}
//--------------------utech--------------------utech--------------------utech--------------------
bool UTableWidgetSqlExt::sortingEnabled()
{
	return uSortingEnabled;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTableWidgetSqlExt::setTwExtSorting(int clickedColumn)
{
	Qt::SortOrder order;
	if (twSortOrderAsc)
		order = Qt::AscendingOrder;
	else
		order = Qt::DescendingOrder;
	twSortOrderAsc = (!twSortOrderAsc);
	tableWidget->sortItems(clickedColumn, order);
}
//--------------------utech--------------------utech--------------------utech--------------------
UTableWidgetSqlExt::~UTableWidgetSqlExt()
{	
	
}
//--------------------utech--------------------utech--------------------utech--------------------
	
//--------------------utech--------------------utech--------------------utech--------------------	
UDataFormView::UDataFormView(QTableWidget *tWidget, QString sqlTName)
	: UTableWidgetSqlExt(tWidget, sqlTName)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
bool UDataFormView::insertWidget(QWidget *widget, QString columnName)
{
	if (!colNamesList.contains( columnName, Qt::CaseInsensitive )){
		qDebug() << "UDataFormView classObject - Wrong widget columnName value.";
		return false;
	}
	
	bool doneOk=false;
	
	viewWidgetsHash.insert(widget, columnName);
	widget->blockSignals(true);
	
	lineEdit = qobject_cast<QLineEdit *>(widget);
	if (lineEdit){
		connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(valueChanged()));
		doneOk=true;
		goto castDone;
	}
	comboBox = qobject_cast<QComboBox *>(widget);
	if (comboBox){
		connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(valueChanged()));
		new UIntEditingComboBox(comboBox);
		doneOk=true;
		goto castDone;
	}
	spinBox = qobject_cast<QSpinBox *>(widget);
	if (spinBox){
		connect(spinBox, SIGNAL(editingFinished()), this, SLOT(valueChanged()));
		doneOk=true;
		goto castDone;
	}
	doubleSpinBox = qobject_cast<QDoubleSpinBox *>(widget);
	if (doubleSpinBox){
		connect(doubleSpinBox, SIGNAL(editingFinished()), this, SLOT(valueChanged()));
		doneOk=true;
		goto castDone;
	}
	checkBox = qobject_cast<QCheckBox *>(widget);
	if (checkBox){
		connect(checkBox, SIGNAL(stateChanged(int)), this, SLOT(valueChanged()));
		doneOk=true;
		goto castDone;
	}
	timeEdit = qobject_cast<QTimeEdit *>(widget);
	if (timeEdit){
		connect(timeEdit, SIGNAL(editingFinished()), this, SLOT(valueChanged()));
		doneOk=true;
		goto castDone;
	}
	dateEdit = qobject_cast<QDateEdit *>(widget);
	if (dateEdit){
		connect(dateEdit, SIGNAL(editingFinished()), this, SLOT(valueChanged()));
		doneOk=true;
		goto castDone;
	}
	dateTimeEdit = qobject_cast<QDateTimeEdit *>(widget);
	if (dateTimeEdit){
		connect(dateTimeEdit, SIGNAL(editingFinished()), this, SLOT(valueChanged()));
		doneOk=true;
		goto castDone;
	}
	groupBox = qobject_cast<QGroupBox *>(widget);
	if (groupBox){
		connect(groupBox, SIGNAL(toggled(bool)), this, SLOT(valueChanged()));
		doneOk=true;
		goto castDone;
	}
castDone:
	
	if (doneOk){
		return true;
	}
	else{
		qDebug() << "UDataFormView classObject - insertWidget(QWidget *, QString) function got unknown widget.";
		return false;
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDataFormView::setWidgetValue(QWidget *widget, QVariant value)
{
	lineEdit = qobject_cast<QLineEdit *>(widget);
	if (lineEdit){
		lineEdit->setText(value.toString());
		goto castDone;
	}
	comboBox = qobject_cast<QComboBox *>(widget);
	if (comboBox){
		int curInd = comboBox->findData(value.toInt(), Qt::UserRole);
		if (curInd == -1)
			curInd = 0;
		comboBox->setCurrentIndex(curInd);
		goto castDone;
	}
	spinBox = qobject_cast<QSpinBox *>(widget);
	if (spinBox){
		spinBox->setValue(value.toInt());
		goto castDone;
	}
	doubleSpinBox = qobject_cast<QDoubleSpinBox *>(widget);
	if (doubleSpinBox){
		doubleSpinBox->setValue(value.toDouble());;
		goto castDone;
	}
	checkBox = qobject_cast<QCheckBox *>(widget);
	if (checkBox){
		checkBox->setChecked(value.toBool());
		goto castDone;
	}
	timeEdit = qobject_cast<QTimeEdit *>(widget);
	if (timeEdit){
		if (value.isNull())
			timeEdit->setTime(timeEdit->minimumTime());
		else
			timeEdit->setTime(value.toTime());
		goto castDone;
	}
	dateEdit = qobject_cast<QDateEdit *>(widget);
	if (dateEdit){
		if (value.isNull())
			dateEdit->setDate(dateEdit->minimumDate());
		else
			dateEdit->setDate(value.toDate());
		goto castDone;
	}
	dateTimeEdit = qobject_cast<QDateTimeEdit *>(widget);
	if (dateTimeEdit){
		if (value.isNull())
			dateTimeEdit->setDateTime(dateTimeEdit->minimumDateTime());
		else
			dateTimeEdit->setDateTime(value.toDateTime());
		goto castDone;
	}
	groupBox = qobject_cast<QGroupBox *>(widget);
	if (groupBox){
		groupBox->setChecked(value.toBool());
		goto castDone;
	}
castDone:
	
	return;
}
//--------------------utech--------------------utech--------------------utech--------------------
QVariant UDataFormView::widgetValue(QWidget *widget)
{
	QVariant value;
	
	lineEdit = qobject_cast<QLineEdit *>(widget);
	if (lineEdit){
		value = lineEdit->text();
		goto castDone;
	}
	comboBox = qobject_cast<QComboBox *>(widget);
	if (comboBox){
		value = comboBox->itemData(comboBox->currentIndex(), Qt::UserRole);
		goto castDone;
	}
	spinBox = qobject_cast<QSpinBox *>(widget);
	if (spinBox){
		value = spinBox->value();
		goto castDone;
	}
	doubleSpinBox = qobject_cast<QDoubleSpinBox *>(widget);
	if (doubleSpinBox){
		value = doubleSpinBox->value();
		goto castDone;
	}
	checkBox = qobject_cast<QCheckBox *>(widget);
	if (checkBox){
		value = checkBox->isChecked();
		goto castDone;
	}
	timeEdit = qobject_cast<QTimeEdit *>(widget);
	if (timeEdit){
		value = timeEdit->time();
		goto castDone;
	}
	dateEdit = qobject_cast<QDateEdit *>(widget);
	if (dateEdit){
		value = dateEdit->date();
		goto castDone;
	}
	dateTimeEdit = qobject_cast<QDateTimeEdit *>(widget);
	if (dateTimeEdit){
		value = dateTimeEdit->dateTime();
		goto castDone;
	}
	groupBox = qobject_cast<QGroupBox *>(widget);
	if (groupBox){
		value = groupBox->isChecked();
		goto castDone;
	}
castDone:
	
	return value;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDataFormView::populateComboBoxItems(QComboBox *combo, QHash<int, QString> itemsHash)
{
	QHashIterator<int, QString> iter(itemsHash);
	combo->blockSignals(true);
	combo->clear();
	while (iter.hasNext()) {
		iter.next();
		combo->addItem(iter.value(), iter.key());
	}
	combo->blockSignals(false);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDataFormView::populateComboBoxItems(QComboBox *combo, UIntStringList & items)
{
	combo->blockSignals(true);
	combo->clear();
	int size = items.size();
	for (int iter=0; iter<size; iter++)
		combo->addItem(items.valueAt(iter), items.keyAt(iter));
	combo->blockSignals(false);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDataFormView::setItemDelegateForColumn(QString columnName, QHash<int, QString> delegateHash)
{
	int col = columnNumber(columnName);
	tableWidget->setItemDelegateForColumn(col, new UHashComboDelegate(tableWidget, delegateHash));
	
	QList<QWidget *> wList = viewWidgetsHash.keys(columnName);
	for (int iter=0; iter<wList.size(); ++iter){
		comboBox = qobject_cast<QComboBox *>(wList[iter]);
		if (comboBox)
			populateComboBoxItems(comboBox, delegateHash);
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDataFormView::setItemDelegateForColumn(QString columnName, UIntStringList & items)
{
	int col = columnNumber(columnName);
	tableWidget->setItemDelegateForColumn(col, new UIntStringListComboDelegate(tableWidget, items));
	
	QList<QWidget *> wList = viewWidgetsHash.keys(columnName);
	for (int iter=0; iter<wList.size(); ++iter){
		comboBox = qobject_cast<QComboBox *>(wList[iter]);
		if (comboBox)
			populateComboBoxItems(comboBox, items);
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDataFormView::setItemDelegateForColumn(QString columnName, QItemDelegate *iDelegate)
{
	tableWidget->setItemDelegateForColumn(columnNumber(columnName), iDelegate);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDataFormView::setItemDelegateForColumn(int columnPos, QItemDelegate *iDelegate)
{
	tableWidget->setItemDelegateForColumn(columnPos, iDelegate);
}
//--------------------utech--------------------utech--------------------utech--------------------
bool UDataFormView::deleteRow()
{
	tableWidget->selectionModel()->blockSignals(true);
	bool ok = UTableWidgetSqlExt::deleteRow();
	tableWidget->selectionModel()->blockSignals(false);
	populateView();
	return ok;
}
//--------------------utech--------------------utech--------------------utech--------------------
bool UDataFormView::deleteSelectedRows()
{
	tableWidget->selectionModel()->blockSignals(true);
	bool ok = UTableWidgetSqlExt::deleteSelectedRows();
	tableWidget->selectionModel()->blockSignals(false);
	populateView();
	return ok;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDataFormView::populateTable()
{
	disconnect(tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(populateViewWidget(QTableWidgetItem *)));
	disconnect(tableWidget->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(populateView()));
	
	UTableWidgetSqlExt::populateTable();
	populateView();
	
	connect(tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(populateViewWidget(QTableWidgetItem *)));
	connect(tableWidget->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(populateView()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDataFormView::valueChanged()
{
	if (tableWidget->rowCount() == 0)
		return;
	
	currentRow = tableWidget->currentRow();
	
	QWidget *widget = qobject_cast<QWidget *>(QObject::sender());
	QString colName = viewWidgetsHash.value(widget);
	int column = columnNumber(colName);
	if (column < 0)
		return;
	else if (column > tableWidget->columnCount())
		return;
	QVariant newVal = widgetValue(widget);
	tableWidget->item(currentRow, column)->setData(Qt::EditRole, newVal);
	disconnect(tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(populateViewWidget(QTableWidgetItem *)));
	widget->blockSignals(true);
	setWidgetValue(widget, tableWidget->item(currentRow, column)->data(Qt::EditRole));
	widget->blockSignals(false);
	connect(tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(populateViewWidget(QTableWidgetItem *)));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDataFormView::populateView()
{
	QHashIterator<QWidget *,QString> iter(viewWidgetsHash);
	if (tableWidget->rowCount() == 0){
		while (iter.hasNext()){
			iter.next();
			iter.key()->setEnabled(false);
		}
		return;
	}
	
	currentRow = tableWidget->currentRow();
	
	int columnCount = tableWidget->columnCount();
	while (iter.hasNext()){
		iter.next();
		int column = columnNumber(iter.value());
		if ((column > -1) && (column < columnCount)){
			QWidget *widget = iter.key();
			widget->setEnabled(true);
			widget->blockSignals(true);
			setWidgetValue(widget, tableWidget->item(currentRow, column)->data(Qt::EditRole));
			widget->blockSignals(false);
		}
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDataFormView::populateViewWidget(QTableWidgetItem *item)
{
	if (tableWidget->rowCount() == 0)
		return;
	
	currentRow = tableWidget->currentRow();
	if (item->row() != currentRow)
		return;
	
	QList<QWidget *> wList = viewWidgetsHash.keys(columnName(item->column()));
	foreach (QWidget *widget, wList){
		widget->blockSignals(true);
		setWidgetValue(widget, item->data(Qt::EditRole));
		widget->blockSignals(false);
	}
}
//--------------------utech--------------------utech--------------------utech--------------------


//--------------------utech--------------------utech--------------------utech--------------------
UIntEditingComboBox::UIntEditingComboBox(QComboBox *cBox)
	: QObject(cBox)
{
	comboBox = cBox;
	
	comboBox->setEditable(true);
	comboBox->setInsertPolicy(QComboBox::NoInsert);
	
	connect(comboBox->lineEdit(), SIGNAL(editingFinished()), this, SLOT(comboBoxEditingFinished()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UIntEditingComboBox::comboBoxEditingFinished()
{
	bool doneOk;
	int iVal = comboBox->lineEdit()->text().toInt(&doneOk);
	if (doneOk){
		int ind = comboBox->findData(iVal, Qt::UserRole);
		if (ind != -1)
			comboBox->setCurrentIndex(ind);
		else
			QMessageBox::critical(0, "Невірний ідентифікатор", "Помилковий ідентифікатор "+QString::number(iVal)+".");
			comboBox->setCurrentIndex(comboBox->currentIndex());
	}
	else{
		comboBox->setCurrentIndex(comboBox->currentIndex());
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
