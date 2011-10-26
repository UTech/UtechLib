#ifndef cdx_h
#define cdx_h
#include "xbindex.h"

struct cdxHeader
{
  long rootNode;
  long freeNode;
  long reserved;
  short keyLen;
  struct Features
  {
    bool unique:1;
    int:2;
    bool hasFor:1;
    bool:1;
    bool cdxHeader:1;
    bool cdxFmt:1;
  } features;
  char signature;
  long reserved1[5];
  char reserved2[466];
  short descending;
  short reserved3;
  short forLen;
  short reserved4;
  short forLen2;
  char forBuffer[514];
};

struct cdxNode
{
  short attr;
  short keyCount;
  long leftSibling;
  long rightSibling;
};

struct innerCdxNode: public cdxNode
{
  char keys[500];
};

struct externalCdxNode: public cdxNode
{
  short freeSpace;
  long recNumberMask;
  char reservByteCounterMask;
  char tailByteCounterMask;
  char recBitUsing;
  char reservBitUsing;
  char tailBitUsing;
  char byteCount;
  char keys[490];
};

class XBDLLEXPORT xbCdx: public xbIndex
{
  public:
//    xbCdx() {} I don't like to make empty object with no protection 
// to method method call. And I don't see any need of it.
    xbCdx(xbDbf* dbf): xbIndex(dbf) {}
    virtual ~xbCdx() {CloseIndex();}

//    xbCdx(xbDbf* dbf, const char* tagName, const char* expr);
    xbShort CreateIndex(const char *filename, const char* tagname, 
         const char *expr, xbShort unique, xbShort overwrite) {return 0;}
    xbShort AddTag(const char* tagname, const char *expr, xbShort unique, 
         xbShort overwrite) {return 0;}
    virtual xbLong   GetTotalNodes() {return 0;}
    virtual xbULong  GetCurDbfRec() {return 0;}
    virtual xbShort  CreateKey( xbShort, xbShort ) {return 0;}
    virtual xbShort  GetCurrentKey(char *key) {return 0;}
    virtual xbShort  AddKey( xbLong ) {return 0;}
    virtual xbShort  UniqueIndex() {return 0;}
    virtual xbShort  DeleteKey( xbLong ) {return 0;}
    virtual xbShort  KeyWasChanged() {return 0;}
    virtual xbShort  FindKey( const char * ) {return 0;}
    virtual xbShort  FindKey() {return 0;}
    virtual xbShort  FindKey( xbDouble ) {return 0;}
    virtual xbShort  GetNextKey() {return 0;}
    virtual xbShort  GetLastKey() {return 0;}
    virtual xbShort  GetFirstKey() {return 0;}
    virtual xbShort  GetPrevKey() {return 0;}
    virtual xbShort  ReIndex(void (*statusFunc)(xbLong itemNum, xbLong numItems) = 0) {return 0;}
    virtual xbShort  KeyExists( xbDouble ) {return 0;}
    virtual void     GetExpression(char *buf, int len) {}
#ifdef XBASE_DEBUG
    virtual void     DumpHdrNode( xbShort Option ) {};
    virtual void     DumpNodeRec( xbLong ) {};
    virtual void     DumpNodeChain() {};
    virtual xbShort  CheckIndexIntegrity( xbShort ) {return 0;};
#endif
    
//    static xbString CreateIndexName(const xbString& dbfName);
    virtual const char* GetExtWithDot(bool lower);
  
  protected:
    virtual xbShort GetHeadNode() {return 0;}
    virtual xbUShort GetKeyLen() {return 0;}
    virtual const char* GetKeyExpression() {return "";}
    virtual void FreeNodesMemory() {}

  private:
    xbCdx(const xbCdx&);
    xbCdx& operator=(const xbCdx&);
};

#endif
