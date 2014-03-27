#ifndef _CLASS_DESC_H_
#define _CLASS_DESC_H_

#include <map>
#include <string>

struct ParameterDesc
{
    std::string name;
    std::string type;
};

struct MethodDesc
{
    std::string name;
    std::string signature;
    std::string returnType;
    std::string access;
    bool isVirtual;
    std::vector<ParameterDesc> parameters;
};

struct ClassDesc
{
    typedef std::map<std::string, ClassDesc> Map;

    std::string name;
    bool isAbstract;
    bool isQObject;
    std::vector<std::string> baseClassNames;
    std::vector<MethodDesc> methods;
};

#endif
