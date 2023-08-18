#ifndef AUTOMATA_H
#define AUTOMATA_H


#include <set>
#include <unordered_map>

// Automata interface
template <class Symbol>
class Automata {
public:
    virtual void reset() = 0;
    virtual bool isDone() const = 0;
    virtual void step(Symbol symbol) = 0;

};

template <class Symbol>
class DFA : Automata<Symbol> {
private:
    int current_state;
    std::set<int> final_states;
    std::unordered_map<std::pair<int, Symbol>, int> transitions;

public:
    DFA(std::unordered_map<std::pair<int, Symbol>, int> transitions, std::set<int> final_states)
    : current_state(0), transitions(transitions), final_states(final_states) {}

    void reset() {
        this->current_state= 0;
    }

    bool isDone() const {
        return final_states.count(this->current_state);
    }

    void step(Symbol symbol) {
        this->current_state = transitions[{this->current_state, symbol}];
    }
};

template <class T>
class NFA : Automata<T> {

};


#endif //AUTOMATA_H
