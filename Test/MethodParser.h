#ifndef _METHOD_PARSER_H_
#define _METHOD_PARSER_H_

#include <vector>
#include <utility>

#include <Index.h>

#include "ClassDesc.h"
#include "ClangUtil.h"

class MethodParser
{
public:
    enum MethodType
    {
        NORMAL,
        SLOT,
        SIGNAL
    };
    typedef std::pair<LocationInfo, MethodType> AccessLocation;

    MethodParser();

    bool checkForSlot(CXTranslationUnit tu, CXToken** tokenPtr);
    void tokenizeClass(CXCursor cursor);

    CXChildVisitResult visit(CXCursor cursor, CXCursor parent);
    CXChildVisitResult visit2(CXCursor cursor, CXCursor parent);

private:
    CXChildVisitResult handleEnum_(CXCursor start, CXCursor parent,
        CXClientData clientData);

    unsigned int extractClassMethod_(CXCursor cursor);

    std::vector<AccessLocation> accessLocations_;

    ClassDesc currentClass_;
    MethodDesc currentMethod_;
    std::string currentAccess_;

    ClassDesc::Map name2ClassMap_;

};

std::ostream& operator<<(std::ostream& stream,
    const MethodParser::MethodType& mt);
std::ostream& operator<<(std::ostream& stream,
    const MethodParser::AccessLocation& al);


#endif
