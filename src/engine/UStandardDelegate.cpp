//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл визначення бібліотеки стандартних делегатів для комірок 
//
// Створений програмістами Компанії "Утех" 23.03.2008р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UStandardDelegate.h"

#include <QtDebug>
#include <QPainter>
#include <QSqlQuery>
#include <QMessageBox>

//--------------------utech--------------------utech--------------------utech--------------------
USpinBoxDelegate::USpinBoxDelegate(int min, int max, QObject *parent)
    : QItemDelegate(parent)
{
	minValue = min;
	maxValue = max;
}
//--------------------utech--------------------utech--------------------utech--------------------
QWidget *USpinBoxDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
    QSpinBox *spinBox = new QSpinBox(parent);
	spinBox->setMinimum( minValue );
	spinBox->setMaximum( maxValue );
	spinBox->setAlignment( Qt::AlignRight );
		
    //connect(spinBox, SIGNAL(editingFinished()), this, SLOT(QItemDelegate::commitAndCloseEditor()));
    return spinBox;
}
//--------------------utech--------------------utech--------------------utech--------------------
void USpinBoxDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const
{
	int num = index.model()->data(index, Qt::DisplayRole).toInt();
    QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);
    spinBox->setValue(num);
	spinBox->selectAll();
}
//--------------------utech--------------------utech--------------------utech--------------------
void USpinBoxDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
    QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);
    int num = spinBox->value();
    model->setData(index, num);
}
//--------------------utech--------------------utech--------------------utech--------------------
UDoubleSpinBoxDelegate::UDoubleSpinBoxDelegate(double min, double max, int dec, QObject *parent )
    : QItemDelegate(parent)
{
	minValue = min;
	maxValue = max;
	decimals = dec;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDoubleSpinBoxDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
	QStyleOptionViewItemV3 opt = setOptions(index, option);
	
	drawBackground(painter, opt, index);
	drawDisplay(painter, opt, opt.rect, QString::number(index.data().toDouble(),'f', decimals).replace('.',','));
	drawFocus(painter, opt, opt.rect);
}
//--------------------utech--------------------utech--------------------utech--------------------
QWidget *UDoubleSpinBoxDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
	UDoubleSpinBox *doubleSpinBox = new UDoubleSpinBox(parent);
	doubleSpinBox->setMinimum ( minValue );
	doubleSpinBox->setMaximum ( maxValue );
	doubleSpinBox->setDecimals( decimals );
	doubleSpinBox->setAlignment( Qt::AlignRight );
		
    //connect(doubleSpinBox, SIGNAL(editingFinished()), this, SLOT(QItemDelegate::commitAndCloseEditor()));
    return doubleSpinBox;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDoubleSpinBoxDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const
{
	double num = index.model()->data(index, Qt::EditRole).toDouble();
    QDoubleSpinBox *doubleSpinBox = qobject_cast<QDoubleSpinBox *>(editor);
    doubleSpinBox->setValue(num);
	doubleSpinBox->selectAll();
 }
//--------------------utech--------------------utech--------------------utech--------------------
void UDoubleSpinBoxDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
	QDoubleSpinBox *doubleSpinBox = qobject_cast<QDoubleSpinBox *>(editor);
    double num = doubleSpinBox->value();
    model->setData(index, num);
}
//--------------------utech--------------------utech--------------------utech--------------------
UDateEditDelegate::UDateEditDelegate( QDate minD, QDate maxD, QObject *parent)
    : QItemDelegate(parent)
{
	minDate = minD;
	maxDate = maxD;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDateEditDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
	QStyleOptionViewItemV3 opt = setOptions(index, option);
	
	drawBackground(painter, opt, index);
	QDate date = index.data().toDate();
	if (date.isValid())
		drawDisplay(painter, opt, opt.rect, index.data().toDate().toString("dd.MM.yyyy"));
	else
		drawDisplay(painter, opt, opt.rect, "-");
	drawFocus(painter, opt, opt.rect);
}
//--------------------utech--------------------utech--------------------utech--------------------
QWidget *UDateEditDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
	QDateEdit *dEdit = new QDateEdit(parent);
	dEdit->setDateRange(minDate,maxDate);
	dEdit->setAlignment( Qt::AlignRight );
	
    //connect(dEdit, SIGNAL(editingFinished()), this, SLOT(QItemDelegate::commitAndCloseEditor()));
    return dEdit;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDateEditDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const
{
	QDate date = index.model()->data(index, Qt::EditRole).toDate();
    QDateEdit *dEdit = qobject_cast<QDateEdit *>(editor);
    dEdit->setDate(date);
	dEdit->selectAll();
 }
//--------------------utech--------------------utech--------------------utech--------------------
void UDateEditDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
	QDateEdit *dEdit = qobject_cast<QDateEdit *>(editor);
    model->setData(index, dEdit->date());
}
//--------------------utech--------------------utech--------------------utech--------------------
//--------------------utech--------------------utech--------------------utech--------------------
UBoolComboDelegate::UBoolComboDelegate( QObject *parent, QString trueStr, QString falseStr )
    : QItemDelegate(parent)
{
	trueString = trueStr;
	falseString = falseStr;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UBoolComboDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
	QStyleOptionViewItemV3 opt = setOptions(index, option);
	
	drawBackground(painter, opt, index);
	if (index.data().toBool())
		drawDisplay(painter, opt, opt.rect, trueString);
	else
		drawDisplay(painter, opt, opt.rect, falseString);
	drawFocus(painter, opt, opt.rect);
}
//--------------------utech--------------------utech--------------------utech--------------------
QWidget *UBoolComboDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
	QComboBox *comboBox = new QComboBox(parent);
	comboBox->addItem(trueString);
	comboBox->addItem(falseString);
	comboBox->setEditable(false);
		
    //connect(comboBox, SIGNAL(editingFinished()), this, SLOT(QItemDelegate::commitAndCloseEditor()));
    return comboBox;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UBoolComboDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const
{
	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	if (index.model()->data(index, Qt::EditRole).toBool())
		comboBox->setCurrentIndex( 0 );
	else
		comboBox->setCurrentIndex( 1 );
 }
//--------------------utech--------------------utech--------------------utech--------------------
void UBoolComboDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	if (comboBox->currentIndex() == 0)
		model->setData(index, true, Qt::EditRole);
	else
		model->setData(index, false, Qt::EditRole);
}
//--------------------utech--------------------utech--------------------utech--------------------

UCheckBoxDelegate::UCheckBoxDelegate( QObject *parent, QString trueStr, QString falseStr, QString checkBoxStr )
    : QItemDelegate(parent)
{
	trueString = trueStr;
	falseString = falseStr;
	checkBoxString = checkBoxStr;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UCheckBoxDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
	QStyleOptionViewItemV3 opt = setOptions(index, option);
	
	drawBackground(painter, opt, index);
	if (index.data().toBool())
		drawDisplay(painter, opt, opt.rect, trueString);
	else
		drawDisplay(painter, opt, opt.rect, falseString);
	drawFocus(painter, opt, opt.rect);
}
//--------------------utech--------------------utech--------------------utech--------------------
QWidget *UCheckBoxDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
	QCheckBox *checkBox = new QCheckBox(parent);
	checkBox->setText(checkBoxString);
    return checkBox;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UCheckBoxDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const
{
	QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor);
	checkBox->setChecked(index.model()->data(index, Qt::EditRole).toBool());
 }
//--------------------utech--------------------utech--------------------utech--------------------
void UCheckBoxDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
	QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor);
	model->setData(index, checkBox->isChecked(), Qt::EditRole);
}
//--------------------utech--------------------utech--------------------utech--------------------
UHashComboDelegate::UHashComboDelegate( QObject *parent, QHash<int, QString> hash )
    : QItemDelegate(parent)
{
	strHash = hash;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UHashComboDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
	QStyleOptionViewItemV3 opt = setOptions(index, option);
	
	drawBackground(painter, opt, index);
	drawDisplay(painter, opt, opt.rect, strHash.value(index.data().toInt()));
	drawFocus(painter, opt, opt.rect);
}
//--------------------utech--------------------utech--------------------utech--------------------
QWidget *UHashComboDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
	QComboBox *comboBox = new QComboBox(parent);
	comboBox->setEditable(true);
	comboBox->setInsertPolicy(QComboBox::NoInsert);
	QHashIterator<int, QString> iter(strHash);
	while (iter.hasNext()) {
		iter.next();
		comboBox->addItem(iter.value(), iter.key());
	}
    return comboBox;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UHashComboDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const
{
	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	int curInd = comboBox->findData(index.model()->data(index, Qt::EditRole).toInt(), Qt::UserRole);
	if (curInd == -1)
		curInd = 0;
	comboBox->setCurrentIndex(curInd);
	comboBox->lineEdit()->selectAll();
 }
//--------------------utech--------------------utech--------------------utech--------------------
void UHashComboDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	bool doneOk;
	int iVal = comboBox->currentText().toInt(&doneOk);
	if (doneOk){
		if (comboBox->findData( iVal, Qt::UserRole) != -1)
			model->setData(index, iVal, Qt::EditRole);
		else
			QMessageBox::critical(0, "Невірний ідентифікатор", "Помилковий ідентифікатор "+QString::number(iVal)+".");
	}
	else{
		model->setData(index, comboBox->itemData(comboBox->currentIndex(), Qt::UserRole), Qt::EditRole);
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
UIntStringListComboDelegate::UIntStringListComboDelegate( QObject *parent, const UIntStringList & intStrList )
    : QItemDelegate(parent)
{
	strHash = intStrList;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UIntStringListComboDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
	QStyleOptionViewItemV3 opt = setOptions(index, option);
	
	drawBackground(painter, opt, index);
	drawDisplay(painter, opt, opt.rect, strHash.value(index.data().toInt()));
	drawFocus(painter, opt, opt.rect);
}
//--------------------utech--------------------utech--------------------utech--------------------
QWidget *UIntStringListComboDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
	QComboBox *comboBox = new QComboBox(parent);
	comboBox->setEditable(true);
	comboBox->setInsertPolicy(QComboBox::NoInsert);
	for (int i=0; i<strHash.size(); ++i)
		comboBox->addItem(strHash.valueAt(i), strHash.keyAt(i));
    return comboBox;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UIntStringListComboDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const
{
	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	int curInd = comboBox->findData(index.model()->data(index, Qt::EditRole).toInt(), Qt::UserRole);
	if (curInd == -1)
		curInd = 0;
	comboBox->setCurrentIndex(curInd);
	comboBox->lineEdit()->selectAll();
 }
//--------------------utech--------------------utech--------------------utech--------------------
void UIntStringListComboDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	bool doneOk;
	int iVal = comboBox->currentText().toInt(&doneOk);
	if (doneOk){
		if (comboBox->findData( iVal, Qt::UserRole) != -1)
			model->setData(index, iVal, Qt::EditRole);
		else
			QMessageBox::critical(0, "Невірний ідентифікатор", "Помилковий ідентифікатор "+QString::number(iVal)+".");
	}
	else{
		model->setData(index, comboBox->itemData(comboBox->currentIndex(), Qt::UserRole), Qt::EditRole);
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
USqlDynComboBox::USqlDynComboBox(QWidget *parent, QString idColName, QString colSelStr, QString sqlTableName)
	: QComboBox(parent)
{
	idColumnName = idColName;
	columnSelStr = colSelStr;
	tableName = sqlTableName;
	
	setEditable(true);
	setInsertPolicy(QComboBox::NoInsert);
	connect(this->lineEdit(), SIGNAL(textChanged(const QString &)), this, SLOT(showList(const QString &)));
}	
//--------------------utech--------------------utech--------------------utech--------------------
void USqlDynComboBox::showList(const QString & text)
{
	QSqlQuery query;
	query.exec("SELECT "+idColumnName+", "+columnSelStr+" FROM "+tableName+" WHERE "+columnSelStr+" LIKE '"+text+"%'");
	
	QComboBox *comboBox = qobject_cast<QComboBox *>(sender()->parent());
	comboBox->clear();
	qDebug() << text;
	qDebug() << query.lastQuery();
	QAbstractItemModel *model = comboBox->model();
	model->insertRow(0);
	model->insertRow(1);
	model->insertRow(2);
	model->setData(model->index(0,0), QVariant("0000"));
	model->setData(model->index(1,0), QVariant("0000"));
	
	//comboBox->addItem("Ok", 1);
	//while (query.next())
	//	comboBox->addItem(query.value(1).toString(), query.value(0).toInt());
	//comboBox->showPopup();
}
//--------------------utech--------------------utech--------------------utech--------------------
UComboBoxDelegateSqlExt::UComboBoxDelegateSqlExt( QObject *parent, QString idColName, QString colSelStr, QString colInsName, QString sqlTableName)
    : QItemDelegate(parent)
{
	idColumnName = idColName;
	columnSelStr = colSelStr;
	columnInsName = colInsName;
	tableName = sqlTableName;
	
	populateHash();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UComboBoxDelegateSqlExt::populateHash()
{
	QSqlQuery query;
	query.exec("SELECT "+idColumnName+", "+columnSelStr+" FROM "+tableName);
	while (query.next())
		strHash.insert(query.value(0).toInt(), query.value(1).toString());
}
//--------------------utech--------------------utech--------------------utech--------------------
void UComboBoxDelegateSqlExt::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
	QStyleOptionViewItemV3 opt = setOptions(index, option);
	
	drawBackground(painter, opt, index);
	drawDisplay(painter, opt, opt.rect, strHash.value(index.data().toInt()));
	drawFocus(painter, opt, opt.rect);
}
//--------------------utech--------------------utech--------------------utech--------------------
QWidget *UComboBoxDelegateSqlExt::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
	USqlDynComboBox *comboBox = new USqlDynComboBox(parent, idColumnName, columnSelStr, tableName);
    return comboBox;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UComboBoxDelegateSqlExt::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const
{
	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	int curInd = comboBox->findData(index.model()->data(index, Qt::EditRole).toInt(), Qt::UserRole);
	if (curInd == -1)
		curInd = 0;
	comboBox->setCurrentIndex(curInd);
	comboBox->lineEdit()->selectAll();
 }
//--------------------utech--------------------utech--------------------utech--------------------
void UComboBoxDelegateSqlExt::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	bool doneOk;
	int iVal = comboBox->currentText().toInt(&doneOk);
	if (doneOk){
		if (comboBox->findData( iVal, Qt::UserRole) != -1)
			model->setData(index, iVal, Qt::EditRole);
		else
			QMessageBox::critical(0, "Невірний ідентифікатор", "Помилковий ідентифікатор "+QString::number(iVal)+".");
	}
	else{
		model->setData(index, comboBox->itemData(comboBox->currentIndex(), Qt::UserRole), Qt::EditRole);
	}
}
//--------------------utech--------------------utech--------------------utech--------------------

UTimeDelegate::UTimeDelegate(QObject *parent, QString tFormat)
    : QItemDelegate(parent)
{
	timeFormat = tFormat;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTimeDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
	QStyleOptionViewItemV3 opt = setOptions(index, option);
	
	drawBackground(painter, opt, index);
	drawDisplay(painter, opt, opt.rect, index.data(Qt::DisplayRole).toTime().toString(timeFormat));
	drawFocus(painter, opt, opt.rect);
}
//--------------------utech--------------------utech--------------------utech--------------------
QWidget *UTimeDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
	QTimeEdit *timeEdit = new QTimeEdit(parent);
	timeEdit->setDisplayFormat(timeFormat);
    return timeEdit;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UTimeDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const
{
	QTimeEdit *timeEdit = qobject_cast<QTimeEdit *>(editor);
	timeEdit->setTime(index.model()->data(index, Qt::EditRole).toTime());
 }
//--------------------utech--------------------utech--------------------utech--------------------

void UTimeDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
	QTimeEdit *timeEdit = qobject_cast<QTimeEdit *>(editor);
	model->setData(index, timeEdit->time(), Qt::EditRole);
}
//--------------------utech--------------------utech--------------------utech--------------------
UDateTimeDelegate::UDateTimeDelegate(QObject *parent, QString tFormat)
    : QItemDelegate(parent)
{
	timeFormat = tFormat;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDateTimeDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
	QStyleOptionViewItemV3 opt = setOptions(index, option);
	
	drawBackground(painter, opt, index);
	drawDisplay(painter, opt, opt.rect, index.data(Qt::DisplayRole).toDateTime().toString(timeFormat));
	drawFocus(painter, opt, opt.rect);
}
//--------------------utech--------------------utech--------------------utech--------------------
QWidget *UDateTimeDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
	QDateTimeEdit *dateTimeEdit = new QDateTimeEdit(parent);
	dateTimeEdit->setDisplayFormat(timeFormat);
	dateTimeEdit->setAlignment( Qt::AlignRight );
	
    return dateTimeEdit;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDateTimeDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const
{
	QDateTimeEdit *dateTimeEdit = qobject_cast<QDateTimeEdit *>(editor);
	dateTimeEdit->setDateTime(index.model()->data(index, Qt::EditRole).toDateTime());
 }
//--------------------utech--------------------utech--------------------utech--------------------
void UDateTimeDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
	QDateTimeEdit *dateTimeEdit = qobject_cast<QDateTimeEdit *>(editor);
	model->setData(index, dateTimeEdit->dateTime(), Qt::EditRole);
}
//--------------------utech--------------------utech--------------------utech--------------------
