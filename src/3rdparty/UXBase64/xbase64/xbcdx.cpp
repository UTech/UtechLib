#include <string>
#include <fstream>
#include "xbase64.h"
#include "xbcdx.h"

/*xbCdx::xbCdx(xbDbf* dbf, const char* tagName, const char* expr): 
     xbIndex(dbf)
{
  IndexName=CreateIndexName(dbf->GetDbfName());
  if (Tools::FileExists(indexName_.c_str())) OpenIndex(indexName_.c_str());
  else CreateIndex(tagName, expr, XB_NOT_UNIQUE, XB_DONTOVERLAY);
}

xbShort xbCdx::CreateIndex(const char *tagName, const char *expr, 
     xbShort unique, xbShort overwrite)
{
//  indexfp=fopen(IndexName.c_str(), "wb+");
  return 0;
}

inline const char* Ext(char c)
{
  return (c>='A' && c<='Z')? ".CDX": ".cdx"; 
}

xbString xbCdx::CreateIndexName(const xbString& dbfName)
{
  std::string::size_type pos=dbfName.find_last_of(".\\");
  if (pos==std::string::npos || dbfName[pos]=='\\' || pos==0) 
       return dbfName+Ext(dbfName[dbfName.length()-1]);
  return dbfName.substr(0, pos)+Ext(dbfName[pos+1]);
  return xbString();
}
*/

const char* xbCdx::GetExtWithDot(bool lower) 
{
  return lower? ".cdx": ".CDX";
}
