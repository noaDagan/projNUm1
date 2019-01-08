#include "Searcher.h"
#include "list"
#include "State.h"
#include "Searchable.h"
#ifndef PROJECTNUM2_BFS_H
#define PROJECTNUM2_BFS_H

template <class T1,class T2, class T>
class Bfs : public Searcher<T1,T2>{
public:
    Bfs();
    virtual list<State<T>> search (Searchable<T2> searchable);
    virtual int getNumberOfNodesEvaluated();
    list<State<T>>createBackTrace(Searchable<T2> searchable, State<T> goalState);
};


#endif //PROJECTNUM2_BFS_H
