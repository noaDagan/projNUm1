#include "CacheManager.h"
#include <map>
#include <fstream>
#include <iostream>
#include <string.h>

#ifndef PROJECTNUM2_FILECACHEMANAGER_H
#define PROJECTNUM2_FILECACHEMANAGER_H

template <class T1, class  T2>

class FileCacheManager : public CacheManager <string,string> {
    map<string,string> solutionMap;
public:
    void readFile();
    FileCacheManager();
    ~FileCacheManager();
    virtual bool haveSolution(string problem);
    virtual string getSolution(string problem);
    virtual void saveSolution(string problem, string solution);
};


#endif //PROJECTNUM2_FILECACHEMANAGER_H
