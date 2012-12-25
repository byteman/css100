#ifndef BYCONFIGMGR_H
#define BYCONFIGMGR_H
#include "ByConfig.h"
class ByConfigMgr{
public:
	ByConfigMgr(std::string type);
    ~ByConfigMgr();
	bool Open(string path);
    bool Close();
	double ReadFloat(const string Section, const string Ident, double Default);
	int    ReadInteger(const string Section, const string Ident, int Default);
	string ReadString(const string Section, const string Ident, const string Default);
	bool   WriteFloat(const string Section, const string Ident, double Value,int dot_cont=2);
	bool   WriteInteger(const string Section, const string Ident, int Value);
	bool   WriteString(const string Section, const string Ident, const string Value);
	bool   WriteBool(const string Section, const string Ident, bool Value);
	bool   ReadBool(const string Section, const string Ident, bool Default);
	bool   ValueExists(const string Section, const string Ident);
	bool   SectionExists(const string Section);
	bool   setProperty(const std::string& name, const std::string& value);
	std::string    getProperty(const std::string& name) const;
private:
	TByConfigImpl* _impl;
};
 
#endif
