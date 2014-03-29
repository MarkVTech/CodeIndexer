#ifndef _METHOD_PARSER_H_
#define _METHOD_PARSER_H_

#include <vector>
#include <utility>

#include <Index.h>

#include "ClassDesc.h"
#include "ClangUtil.h"

class QObjectIndexer
{
public:
    enum MethodType
    {
        NORMAL,
        SLOT,
        SIGNAL
    };
    typedef std::pair<LocationInfo, MethodType> AccessLocation;

    QObjectIndexer();

    bool checkForSlot(CXTranslationUnit tu, CXToken** tokenPtr);
    void tokenizeClass(CXCursor cursor);

    CXChildVisitResult visit(CXCursor cursor, CXCursor parent);
    CXChildVisitResult visit2(CXCursor cursor, CXCursor parent);

private:
    CXChildVisitResult handleEnum_(CXCursor start, CXCursor parent,
        CXClientData clientData);

    unsigned int extractConstructor_(CXCursor cursor);
    unsigned int extractDestructor_(CXCursor cursor);
    unsigned int extractBaseSpec_(CXCursor cursor);
    unsigned int extractClassMethod_(CXCursor cursor);
    unsigned int extractParmDecl_(CXCursor cursor);
    unsigned int extractFieldDecl_(CXCursor cursor);
    unsigned int extractEnumDecl_(CXCursor cursor);
    unsigned int extractRecord_(CXCursor cursor, const std::string& name);

    void dump_(CXToken tokens[], CXCursor cursors[], unsigned int count);

    std::vector<AccessLocation> accessLocations_;

    std::string currentRecord_;
    MethodDesc currentMethod_;
    std::string currentAccess_;

    ClassDesc::Map name2ClassMap_;

};

std::ostream& operator<<(std::ostream& stream,
    const QObjectIndexer::MethodType& mt);
std::ostream& operator<<(std::ostream& stream,
    const QObjectIndexer::AccessLocation& al);


#endif
