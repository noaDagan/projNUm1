
#include "Matrix.h"

template<class VALUE>
Matrix<VALUE>::Matrix() {
    this->countRow = 0;
}

template<class VALUE>
State<VALUE> Matrix<VALUE>::getInitialState() {
    return this->initialState;
}

template<class VALUE>
State<VALUE> Matrix<VALUE>::getGoalState() {
    return this->goalState;
}

template<class VALUE>
void Matrix<VALUE>::setGoalState(State<VALUE> goalState) {
    this->goalState = goalState;
}

template<class VALUE>
void Matrix<VALUE>::setInitialState(State<VALUE> initialState) {
    this->initialState = initialState;
}

template<class VALUE>
void Matrix<VALUE>::addRow(string row) {
    vector<State<VALUE>> rowVector;
    double cost;
    char *temp = const_cast<char *>(row.c_str());
    temp = strtok(temp, ",");
    int col = 0;
    while (temp != "") {
        cost = atof(temp);
        temp = strtok(NULL, ",");
        State<string> newState = new State<string>();
        string name = to_string(this->countRow) + "," + to_string(col);
        newState.setState(name);
        newState.setCost(cost);
        rowVector.push_back(newState);
        col++;
    }
    this->matrixArray.push_back(rowVector);
    this->countRow++;

}

template<class VALUE>
State<VALUE> Matrix<VALUE>::getStateByIndex(int row, int col) {
    return this->matrixArray[row][col];
}

template<class VALUE>
list<State<VALUE>> Matrix<VALUE>::getAllPossibleStates(State<string> state) {
    list<State<string>> possibleStates;
    string name = state.getState();
    char *index = const_cast<char *>(name.c_str());
    index = strtok(index, ",");
    int i = stoi(index);
    index = strtok(NULL, ",");
    int j = stoi(index);
    int sizeOfRow = this->matrixArray[i].size();
    if (i != 0) {
        possibleStates.insert(this->matrixArray[i - 1][j]);
    }
    if (j != 0) {
        possibleStates.insert(this->matrixArray[i][j - 1]);
    }
    if (j < sizeOfRow - 1) {
        possibleStates.insert(this->matrixArray[i][j + 1]);
    }
    if (i < this->countRow) {
        possibleStates.insert(this->matrixArray[i + 1][j]);
    }
    return possibleStates;
}