#ifndef PROJECTNUM2_STATE_H
#define PROJECTNUM2_STATE_H

template<class VALUE>
class State {
    VALUE state;
public:
    VALUE getState() const;

    double getCost() const;

public:
    void setState(VALUE state);

private:
    double cost;
    State<VALUE> cameFrom;
public:
    State();
    virtual bool equal(State<VALUE> states);
    void setCameFrom(State<VALUE> states);
    State<VALUE> getCameFrom();

    void setCost(double cost);
};


#endif //PROJECTNUM2_STATE_H
