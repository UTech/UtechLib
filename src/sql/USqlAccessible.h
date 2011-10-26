//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації глобальних службових фнккцій програми нарахування зарплати
//
// Створений програмістами Компанії "Утех" 17.07.2007р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef USQLACCESSIBLE_H
#define USQLACCESSIBLE_H

#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QTime>
#include <QDate>
#include <QSqlQuery>

class USql: QObject
{
	Q_OBJECT
	Q_ENUMS(UDatabaseType)
  public:
	enum UDatabaseType {UINVALIDDB=0, UDB2=1, UIBASE=2, UMYSQL=3, UOCI=4, UODBC=5, UPSQL=6, USQLITE=7, USQLITE2=8, UTDS=9};
};

int nextLichylnyk(QString tableName, QString incColumnName="id");

//Функції для роботи з mySql
QString mysqlStr(int val);
QString mysqlStr(double val, bool money = true);
QString mysqlStr(QString val);
QString mysqlStr(bool val);
QString mysqlStr(QDate val);

QString sqlStr(int val);
QString sqlStr(double val, bool money = true);
QString sqlStr(QString val);
QString sqlStr(bool val);
QString sqlStr(QDate val);
QString sqlStr(QTime val);
QString sqlStr(QDateTime val);
QString escapeSqlStr(QString in, USql::UDatabaseType sqlDatabaseType = USql::UMYSQL);
//--------------------utech--------------------utech--------------------utech--------------------
#endif
