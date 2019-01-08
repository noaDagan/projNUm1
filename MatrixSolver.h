
#include "Solver.h"
#include <string>
#include "Matrix.h"
#include "Searcher.h"
#include "Searchable.h"
#ifndef PROJECTNUM2_MATRIXSOLVER_H
#define PROJECTNUM2_MATRIXSOLVER_H
using namespace std;

template <class PROBLEM, class SOLUTION>
class MatrixSolver : public Solver <PROBLEM, SOLUTION> {
    Searcher<PROBLEM>* searcher;
public:
    MatrixSolver(Searcher<PROBLEM>* s);
    virtual string solve(string problem) = 0;
    Matrix<string>* createMatrix(string values);
};


#endif //PROJECTNUM2_MATRIXSOLVER_H
