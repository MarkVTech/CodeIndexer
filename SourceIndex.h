#ifndef _INDEX_H_
#define _INDEX_H_

#include <string>
#include <vector>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <Index.h>

class SourceIndex
{
public:
    typedef std::vector<std::string> Defines;
    typedef std::vector<std::string> IncludePaths;
    typedef boost::function<CXChildVisitResult(CXCursor, CXCursor)>
        VisitorFunctor;

    SourceIndex(const Defines& defines, const IncludePaths& includePaths);
    ~SourceIndex();

    unsigned int parse(const std::string& sourceFile, VisitorFunctor& func);

private:
    Defines defines_;
    IncludePaths includePaths_;

    CXIndex index_;

    static CXChildVisitResult VisitorEntryPoint(CXCursor start, CXCursor parent,
        CXClientData clientData);
};

#endif
