#ifndef PROJECTNUM2_STATE_H
#define PROJECTNUM2_STATE_H

template<class T>
class State {
    T state;
    double cost;
    State<T> cameFrom;
public:
    State(T state);
    virtual bool equal(State<T> state)=0;
};


#endif //PROJECTNUM2_STATE_H
