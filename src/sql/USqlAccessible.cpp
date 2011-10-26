//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконаня глобальних службових фнккцій програми нарахування зарплати
//
// Створений програмістами Компанії "Утех" 17.07.2007р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "USqlAccessible.h"
#include "../engine/UMath.h"

#include <QtDebug>

//--------------------utech--------------------utech--------------------utech--------------------
int nextLichylnyk(QString tableName, QString incColumnName)
{
	QSqlQuery *query = new QSqlQuery();
	query->exec("SELECT max("+incColumnName+") FROM " + tableName);
	if (!query->seek(0))
		return -1;
	int iterId = query->value(0).toInt()+1;
	delete query;
	return iterId;
}
//--------------------utech--------------------utech--------------------utech--------------------
QString mysqlStr(int val)
{
	return sqlStr(val);
}
//--------------------utech--------------------utech--------------------utech--------------------
QString mysqlStr(double val, bool money)
{
	return sqlStr(val, money);
}
//--------------------utech--------------------utech--------------------utech--------------------
QString mysqlStr(QString val)
{
	return sqlStr(val);
}
//--------------------utech--------------------utech--------------------utech--------------------
QString mysqlStr(bool val)
{
	return sqlStr(val);
}
//--------------------utech--------------------utech--------------------utech--------------------
QString mysqlStr(QDate val)
{
	return sqlStr(val);
}
//--------------------utech--------------------utech--------------------utech--------------------
QString sqlStr(int val)
{
	return QString::number(val);
}
//--------------------utech--------------------utech--------------------utech--------------------
QString sqlStr(double val, bool money)
{
	if (money)
		return m_to_str_2_krapka(val);
	else
		return QString::number(val).replace(",",".");
}
//--------------------utech--------------------utech--------------------utech--------------------
QString sqlStr(QString val)
{
	return "'"+val+"'";
}
//--------------------utech--------------------utech--------------------utech--------------------
QString sqlStr(bool val)
{
	if (val)
		return "true";
	else
		return "false";
}
//--------------------utech--------------------utech--------------------utech--------------------
QString sqlStr(QDate val)
{
	return "'"+val.toString("yyyy-MM-dd")+"'";
}
//--------------------utech--------------------utech--------------------utech--------------------
QString sqlStr(QTime val)
{
	return "'"+val.toString("hh:mm")+"'";
}
//--------------------utech--------------------utech--------------------utech--------------------
QString sqlStr(QDateTime val)
{
	return "'"+val.toString("yyyy-MM-dd hh:mm")+"'";
}
//--------------------utech--------------------utech--------------------utech--------------------
QString escapeSqlStr(QString in, USql::UDatabaseType sqlDatabaseType)
{
    QString retval = "'";
    for (QString::iterator it = in.begin(); it != in.end(); it++){
		if (sqlDatabaseType == USql::UMYSQL){
			if (*it == '\"')
				retval += "\\\"";
			else if (*it == '\'')
				retval += "\\\'";
			else if (*it == '\\')
				retval += "\\\\";
			else
				retval += *it;
		}
		else if (sqlDatabaseType == USql::UODBC){
			if (*it == '\"')
				retval += "\\\"";
			else if (*it == '\'')
				retval += "\\\'";
			else if (*it == '\\')
				retval += "\\\\";
			else
				retval += *it;
		}
		else if (sqlDatabaseType == USql::USQLITE){
			if (*it == '\'')
				retval += "\'\'";
			else
				retval += *it;
		}
		else
			retval += *it;
    }
	retval += "'";
    return retval;
}
//--------------------utech--------------------utech--------------------utech--------------------

