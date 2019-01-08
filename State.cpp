#include "State.h"

template <class VALUE>
State<VALUE>::State() {
}

template <class VALUE>
State<VALUE> State<VALUE>::getCameFrom() {
    return this->cameFrom;
}

template <class VALUE>
bool State<VALUE>::equal(State<VALUE> states) {
    return this->state == states.state;
}

template <class VALUE>
void State<VALUE>::setCameFrom(State<VALUE> states) {
    this->state = states.state;
}


template<class VALUE>
void State<VALUE>::setCost(double cost) {
    State::cost = cost;
}

template<class VALUE>
void State<VALUE>::setState(VALUE state) {
    State::state = state;
}

template<class VALUE>
VALUE State<VALUE>::getState() const {
    return state;
}

template<class VALUE>
double State<VALUE>::getCost() const {
    return cost;
}
