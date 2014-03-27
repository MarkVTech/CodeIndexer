#include "SourceIndex.h"

SourceIndex::
SourceIndex(const Defines& defines, const IncludePaths& includePaths) :
    defines_(defines),
    includePaths_(includePaths)
{
    index_ = clang_createIndex(0, 0);
}

SourceIndex::
~SourceIndex()
{
    clang_disposeIndex(index_);
}

unsigned int SourceIndex::
parse(const std::string& sourceFile, SourceIndex::VisitorFunctor& func)
{
    //
    // Build up list of args...
    //
    int nArgs = 3; // -c, -x, c++
    unsigned int idx = nArgs;
    nArgs += defines_.size() * 2;
    nArgs += includePaths_.size() * 2;

    const char* args[nArgs];
    args[0] = "-c";
    args[1] = "-x";
    args[2] = "c++";

    Defines::iterator i;
    for ( i=defines_.begin(); i!=defines_.end(); ++i )
    {
        args[idx++] = "-D";
        args[idx++] = i->c_str();
    }

    IncludePaths::iterator i2;
    for ( i2=includePaths_.begin(); i2!=includePaths_.end(); ++i2 )
    {
        args[idx++] = "-I";
        args[idx++] = i2->c_str();
    }

    CXTranslationUnit tu = clang_parseTranslationUnit(index_,
        sourceFile.c_str(), args, nArgs, 0, 0, CXTranslationUnit_None);

    CXCursor startCursor = clang_getTranslationUnitCursor(tu);

    return clang_visitChildren(startCursor, &SourceIndex::VisitorEntryPoint,
        &func);
}

CXChildVisitResult SourceIndex::
VisitorEntryPoint(CXCursor start, CXCursor parent, CXClientData clientData)
{
    SourceIndex::VisitorFunctor f =
        *(static_cast<SourceIndex::VisitorFunctor*>(clientData));

    return f(start, parent);
}
