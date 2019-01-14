#include "CacheManager.h"
#include <map>
#include <fstream>
#include <iostream>
#include <string.h>

#ifndef PROJECTNUM2_FILECACHEMANAGER_H
#define PROJECTNUM2_FILECACHEMANAGER_H

template<class T1, class T2>

class FileCacheManager : public CacheManager<string, string> {
    map <string, string> solutionMap;
public:

    /**
     * The function read the solution fike and save the information in a map
     */
    void readFile() {
        string line;
        string problem = "", solution;
        string inputFile = "solutionFile.txt";
        ifstream problemsFile(inputFile);
        if (problemsFile.is_open()) {
            while (getline(problemsFile, line)) {
                char *temp = const_cast<char *>(line.c_str());
                temp = strtok(temp, ";");
                while ((strcmp("end", temp)) != 0) {
                    problem += temp;
                    problem += ";";
                    temp = strtok(NULL, ";");
                }

                problem += "end";
                temp = strtok(NULL, ";");
                solution = temp;
                this->solutionMap.insert(
                        pair<string, string>(problem, solution));
                problem = "";
            }
            problemsFile.close();
        }
    }

    //Constructor
    FileCacheManager() {
        this->readFile();
    }

    /**
    * The function write to the file the new algoritim
     */
    void writeToFile(string problem, string solution) {
        string inputFile = "solutionFile.txt";
        ofstream problemsFile(inputFile, ios::app);
        if (problemsFile.is_open()) {
            problemsFile << problem;
            problemsFile << ";";
            problemsFile << solution;
            problemsFile << "\n";
        }
    }

    //Distructor
    virtual ~FileCacheManager() {};

    /**
       * The function returns returns a saved solution to a given problem.
     */
    string getSolution(string problem) {
        return this->solutionMap.find(problem)->second;
    }

    /**
    * The function receive a problem and solution and save them.
    */
    void saveSolution(string problem, string solution) {
        this->solutionMap.insert(pair<string, string>(problem, solution));
        writeToFile(problem, solution);
    }

    /**
     * The function returns if the solution to a given problem  was already solved and saved.
     */
    bool haveSolution(string problem) {
        if (this->solutionMap.count(problem)) {
            return true;
        }
        return false;
    }
};


#endif //PROJECTNUM2_FILECACHEMANAGER_H
