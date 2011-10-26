#include "UNumberToStringConverter.h"


QString numberToString(QString string){
 QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
  QString s;
  QString str;
  QString sCop;
  str = string.section(',',0,0);
  sCop = string.section(',',1,1);
  
  sCop = " " + sCop;
  sCop +=codec->toUnicode(" коп.");
  QChar charOdunuci;
  QChar charDesatku;
  QChar charSotni;
  QChar charTusachi;
  QChar charDesTusach;
  int strLength = str.length();
//================================odunuci
if(strLength ==1){
  charOdunuci = str[0];
  s = odunuci(charOdunuci)+codec->toUnicode("грн.");}
//===========================??????? 
else if(strLength ==2){
	 charOdunuci = str[1];
	 charDesatku = str[0];
     if (charDesatku == '1')
	    s = desjatku(charDesatku,charOdunuci)+codec->toUnicode("грн.");
	 else if(charOdunuci == '0')
		s = desjatku(charDesatku) + codec->toUnicode("грн."); 
     else
	    s = desjatku(charDesatku) + odunuci(charOdunuci) + codec->toUnicode("грн.");
    
}
 //===================================sotni
else if (strLength == 3)
 {
     charSotni   = str[0];
	 charDesatku = str[1];
	 charOdunuci = str[2];
	 QString sDop;

	 s = sotni(charSotni);
	 if (charDesatku == '1')
	     s = s.append(desjatku(charDesatku,charOdunuci)+codec->toUnicode("грн."));
	 else if(charOdunuci == '0')
	     s = s.append(desjatku(charDesatku) + codec->toUnicode("грн."));
	 else
	     s = s.append(desjatku(charDesatku) + odunuci(charOdunuci) + codec->toUnicode("грн."));
 }
//==================tusachi
else if (strLength == 4)
{
	charTusachi = str[0];
	charSotni   = str[1];
    charDesatku = str[2];
    charOdunuci = str[3];
    

	if(charTusachi=='1')
		s = odunuci(charTusachi)+codec->toUnicode("тис€ча ");
	else if((charTusachi =='2')||(charTusachi =='3')||(charTusachi =='4'))
		s = odunuci(charTusachi)+codec->toUnicode("тис€ч≥ ");
	else
		s = odunuci(charTusachi)+codec->toUnicode("тис€ч ");
     s = s.append(sotni(charSotni));
	 if (charDesatku == '1')
	     s = s.append(desjatku(charDesatku,charOdunuci)+codec->toUnicode("грн."));
	 else if(charOdunuci == '0')
	     s = s.append(desjatku(charDesatku) + codec->toUnicode("грн."));
	 else
	     s = s.append(desjatku(charDesatku) + odunuci(charOdunuci) + codec->toUnicode("грн."));
	 
}
//=================desTusachi
else if(strLength == 5)
{
	charDesTusach = str[0]; 
	charTusachi   = str[1];
	charSotni     = str[2];
      charDesatku   = str[3];
      charOdunuci   = str[4];
      
	 
    if(charDesTusach=='1')//=========10000-19000
		s = desjatku(charDesTusach,charTusachi)+codec->toUnicode("тис€ч ");
	else if(charTusachi=='0')//=======20000-30000
		s = desjatku(charDesTusach)+codec->toUnicode("тис€ч ");
	else if(charTusachi=='1')//=======21000-31000
	    s = desjatku(charDesTusach)+odunuci(charTusachi)+codec->toUnicode("тис€ча ");
	else if((charTusachi=='2')||(charTusachi=='3')||(charTusachi=='4'))//22000-24000
		s = desjatku(charDesTusach)+odunuci(charTusachi)+codec->toUnicode("тис€ч≥ ");
    else //25000-29000
		s = desjatku(charDesTusach)+odunuci(charTusachi)+codec->toUnicode("тис€ч ");
     s = s.append(sotni(charSotni));
	 if (charDesatku == '1')
	     s = s.append(desjatku(charDesatku,charOdunuci)+codec->toUnicode("грн."));
	 else if(charOdunuci == '0')
	     s = s.append(desjatku(charDesatku) + codec->toUnicode("грн."));
	 else
	     s = s.append(desjatku(charDesatku) + odunuci(charOdunuci) + codec->toUnicode("грн."));
	 


}
//=================sotniTusach
else if(strLength == 6)
{
	QChar charSotniTusach = str[0];
	charDesTusach = str[1]; 
	charTusachi   = str[2];
	charSotni     = str[3];
    charDesatku   = str[4];
    charOdunuci   = str[5];
      
	
	//-------------
	//s = sotni(charSotniTusach);
	// if (charDesTusach == '1')
	//     s = s.append(desjatku(charDesTusach,charTusachi)+codec->toUnicode("грн."));
	// else if(charTusachi == '0')
	//     s = s.append(desjatku(charDesTusach) + codec->toUnicode("грн."));
	// else
	//     s = s.append(desjatku(charDesTusach) + odunuci(charTusachi) + codec->toUnicode("грн."));
	//--------------
	
	s = sotni(charSotniTusach);
    if(charDesTusach=='1')//=========10000-19000
		s += desjatku(charDesTusach,charTusachi)+codec->toUnicode("тис€ч ");
	else if(charTusachi=='0')//=======20000-30000
		s += desjatku(charDesTusach)+codec->toUnicode("тис€ч ");
	else if(charTusachi=='1')//=======21000-31000
	    s += desjatku(charDesTusach)+odunuci(charTusachi)+codec->toUnicode("тис€ча ");
	else if((charTusachi=='2')||(charTusachi=='3')||(charTusachi=='4'))//22000-24000
		s += desjatku(charDesTusach)+odunuci(charTusachi)+codec->toUnicode("тис€ч≥ ");
    else //25000-29000
		s += desjatku(charDesTusach)+odunuci(charTusachi)+codec->toUnicode("тис€ч ");
     s = s.append(sotni(charSotni));
	 if (charDesatku == '1')
	     s = s.append(desjatku(charDesatku,charOdunuci)+codec->toUnicode("грн."));
	 else if(charOdunuci == '0')
	     s = s.append(desjatku(charDesatku) + codec->toUnicode("грн."));
	 else
	     s = s.append(desjatku(charDesatku) + odunuci(charOdunuci) + codec->toUnicode("грн."));
	 


}
   s = s+ sCop;  
   return s;
}



 QString odunuci(QChar & charOdunuci1){
     QString s;
  QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
  if(charOdunuci1 =='0')
    s = s.append(codec->toUnicode("нуль "));
  if(charOdunuci1 =='1')
    s = s.append(codec->toUnicode("одна "));
  if(charOdunuci1 =='2')
    s = s.append(codec->toUnicode("дв≥ "));
  if(charOdunuci1 =='3')
    s = s.append(codec->toUnicode("три "));
  if(charOdunuci1 =='4')
    s = s.append(codec->toUnicode("чотири "));
  if(charOdunuci1 =='5')
    s = s.append(codec->toUnicode("п'€ть "));
  if(charOdunuci1 =='6')
    s = s.append(codec->toUnicode("ш≥сть "));
  if(charOdunuci1 =='7')
    s = s.append(codec->toUnicode("с≥м "));
  if(charOdunuci1 =='8')
    s = s.append(codec->toUnicode("в≥с≥м "));
  if(charOdunuci1 =='9')
    s = s.append(codec->toUnicode("дев'€ть "));
  return s;}
 
 QString desjatku(QChar &charDesjatku, QChar nullChar)
 {
  QString s;
  QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
  if((charDesjatku =='1')&&(nullChar =='0'))
    s = codec->toUnicode("дес€ть ");
  else if((charDesjatku =='1')&&(nullChar =='1'))
    s = codec->toUnicode("одинадц€ть ");
  else if((charDesjatku =='1')&&(nullChar =='2'))
    s = codec->toUnicode("дванадц€ть ");
  else if((charDesjatku =='1')&&(nullChar =='3'))
    s = codec->toUnicode("тринадц€ть ");
  else if((charDesjatku =='1')&&(nullChar =='4'))
    s = codec->toUnicode("чотирнадц€ть ");
  else   if((charDesjatku =='1')&&(nullChar =='5'))
    s = codec->toUnicode("п'€тнадц€ть ");
  else   if((charDesjatku =='1')&&(nullChar =='6'))
    s = codec->toUnicode("ш≥стнадц€ть ");
  else   if((charDesjatku =='1')&&(nullChar =='7'))
    s = codec->toUnicode("с≥мнадц€ть ");
  else   if((charDesjatku =='1')&&(nullChar =='8'))
    s = codec->toUnicode("в≥с≥мнадц€ть ");
  else   if((charDesjatku =='1')&&(nullChar =='9'))
    s = codec->toUnicode("дев'€тнадц€ть ");
  else   if(charDesjatku =='2')
    s = s.append(codec->toUnicode("двадц€ть "));
  else   if(charDesjatku =='3')
    s = s.append(codec->toUnicode("тридц€ть "));
  else   if(charDesjatku =='4')
    s = s.append(codec->toUnicode("сорок "));
  else   if(charDesjatku =='5')
    s = s.append(codec->toUnicode("п'€тдес€ть "));
  else   if(charDesjatku =='6')
    s = s.append(codec->toUnicode("ш≥стдес€ть "));
  else   if(charDesjatku =='7')
    s = s.append(codec->toUnicode("с≥мдес€ть "));
  else   if(charDesjatku =='8')
    s = s.append(codec->toUnicode("в≥с≥мдес€ть "));
  else   if(charDesjatku =='9')
    s = s.append(codec->toUnicode("дев'€носто "));
  return s;

 }
 QString sotni(QChar & charSotni)
 {
	 QString s;
     QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
	 if(charSotni =='0')
	   s.clear();
	 if(charSotni =='1')
       s = s.append(codec->toUnicode("сто "));
     if(charSotni =='2')
       s = s.append(codec->toUnicode("дв≥ст≥ "));
     if(charSotni =='3')
       s = s.append(codec->toUnicode("триста "));
     if(charSotni =='4')
       s = s.append(codec->toUnicode("чотириста "));
     if(charSotni =='5')
       s = s.append(codec->toUnicode("п'€тсот "));
     if(charSotni =='6')
       s = s.append(codec->toUnicode("ш≥стсот "));
     if(charSotni =='7')
       s = s.append(codec->toUnicode("с≥мсот "));
     if(charSotni =='8')
       s = s.append(codec->toUnicode("в≥с≥мсот "));
     if(charSotni =='9')
       s = s.append(codec->toUnicode("дев'€тсот "));
     return s;
 }
