
#include "MatrixSolver.h"

template<class PROBLEM, class SOLUTION>

MatrixSolver<PROBLEM, SOLUTION>::MatrixSolver(Searcher<PROBLEM>* s) {
    this->searcher = s;
}

template<class PROBLEM, class SOLUTION>
string MatrixSolver<PROBLEM, SOLUTION>::solve(string problem) {
    Searchable<string> *matrix=this->createMatrix(problem);

}

template<class PROBLEM, class SOLUTION>
Matrix<string>* MatrixSolver<PROBLEM, SOLUTION>::createMatrix(string values) {
    Matrix<string> *matrix = new Matrix<string>();
    char *temp = const_cast<char *>(values.c_str());
    temp = strtok(temp, ";");
    while (temp != "end") {
        string s = temp;
        matrix->addRow(s);
        temp = strtok(NULL, ";");
    }
    temp = strtok(temp, ";");
    string initializeState = temp;
    char *index = const_cast<char *>(initializeState.c_str());
    index =strtok(temp, ",");
    int i=stoi(index);
    index =strtok(NULL, ",");
    int j = stoi(index);
    matrix->setInitialState(matrix->getStateByIndex(i,j));
    temp = strtok(temp, ";");
     initializeState = temp;
    index = const_cast<char *>(initializeState.c_str());
    index =strtok(temp, ",");
     i=stoi(index);
    index =strtok(NULL, ",");
    j = stoi(index);
    matrix->setGoalState(matrix->getStateByIndex(i,j));
    return matrix;
}