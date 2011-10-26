#include "UMath.h"

QString	uMToStr(double money)
{
	return m_to_str(money);
}

QString	uMToStr2(double money)
{
	return m_to_str_2(money);
}

QString	uMToStr2Krapka(double money)
{
	return m_to_str_2_krapka(money);
}

double uDToM(double d)
{
	return d_to_m(d);
}

QString m_to_str(double money)
{
	bool znak=FALSE;
	if (money < -0.9999){
		money *= -1;
		znak = TRUE;
	}
	int i_val = money;
	money -= i_val;
	if (money >= 0.5) i_val ++;
	QString res_str;
	if (znak) res_str += "-";
	res_str += QVariant(i_val).toString();
	return res_str;
}
//------------------------------------------------------------
QString m_to_str_2(double money)
{	
	
	bool znak=FALSE;
	if (money < -0.009999){
		money *= -1;
		znak = TRUE;
	}
	money += 0.00001;
	int i_val = money, i_val_2;
	money -= i_val;
	money *= 100;
	i_val_2 = money;
	money -= i_val_2;
	if (money >= 0.5) i_val_2 ++;
	if (i_val_2 >= 100){
		i_val_2 --;
		i_val ++;
	}
	QString res_str;
	if (znak) res_str += "-";
	res_str += QVariant(i_val).toString();
	res_str += ",";
	if (i_val_2<10) res_str += "0";
	res_str += QVariant(i_val_2).toString();
	return res_str;
}
//------------------------------------------------------------
QString	m_to_str_2_krapka(double money)
{
	bool znak=FALSE;
	if (money < -0.009999){
		money *= -1;
		znak = TRUE;
	}
	money += 0.00001;
	int i_val = money, i_val_2;
	money -= i_val;
	money *= 100;
	i_val_2 = money;
	money -= i_val_2;
	if (money >= 0.5) i_val_2 ++;
	if (i_val_2 >= 100){
		i_val_2 --;
		i_val ++;
	}
	QString res_str;
	if (znak) res_str += "-";
	res_str += QVariant(i_val).toString();
	res_str += ".";
	if (i_val_2<10) res_str += "0";
	res_str += QVariant(i_val_2).toString();
	return res_str;
}
//------------------------------------------------------------
double 	d_to_m(double d)
{
	bool znak=FALSE;
	if (d < -0.009999){
		d *= -1;
		znak = TRUE;
	}
	d *= 100;
	d += 0.5001;
	int money = d;
	d = money/100.0;
	if (znak)
		d *= -1;
	return d;
}
//------------------------------------------------------------
QString uPrizvIB(QString prizv, QString imya, QString batk)
{
	QString res = prizv;
	if (!imya.size())
		return res;
	res += QString(" ")+imya.at(0)+".";
	if (!batk.size())
		return res;
	res += batk.at(0)+QString(".");
	return res;
}
//------------------------------------------------------------
