#include <vector>
#include "Bfs.h"
#include <unordered_set>
#include<vector>
#include <queue>

template<class T1, class T2, class T>

list<State<T>> Bfs<T1, T2, T>::search(Searchable<T2> searchable) {
    vector<State<T>> open;
    unordered_set<State<T>> close;
    vector<State<T>> successors;
    open.push_back(searchable.getInitialState());
    while (!open.empty()) {
        State<T> currentState = open[0];
        open.erase(open.begin());
        close.insert(currentState);
        if (currentState.equal(searchable.getGoalState())) {
            return this->createBackTrace(searchable, currentState);
        }
        successors = searchable.getAllPossibleStates(currentState);
        while (!successors.empty()) {
            for (int i = 0; i < successors.size(); i++) {
                if (!close.count(successors[i])) {
                    State<T> tempState = successors[i];
                    tempState.setCameFrom(currentState);
                    open.push_back(tempState);
                }
            }
        }
    }
}

template<class T1, class T2, class T>
list<State<T>> Bfs<T1, T2, T>::createBackTrace(Searchable<T2> searchable, State<T> goalState) {
    list<State<T>> backTrace;
    State<T> startState = searchable.getInitialState();
    while (!goalState.equal(startState)) {
        backTrace.push_front(goalState);
        goalState = goalState.getCameFrom();
    }
    backTrace.push_front(startState);
    return backTrace;

}