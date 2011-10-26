#ifndef UNUMBERTOSTRINGCONVERTER_H
#define UNUMBERTOSTRINGCONVERTER_H

#include<QtCore>

QString numberToString(QString);
QString odunuci(QChar &);
QString desjatku(QChar & charDesjatku, QChar nullChar = '0');
QString sotni(QChar & charSotni);

#endif
