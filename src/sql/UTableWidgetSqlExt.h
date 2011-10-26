//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#ifndef UTABLEWIDGETSQLEXT_H
#define UTABLEWIDGETSQLEXT_H

#include <QObject>
#include <QString>
#include <QtSql>
#include <QtGui>

#include "USqlAccessible.h"
#include "U2List.h"

//--------------------utech--------------------utech--------------------utech--------------------
class UTableWidgetSqlExt : public QObject
{
	Q_OBJECT
  public:
	UTableWidgetSqlExt(QTableWidget *tWidget, QString sqlTName, QString connectionName=QLatin1String("defaultConnection"));
	virtual ~UTableWidgetSqlExt();
	USql::UDatabaseType dataType(QString conName);
	QString __sqlEscStr(QVariant v);
	
	void populateTableRow(int row, QSqlRecord record);
	void populateTableItem(int row, int col, QSqlRecord * record);
	bool addRow(QString insertQuery = "");
	bool deleteRow();
	bool deleteSelectedRows();
	QString sqlFilter();
	void setSqlFilter(QString str);
	void clearSqlFilter();
	QString sqlOrderBy();
	void setSqlOrderBy(QString str);
	void clearSqlOrderBy();
	void setItemDelegateForColumn(QString columnName, QItemDelegate *iDelegate);
	void setItemDelegateForColumn(int columnPos, QItemDelegate *iDelegate);
	void setColumnHidden(QString columnName, bool hide=true);
	void setColumnHidden(int column, bool hide=true);
	void setItemData(int row, QString colName, QVariant val);
	int columnNumber(QString columnName);
	QString columnName(int columnNumber);
	void setColumnWidth(QString columnName, int width);
	void setColumnWidth(int columnPos, int width);
	void setCurrentItemData(QString columnName, QVariant val);
	QVariant currentItemData(QString columnName);
	void clearColAlignmentHash();
	void addColAlignment(QString colName, Qt::Alignment al);
	void clearColItemFlagsHash();
	void addColItemFlags(QString colName, Qt::ItemFlags f);
	void clearColBgColorHash();
	void addColBgColor(QString colName, QColor cl);
	void setSortingEnabled(bool sortingEnabled);
	bool sortingEnabled();
  public slots:
	void populateTable();
	void saveItem(QTableWidgetItem * item);
  private slots:
	void setTwExtSorting(int clickedColumn);
  signals:
	void tableItemEdited(QTableWidgetItem *);
  public:
	QStringList colNamesList;
  protected:
	QTableWidget *tableWidget;
	QString sqlTableName;
	QHash<QString, Qt::Alignment> colAlignmentHash;
	QHash<QString, Qt::ItemFlags> colItemFlagsHash;
	QHash<QString, QColor> colBgColorHash;
	QString whereFiltrStr;
	QString orderByStr;
	QString conName;
	USql::UDatabaseType uDbType;
	bool driverCanFatchLastInsertId;
	bool uSortingEnabled;
	bool twSortOrderAsc;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UDataFormView : public UTableWidgetSqlExt
{
  Q_OBJECT
  public:
	UDataFormView(QTableWidget *tWidget, QString sqlTName);
	bool insertWidget(QWidget *widget, QString columnName);
	void setWidgetValue(QWidget *widget, QVariant value);
	QVariant widgetValue(QWidget *widget);
	void populateComboBoxItems(QComboBox *combo, QHash<int, QString> itemsHash);
	void populateComboBoxItems(QComboBox *combo, UIntStringList & items);
	void setItemDelegateForColumn(QString columnName, QHash<int, QString> delegateHash);
	void setItemDelegateForColumn(QString columnName, UIntStringList & items);
	void setItemDelegateForColumn(QString columnName, QItemDelegate *iDelegate);
	void setItemDelegateForColumn(int columnPos, QItemDelegate *iDelegate);
	bool deleteRow();
	bool deleteSelectedRows();
  public slots:
	void populateTable(); //модицікована функція
	void valueChanged();
	void populateView();
	void populateViewWidget(QTableWidgetItem *item);
  private:
	QHash<QWidget *, QString> viewWidgetsHash;
	
	//WidgetsForCasts
	QLineEdit * lineEdit;
	QComboBox * comboBox;
	QSpinBox * spinBox;
	QDoubleSpinBox * doubleSpinBox;
	QCheckBox * checkBox;
	QTimeEdit * timeEdit;
	QDateEdit * dateEdit;
	QDateTimeEdit * dateTimeEdit;
	QGroupBox * groupBox;
	//---
	int currentRow;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UIntEditingComboBox : QObject
{
  Q_OBJECT
  public:
	UIntEditingComboBox(QComboBox *cBox);
  public slots:
	void comboBoxEditingFinished();
  private:
	QComboBox *comboBox;
};

#endif
