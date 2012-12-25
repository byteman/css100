
#include <Poco/SingletonHolder.h>
#include <Poco/String.h>
#include "ByConfigMgr.h"
#include "ByDBConfig.h"
#include "ByIniConfig.h"
ByConfigMgr::ByConfigMgr(std::string type):
    _impl(NULL)
{

    if(Poco::toUpper(type) == "INI")
    {
        _impl = new TIniFile();
    }else if(Poco::toUpper(type) == "SQLITE3")
    {
        _impl = new ByDBConfig();
    }
}
ByConfigMgr::~ByConfigMgr()
{
    if(_impl)
    {
        delete _impl;
        _impl = NULL;
    }
}
bool ByConfigMgr::Open(string path)
{
    if(_impl)
    {
        return _impl->Open (path);
    }
    return false;
}
bool ByConfigMgr::Close()
{
    if(_impl)
    {
        return _impl->Close ();
    }
    return false;
}

double ByConfigMgr::ReadFloat(const string Section, const string Ident, double Default)
{
    if(_impl)
    {
        return _impl->ReadFloat (Section,Ident,Default);
    }
    return Default;
}
int    ByConfigMgr::ReadInteger(const string Section, const string Ident, int Default)
{
    if(_impl)
    {
        return _impl->ReadInteger (Section,Ident,Default);
    }
    return Default;
}
string ByConfigMgr::ReadString(const string Section, const string Ident, const string Default)
{
    if(_impl)
    {
        return _impl->ReadString (Section,Ident,Default);
    }
    return Default;
}
bool   ByConfigMgr::WriteFloat(const string Section, const string Ident, double Value,int dot_cont)
{
    if(_impl)
    {
        return _impl->WriteFloat (Section,Ident,Value,dot_cont);
    }
    return false;
}
bool   ByConfigMgr::WriteInteger(const string Section, const string Ident, int Value)
{
    if(_impl)
    {
        return _impl->WriteInteger (Section,Ident,Value);
    }
    return false;
}
bool   ByConfigMgr::WriteString(const string Section, const string Ident, const string Value)
{
    if(_impl)
    {
        return _impl->WriteString (Section,Ident,Value);
    }
    return false;
}
bool   ByConfigMgr::WriteBool(const string Section, const string Ident, bool Value)
{
    if(_impl)
    {
        return _impl->WriteBool (Section,Ident,Value);
    }
    return false;
}
bool   ByConfigMgr::ReadBool(const string Section, const string Ident, bool Default)
{

}
bool   ByConfigMgr::ValueExists(const string Section, const string Ident)
{
    if(_impl)
    {
        return _impl->ValueExists (Section,Ident);
    }
    return false;
}
bool   ByConfigMgr::SectionExists(const string Section)
{
    if(_impl)
    {
        return _impl->SectionExists (Section);
    }
    return false;
}
bool   ByConfigMgr::setProperty(const std::string& name, const std::string& value)
{
    if(_impl)
    {
        return _impl->setProperty (name,value);
    }
    return false;
}
std::string    ByConfigMgr::getProperty(const std::string& name) const
{
    if(_impl)
    {
        return _impl->getProperty (name);
    }
    return "";
}
