#include "State.h"
#include <list>
#ifndef PROJECTNUM2_SEARCHABLE_H
#define PROJECTNUM2_SEARCHABLE_H

using namespace std;

template <class T>
class Searchable   {
public:
    virtual State <T> getInitialState() = 0;
    virtual State <T> getGoalState() = 0;
    virtual list<State<T>> getAllPossibleStates(State<T> s) = 0;
};
#endif //PROJECTNUM2_SEARCHABLE_H
