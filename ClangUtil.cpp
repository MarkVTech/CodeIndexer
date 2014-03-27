#include <iostream>

#include "ClangUtil.h"

std::ostream&
operator<<(std::ostream& stream, const LocationInfo& location)
{

    std::cout << location.filePath <<
        " line: " << location.line <<
        ", column: " << location.column <<
        ", offset: " << location.offset;

    return stream;
}

std::string
getClangString(CXString str)
{
    const char* tmp = clang_getCString(str);
    if (tmp == NULL)
    {
        return "";
    }
    else
    {
        std::string translated = std::string(tmp);
        clang_disposeString(str);
        return translated;
    }
}

LocationInfo
getLocationInfo(const CXSourceLocation& location)
{
    CXFile file;
    unsigned int line;
    unsigned int column;
    unsigned int offset;

    clang_getFileLocation(location, &file, &line, &column, &offset);

    return LocationInfo(getClangString(clang_getFileName(file)),
        line, column, offset);
}

LocationInfo
getLocationInfo(const CXCursor& cursor)
{
    CXFile file;
    unsigned int line;
    unsigned int column;
    unsigned int offset;

    CXSourceLocation location = clang_getCursorLocation(cursor);

    clang_getFileLocation(location, &file, &line, &column, &offset);

    return LocationInfo(getClangString(clang_getFileName(file)),
        line, column, offset);
}
