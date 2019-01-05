

#ifndef PROJECTNUM2_SOLVER_H
#define PROJECTNUM2_SOLVER_H


template<class T1, class T2>
class Solver {
public:
    virtual T2 solve(T1 problem) = 0;
};


#endif //PROJECTNUM2_SOLVER_H
