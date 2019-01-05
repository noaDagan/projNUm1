
#include <string>
#ifndef PROJECTNUM2_CACHMANNAGER_H
#define PROJECTNUM2_CACHMANNAGER_H
using namespace std;

template <class T1, class  T2>
class CacheManager {
public:
    virtual bool haveSolution(T1 problem) = 0;
    virtual T2 getSolution(T1 problem) = 0;
    virtual void saveSolution(T1 problem, T2 solution) = 0;

};


#endif //PROJECTNUM2_CACHMANNAGER_H
