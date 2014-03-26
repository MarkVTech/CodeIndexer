#include <iostream>

#include "../ClangUtil.h"
#include "QObjectIndexer.h"

using namespace std;


QObjectIndexer::
QObjectIndexer() :
    currentRecord_(""),
    currentAccess_("private")
{}


unsigned int QObjectIndexer::
extractDestructor_(CXCursor cursor)
{
cout << endl << "============ DESTRUCTOR =====================" << endl;
    CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
    CXSourceRange range = clang_getCursorExtent(cursor);
            
    //
    // Tokenize the class, and annotate the tokens with cursors
    //
    CXToken* tokens = 0;
    unsigned int numTokens;
    clang_tokenize(tu, range, &tokens, &numTokens);

    CXCursor cursors[numTokens];
    clang_annotateTokens(tu, tokens, numTokens, cursors);
    cout << "numTokens " << numTokens << endl;

    string cursorSpelling =
         getClangString(clang_getCursorSpelling(cursor));
    cout << "Method is " << cursorSpelling << endl;
    //getClangString(clang_getTypeSpelling(type )) << endl;


    for ( unsigned int idx=0; idx<numTokens; ++idx)
    {
        string tokenStr = getClangString(clang_getTokenSpelling(tu,
            tokens[idx]));
        cout << "\ttoken: " << tokenStr;
        cout << "\tcursor: " <<
            getClangString(clang_getCursorSpelling(cursors[idx]));
        cout << "\tcursor kind: " <<
            getClangString(clang_getCursorKindSpelling(cursors[idx].kind)) << endl;
    }
cout << "=========================================" << endl << endl;

    return numTokens;

}

unsigned int QObjectIndexer::
extractBaseSpec_(CXCursor cursor)
{
cout << endl << "============ BASE SPEC ======================" << endl;
    CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
    CXSourceRange range = clang_getCursorExtent(cursor);
            
    //
    // Tokenize the class, and annotate the tokens with cursors
    //
    CXToken* tokens = 0;
    unsigned int numTokens;
    clang_tokenize(tu, range, &tokens, &numTokens);

    CXCursor cursors[numTokens];
    clang_annotateTokens(tu, tokens, numTokens, cursors);
    cout << "numTokens " << numTokens << endl;

    string cursorSpelling =
         getClangString(clang_getCursorSpelling(cursor));
    cout << "Base class is " << cursorSpelling << endl;
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
        cout << "\ttoken: " << tokenStr;
        cout << "\tcursor: " <<
            getClangString(clang_getCursorSpelling(cursors[idx]));
        cout << "\tcursor kind: " <<
            getClangString(clang_getCursorKindSpelling(cursors[idx].kind)) << endl;
    }
cout << "=========================================" << endl << endl;

    return numTokens;

}

unsigned int QObjectIndexer::
extractConstructor_(CXCursor cursor)
{
cout << endl << "============ CONSTRUCTOR =====================" << endl;
    CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
    CXSourceRange range = clang_getCursorExtent(cursor);
            
    //
    // Tokenize the class, and annotate the tokens with cursors
    //
    CXToken* tokens = 0;
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
        cout << "\ttoken: " << tokenStr;
        cout << "\tcursor: " <<
            getClangString(clang_getCursorSpelling(cursors[idx]));
        cout << "\tcursor kind: " <<
            getClangString(clang_getCursorKindSpelling(cursors[idx].kind)) << endl;

        CXCursorKind cursorKind = cursors[idx].kind;
        if ( cursorKind == CXCursor_ParmDecl )
        {
            idx += extractParmDecl_(cursors[idx])-1;
        }
    }
cout << "=========================================" << endl << endl;

    return numTokens;

}

unsigned int QObjectIndexer::
extractClassMethod_(CXCursor cursor)
{
cout << endl << "============ METHOD =====================" << endl;
    CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
    CXSourceRange range = clang_getCursorExtent(cursor);
            
    //
    // Tokenize the class, and annotate the tokens with cursors
    //
    CXToken* tokens = 0;
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
        cout << "\ttoken: " << tokenStr;
        cout << "\tcursor: " <<
            getClangString(clang_getCursorSpelling(cursors[idx]));
        cout << "\tcursor kind: " <<
            getClangString(clang_getCursorKindSpelling(cursors[idx].kind)) << endl;

        CXCursorKind cursorKind = cursors[idx].kind;
        if ( cursorKind == CXCursor_ParmDecl )
        {
            idx += extractParmDecl_(cursors[idx])-1;
        }
    }

    string lastToken =
        getClangString(clang_getTokenSpelling(tu, tokens[numTokens-1]));
        if ( lastToken == "public" || lastToken == "private" ||
                lastToken == "protected" || lastToken == "signals" )
            numTokens -= 1;
        
cout << "=========================================" << endl << endl;

    return numTokens;
}

unsigned int QObjectIndexer::
extractParmDecl_(CXCursor cursor)
{
cout << endl << "============ PARM =====================" << endl;
    CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
    CXSourceRange range = clang_getCursorExtent(cursor);
            
    //
    // Tokenize the class, and annotate the tokens with cursors
    //
    CXToken* tokens = 0;
    unsigned int numTokens;
    clang_tokenize(tu, range, &tokens, &numTokens);

    CXCursor cursors[numTokens];
    clang_annotateTokens(tu, tokens, numTokens, cursors);
    cout << "numTokens " << numTokens << endl;

    string cursorSpelling =
         getClangString(clang_getCursorSpelling(cursor));
    cout << "Parm is " << cursorSpelling << endl;

    for ( unsigned int idx=0; idx<numTokens; ++idx)
    {
        string tokenStr = getClangString(clang_getTokenSpelling(tu,
            tokens[idx]));
        cout << "\ttoken: " << tokenStr;
        cout << "\tcursor: " <<
            getClangString(clang_getCursorSpelling(cursors[idx]));
        cout << "\tcursor kind: " <<
            getClangString(clang_getCursorKindSpelling(cursors[idx].kind)) << endl;
    }

    string lastToken =
        getClangString(clang_getTokenSpelling(tu, tokens[numTokens-1]));
        if ( lastToken == "public" || lastToken == "private" ||
                lastToken == "protected" || lastToken == "signals" )
            numTokens -= 1;
        
cout << "=========================================" << endl << endl;

    return numTokens;
}

unsigned int QObjectIndexer::
extractFieldDecl_(CXCursor cursor)
{
cout << endl << "============ FIELD DECL ================" << endl;
    CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
    CXSourceRange range = clang_getCursorExtent(cursor);
            
    //
    // Tokenize the class, and annotate the tokens with cursors
    //
    CXToken* tokens = 0;
    unsigned int numTokens;
    clang_tokenize(tu, range, &tokens, &numTokens);

    CXCursor cursors[numTokens];
    clang_annotateTokens(tu, tokens, numTokens, cursors);
    cout << "numTokens " << numTokens << endl;

    string cursorSpelling =
         getClangString(clang_getCursorSpelling(cursor));
    cout << "Field is " << cursorSpelling << endl;
    CXType type = clang_getCursorType(cursor);
    cout << "\tType is " << 
        getClangString(clang_getTypeSpelling(type)) << endl;

cout << "=========================================" << endl << endl;
    return numTokens;
}

unsigned int QObjectIndexer::
extractEnumDecl_(CXCursor cursor)
{
cout << endl << "=============== ENUM ==================" << endl;
    CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
    CXSourceRange range = clang_getCursorExtent(cursor);
            
    //
    // Tokenize the class, and annotate the tokens with cursors
    //
    CXToken* tokens = 0;
    unsigned int numTokens;
    clang_tokenize(tu, range, &tokens, &numTokens);

    CXCursor cursors[numTokens];
    clang_annotateTokens(tu, tokens, numTokens, cursors);
    cout << "numTokens " << numTokens << endl;

    string cursorSpelling =
         getClangString(clang_getCursorSpelling(cursor));
    cout << "Field is " << cursorSpelling << endl;
    CXType type = clang_getCursorType(cursor);
    cout << "\tType is " << 
        getClangString(clang_getTypeSpelling(type)) << endl;

    for ( unsigned int idx=0; idx<numTokens; ++idx)
    {
        string tokenStr = getClangString(clang_getTokenSpelling(tu,
            tokens[idx]));
        cout << "\ttoken: " << tokenStr;
        cout << "\tcursor: " <<
            getClangString(clang_getCursorSpelling(cursors[idx]));
        cout << "\tcursor kind: " <<
            getClangString(clang_getCursorKindSpelling(cursors[idx].kind)) << endl;
    }
cout << "=========================================" << endl << endl;

    return numTokens;
}

unsigned int QObjectIndexer::
extractRecord_(CXCursor cursor, const string& parentName)
{
cout << endl << "=============== RECORD ==================" << endl;
cout << "* parentName is " << parentName << " *" << endl;
    unsigned int numTokens=0;

    string tokenStr = "";
    string currentAccess = "";

    //
    // For now, only want to process the main file of interest...
    //
    if ( !clang_Location_isFromMainFile(clang_getCursorLocation(cursor)) )
        return CXChildVisit_Continue;

    string cursorSpelling =
         getClangString(clang_getCursorSpelling(cursor));
    
    string thisCursor = cursorSpelling;
    cout << "thisCursor = " << thisCursor << endl;

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
        //unsigned int numTokens = 0;
        clang_tokenize(tu, range, &tokens, &numTokens);

        CXCursor cursors[numTokens];
        clang_annotateTokens(tu, tokens, numTokens, cursors);

        //
        // Dissect the class
        //
        for ( unsigned int tidx=0; tidx<numTokens; ++tidx)
        {
            tokenStr = getClangString(clang_getTokenSpelling(tu,
                tokens[tidx]));
            cout << "token[" << tidx << "] = " << tokenStr <<  endl;

            CXCursorKind cursorKind = cursors[tidx].kind;

            if ( cursorKind == CXCursor_Constructor )
            {
                tidx += extractConstructor_(cursors[tidx])-1;
            }

            if ( cursorKind == CXCursor_Destructor )
            {
                tidx += extractDestructor_(cursors[tidx])-1;
            }

            if ( cursorKind == CXCursor_CXXBaseSpecifier )
            {
                tidx += extractBaseSpec_(cursors[tidx]) - 1;
            }

            if ( cursorKind == CXCursor_CXXMethod )
            {
                tidx += extractClassMethod_(cursors[tidx])-1;
            }

            if ( cursorKind == CXCursor_ParmDecl )
            {
                tidx += extractParmDecl_(cursors[tidx])-1;
            }

            if ( cursorKind == CXCursor_FieldDecl )
            {
                tidx += extractFieldDecl_(cursors[tidx])-1;
            }

            if ( cursorKind == CXCursor_EnumDecl )
            {
                tidx += extractEnumDecl_(cursors[tidx]);
            }

            if ( parentName == thisCursor && cursorKind == CXCursor_StructDecl )
            {
                string nextCursorSpelling =
                    getClangString(clang_getCursorSpelling(cursors[tidx]));
                tidx += extractRecord_(cursors[tidx], cursorSpelling)-1;
            }

            if ( tokenStr == "public" || tokenStr == "protected" ||
                    tokenStr == "private" )
            {
                currentAccess_ = tokenStr;
                ++tidx;
                tokenStr = getClangString(clang_getTokenSpelling(tu,
                    tokens[tidx]));
                if (  tokenStr == "slots" )
                    currentAccess_ += "slots";
                cout << "currentAccess_ = " << currentAccess_ << endl;
                ++tidx;
                continue;
            }
            if ( tokenStr == "signals" )
            {
                currentAccess_ = "signals";
                cout << "currentAccess_ = " << currentAccess_ << endl;
                continue;
            }
       }
       }
cout << "Returning " << numTokens << " tokens" << endl;
cout << "=========================================" << endl << endl;

    return numTokens;
}

CXChildVisitResult QObjectIndexer::
visit(CXCursor cursor, CXCursor parent)
{
    //string parentSpelling =
         //getClangString(clang_getCursorSpelling(parent));
     //cout << "***** parent is " << parentSpelling << endl;

    string tokenStr = "";
    string currentAccess = "";

    //
    // For now, only want to process the main file of interest...
    //
    if ( !clang_Location_isFromMainFile(clang_getCursorLocation(cursor)) )
        return CXChildVisit_Continue;

     cout << "\tparent kind is " << 
        getClangString(clang_getCursorKindSpelling(parent.kind)) << endl;


    string cursorSpelling =
         getClangString(clang_getCursorSpelling(cursor));

    CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
    CXSourceRange range = clang_getCursorExtent(cursor);

    if ( cursor.kind == CXCursor_ClassDecl ||
            cursor.kind == CXCursor_StructDecl )
    {
        if ( cursor.kind == CXCursor_ClassDecl )
            currentAccess = "private";
        else
            currentAccess = "public";
            
cout << "Top cursor is " << cursorSpelling << endl;
        extractRecord_(cursor, cursorSpelling);
        //
        // Tokenize the class, and annotate the tokens with cursors
        //
        CXToken* tokens = 0;
        unsigned int numTokens;
        clang_tokenize(tu, range, &tokens, &numTokens);

        CXCursor cursors[numTokens];
        clang_annotateTokens(tu, tokens, numTokens, cursors);


    } // end of class/struct decl

    return CXChildVisit_Continue;
}

ostream&
operator<<(ostream& stream, const QObjectIndexer::MethodType& mt)
{
    switch(mt)
    {
    case QObjectIndexer::NORMAL:
        cout << "NORMAL";
        break;
    case QObjectIndexer::SLOT:
        cout << "SLOT";
        break;
    case QObjectIndexer::SIGNAL:
        cout << "SIGNAL";
        break;
    };

    return stream;
}

ostream&
operator<<(ostream& stream, const QObjectIndexer::AccessLocation& al)
{
    cout << al.second << "@" << al.first;

    return stream;
}
