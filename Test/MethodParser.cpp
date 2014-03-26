#include <iostream>

#include "../ClangUtil.h"
#include "MethodParser.h"

using namespace std;


MethodParser::
MethodParser() :
    currentAccess_("private")
{}

bool MethodParser::
checkForSlot(CXTranslationUnit tu, CXToken** tokenPtr)
{
    string token;

    ++(*tokenPtr);
    token = getClangString(clang_getTokenSpelling(tu,
        **tokenPtr));

    if ( token == "slots" )
    {
        cout << "slots found" << endl;
        ++(*tokenPtr);
        token = getClangString(clang_getTokenSpelling(tu,
            **tokenPtr));
        if ( token == ":" )
        {
            //
            // After we return true, the calling function will find the
            // token pointer aimed at first token after "slots:"
            //
            ++(*tokenPtr);
            return true;
        }
        return false;
    }
    return false;
}

/**
* Finds and records locations of 'public:', 'private:', 'protected:',
* 'public slots:', 'protected slots:', 'private slots:', and 'signals:'
*/
void MethodParser::
tokenizeClass(CXCursor cursor)
{
    CXCursor slotCursor;

    CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
    CXSourceRange range = clang_getCursorExtent(cursor);
    CXSourceLocation rangeStart = clang_getRangeStart(range);

    LocationInfo li = getLocationInfo(rangeStart);
    accessLocations_.push_back(make_pair(li, NORMAL));


    CXToken* tokens = 0;
    CXToken* tokenPtr=tokens;
    unsigned int numTokens;
    clang_tokenize(tu, range, &tokens, &numTokens);

    if ( numTokens > 0 )
    {
        for ( tokenPtr=tokens; tokenPtr != tokens+numTokens; tokenPtr++ )
        {
            string token = getClangString(clang_getTokenSpelling(tu,
                *tokenPtr));
            cout << "token is " << token << endl;

            if ( token == "public" || token == "protected" ||
                token == "private" )
            {
                // 
                // Check for "slots:"; if found, tokenPtr will be aimed
                // at the token just after "slots:"
                //
                if ( checkForSlot(tu, &tokenPtr) )
                {
                    string token = getClangString(clang_getTokenSpelling(tu,
                        *tokenPtr));

                    CXSourceLocation tl = clang_getTokenLocation(tu, *tokenPtr);

                    LocationInfo li = getLocationInfo(tl);
                    cout << "\tLocation is: " << li << endl;

                    accessLocations_.push_back(make_pair(li, SLOT));
                    slotCursor = clang_getCursor(tu, tl);
                }
            }
            else if ( token == "signals" )
            {
                tokenPtr++;
                string token = getClangString(clang_getTokenSpelling(tu,
                   *tokenPtr));
                if ( token == ":" )
                {
                    cout << "signals found" << endl;
                    tokenPtr++;
                    //
                    // tokenPtr now aimed at token just after 'signals:'
                    //
                    string token = getClangString(clang_getTokenSpelling(tu,
                        *tokenPtr));
                    CXSourceLocation tl = clang_getTokenLocation(tu, *tokenPtr);
                    LocationInfo li = getLocationInfo(tl);
                    cout << "\tToken is " << token  << " at " << li << endl;
                    accessLocations_.push_back(make_pair(li, SIGNAL));
                }
            }
            //
            // Neither slot nor signal...
            //
            CXSourceLocation tl = clang_getTokenLocation(tu, *tokenPtr);
            LocationInfo li = getLocationInfo(tl);
            accessLocations_.push_back(make_pair(li, NORMAL));
        }
    }
}

unsigned int MethodParser::
extractClassMethod_(CXCursor cursor)
{
cout << endl << "=========================================" << endl;
    CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
    CXSourceRange range = clang_getCursorExtent(cursor);
            
    //
    // Tokenize the class, and annotate the tokens with cursors
    //
    CXToken* tokens = 0;
    CXToken** tokenPtr = 0;
    unsigned int numTokens;
    clang_tokenize(tu, range, &tokens, &numTokens);

    CXCursor cursors[numTokens];
    clang_annotateTokens(tu, tokens, numTokens, cursors);
    cout << "numTokens " << numTokens << endl;

    string cursorSpelling =
         getClangString(clang_getCursorSpelling(cursor));
    cout << "Method is " << cursorSpelling << endl;
    //getClangString(clang_getTypeSpelling(type )) << endl;
    int nargs = clang_Cursor_getNumArguments(cursor);

    for ( int i=0; i < nargs; i++ )
    {
        CXCursor arg = clang_Cursor_getArgument(cursor, i);
        CXType argType = clang_getCursorType(arg);
        CXType canArgType = clang_getCanonicalType(argType);
        cout << "\tArg type is " <<
        getClangString(clang_getTypeSpelling(canArgType)) << endl;
    }


    for ( unsigned int idx=0; idx<numTokens; ++idx)
    {
        string tokenStr = getClangString(clang_getTokenSpelling(tu,
            tokens[idx]));
        cout << "\t\ttoken: " << tokenStr << endl;
    }
cout << "=========================================" << endl << endl;

    return numTokens;

}

CXChildVisitResult MethodParser::
visit(CXCursor cursor, CXCursor parent)
{
    string tokenStr = "";
    string currentAccess = "";
    CXSourceRange workingRange = clang_getNullRange();

    //
    // For now, only want to process the main file of interest...
    //
    if ( !clang_Location_isFromMainFile(clang_getCursorLocation(cursor)) )
        return CXChildVisit_Continue;


    CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
    CXSourceRange range = clang_getCursorExtent(cursor);

    if ( cursor.kind == CXCursor_ClassDecl ||
            cursor.kind == CXCursor_StructDecl )
    {
        if ( cursor.kind == CXCursor_ClassDecl )
            currentAccess = "private";
        else
            currentAccess = "public";
            
        //
        // Tokenize the class, and annotate the tokens with cursors
        //
        CXToken* tokens = 0;
        unsigned int numTokens;
        clang_tokenize(tu, range, &tokens, &numTokens);

        CXCursor cursors[numTokens];
        clang_annotateTokens(tu, tokens, numTokens, cursors);

        //
        // Dissect the class
        //
        for ( unsigned int tidx=0; tidx<numTokens; ++tidx)
        {
            CXCursorKind cursorKind = cursors[tidx].kind;
            if ( cursorKind == CXCursor_CXXMethod )
            {
                tidx += extractClassMethod_(cursors[tidx]);
            }

            if ( tidx > 1 && getClangString(clang_getTokenSpelling(tu,
                    tokens[tidx-1])) == "slots" )
            {
                string tokenStr = getClangString(clang_getTokenSpelling(tu,
                    tokens[tidx-2]));
                if ( tokenStr == "public" || tokenStr == "protected" ||
                        tokenStr == "private" )
                {
                    cout << tokenStr << " slots:" << endl;
                }
            }
            else if ( tidx > 2 && getClangString(clang_getTokenSpelling(tu,
                     tokens[tidx-2])) == "signals" )
            {
                cout << "signals:" << endl;
            }


        } // end of for loop

    } // end of class/struct decl

    return CXChildVisit_Continue;
}

ostream&
operator<<(ostream& stream, const MethodParser::MethodType& mt)
{
    switch(mt)
    {
    case MethodParser::NORMAL:
        cout << "NORMAL";
        break;
    case MethodParser::SLOT:
        cout << "SLOT";
        break;
    case MethodParser::SIGNAL:
        cout << "SIGNAL";
        break;
    };

    return stream;
}

ostream&
operator<<(ostream& stream, const MethodParser::AccessLocation& al)
{
    cout << al.second << "@" << al.first;

    return stream;
}
