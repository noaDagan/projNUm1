#include "Searchable.h"
#ifndef PROJECTNUM2_SEARCHER_H
#define PROJECTNUM2_SEARCHER_H

template <class T1,class T>
class Searcher {
public:
    virtual T1 search (Searchable<T> searchable) = 0;
    virtual int getNumberOfNodesEvaluated() = 0;
};

#endif //PROJECTNUM2_SEARCHER_H
