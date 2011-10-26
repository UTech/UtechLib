//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації бібліотеки стандартних делегатів для комірок 
//
// Створений програмістами Компанії "Утех" 23.03.2008р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef USTANDARDDELEGATE_H
#define USTANDARDDELEGATE_H

#include <QItemDelegate>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QString>
#include <QModelIndex>
#include <QVariant>
#include <QStringList>
#include <QComboBox>
#include <QDateEdit>
#include <QCheckBox>

#include "UMath.h"
#include "U2List.h"

class UDoubleSpinBox : public QDoubleSpinBox
{
	Q_OBJECT
  public:
	UDoubleSpinBox( QWidget * parent = 0 ) : QDoubleSpinBox(parent){};
	QValidator::State validate( QString & input, int & pos ) const
	{
		input.replace('.',',');
		return QDoubleSpinBox::validate(input, pos);
	};
};

//--------------------utech--------------------utech--------------------utech--------------------
class USpinBoxDelegate : public QItemDelegate
{	
   Q_OBJECT
public:
		USpinBoxDelegate( int min=0, int max=1000, QObject *parent = 0);
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model,  const QModelIndex &index) const;
private slots:

private:
		int minValue;
		int maxValue;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UDoubleSpinBoxDelegate : public QItemDelegate
{	
   Q_OBJECT
public:
		UDoubleSpinBoxDelegate( double min=0, double max=1000, int dec=2, QObject *parent = 0);
		void paint(QPainter *painter,const QStyleOptionViewItem &option,const QModelIndex &index) const;
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model,  const QModelIndex &index) const;
private slots:

private:
		double minValue;
		double maxValue;
		int decimals;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UDateEditDelegate : public QItemDelegate
{	
   Q_OBJECT
public:
		UDateEditDelegate( QDate minD=QDate(2000,1,1), QDate maxD=QDate(2100,1,1), QObject *parent = 0);
		void paint(QPainter *painter,const QStyleOptionViewItem &option,const QModelIndex &index) const;
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model,  const QModelIndex &index) const;
private slots:

private:
		QDate minDate;
		QDate maxDate;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UBoolComboDelegate : public QItemDelegate
{	
   Q_OBJECT
public:
		UBoolComboDelegate( QObject *parent, QString trueStr="Так", QString falseStr="Ні" );
		void paint(QPainter *painter,const QStyleOptionViewItem &option,const QModelIndex &index) const;
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model,  const QModelIndex &index) const;
private slots:

private:
		QString trueString;
		QString falseString;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UCheckBoxDelegate : public QItemDelegate
{	
   Q_OBJECT
public:
		UCheckBoxDelegate( QObject *parent, QString trueStr="Так", QString falseStr="Ні", QString checkBoxStr = "" );
		void paint(QPainter *painter,const QStyleOptionViewItem &option,const QModelIndex &index) const;
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model,  const QModelIndex &index) const;
private slots:

private:
		QString trueString;
		QString falseString;
		QString checkBoxString;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UHashComboDelegate : public QItemDelegate
{	
   Q_OBJECT
public:
		UHashComboDelegate( QObject *parent, QHash<int, QString> hash );
		void paint(QPainter *painter,const QStyleOptionViewItem &option,const QModelIndex &index) const;
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model,  const QModelIndex &index) const;
private slots:

private:
		QHash<int, QString> strHash;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UIntStringListComboDelegate : public QItemDelegate
{	
   Q_OBJECT
public:
		UIntStringListComboDelegate( QObject *parent, const UIntStringList & intStrList );
		void paint(QPainter *painter,const QStyleOptionViewItem &option,const QModelIndex &index) const;
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model,  const QModelIndex &index) const;
private slots:

private:
		UIntStringList strHash;
};
//--------------------utech--------------------utech--------------------utech--------------------
class USqlDynComboBox : public QComboBox
{
	Q_OBJECT
  public:
	USqlDynComboBox(QWidget *parent, QString idColName, QString colSelStr, QString sqlTableName);
  private slots:
	void showList(const QString & text);
  private:
	QString idColumnName;
	QString columnSelStr;
	QString tableName;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UComboBoxDelegateSqlExt : public QItemDelegate
{	
   Q_OBJECT
public:
		UComboBoxDelegateSqlExt( QObject *parent, QString idColName="id", QString colSelStr="''", QString colInsName="''", QString sqlTableName="''" );
		void paint(QPainter *painter,const QStyleOptionViewItem &option,const QModelIndex &index) const;
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model,  const QModelIndex &index) const;
private slots:
		void populateHash();
private:
		QString idColumnName;
		QString columnSelStr;
		QString columnInsName;
		QString tableName;
		QHash<int, QString> strHash;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UTimeDelegate : public QItemDelegate
{	
   Q_OBJECT
public:
		UTimeDelegate(QObject *parent, QString tFormat = "H:mm");
		void paint(QPainter *painter,const QStyleOptionViewItem &option,const QModelIndex &index) const;
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model,  const QModelIndex &index) const;
private slots:

private:
		QString timeFormat;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UDateTimeDelegate : public QItemDelegate
{	
   Q_OBJECT
public:
		UDateTimeDelegate(QObject *parent, QString tFormat = "dd.MM.yyyy H:mm");
		void paint(QPainter *painter,const QStyleOptionViewItem &option,const QModelIndex &index) const;
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model,  const QModelIndex &index) const;
private slots:

private:
		QString timeFormat;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
