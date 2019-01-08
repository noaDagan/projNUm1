#include "Searchable.h"
#include <vector>
#include "State.h"
#include "string"
#include <string.h>
#ifndef PROJECTNUM2_MATRIX_H
#define PROJECTNUM2_MATRIX_H

template < class VALUE>
class Matrix : public Searchable <VALUE> {
    vector<vector<State<VALUE>>> matrixArray;
    State <VALUE> initialState;
    State <VALUE> goalState;
    int countRow;

public:
    Matrix();
    void addRow(string row);
    void setInitialState(State <VALUE> initialState);
    void setGoalState(State <VALUE> goalState);
    virtual State <VALUE> getInitialState();
    virtual State <VALUE> getGoalState();
    virtual list<State<VALUE>> getAllPossibleStates(State<string> state);
    State <VALUE> getStateByIndex(int row,int col);
};


#endif //PROJECTNUM2_MATRIX_H
