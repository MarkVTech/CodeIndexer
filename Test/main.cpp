#include <iostream>

#include <boost/bind.hpp>

#include "../SourceIndex.h"
#include "QObjectIndexer.h"

using namespace std;

int
main(int argc, char** argv)
{
    SourceIndex::Defines defines;
    defines.push_back("slots=");
    defines.push_back("signals=public=");
    defines.push_back("QOBJECT=");
    defines.push_back("Q_PROPERTY=");

    SourceIndex::IncludePaths paths;
    paths.push_back("/usr/local/Trolltech/Qt-4.8.5/include");
    paths.push_back("/usr/local/Trolltech/Qt-4.8.5/include/QtCore");

    SourceIndex si(defines, paths);

    std::string path = "./exampleSrc/Counter.h";
    QObjectIndexer mp;
    SourceIndex::VisitorFunctor f = boost::bind(&QObjectIndexer::visit,
        mp, _1, _2);
    si.parse(path, f);
}
