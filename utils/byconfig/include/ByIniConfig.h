#ifndef __INIFILE_H
#define __INIFILE_H

#include <iostream>
#include "ByConfig.h"
using namespace std;

class TIniFile:public TByConfigImpl{
public:
	TIniFile();
    bool Open(string FileName);
	bool Close();
	TIniFile(string FileName);
    ~TIniFile();
	virtual double ReadFloat(const string Section, const string Ident, double Default);
	virtual int    ReadInteger(const string Section, const string Ident, int Default);
	virtual string ReadString(const string Section, const string Ident, const string Default);
    virtual bool   WriteFloat(const string Section, const string Ident, double Value,int dot_cont=2);
    virtual bool   WriteInteger(const string Section, const string Ident, int Value);
    virtual bool   WriteString(const string Section, const string Ident, const string Value);
    virtual bool   WriteBool(const string Section, const string Ident, bool Value);
	virtual bool   ReadBool(const string Section, const string Ident, bool Default);
	virtual bool   ValueExists(const string Section, const string Ident);
	virtual bool   SectionExists(const string Section);
    virtual string ReadString(const string Ident, const string Default);
	virtual void   WriteString(const string Ident, const string Value);
	string m_FileName;
private:
        bool CheckValid();	
};

#endif
