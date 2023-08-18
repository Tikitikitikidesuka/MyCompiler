#ifndef AUTOMATA_H
#define AUTOMATA_H


#include <unordered_map>
#include <vector>
#include <set>


// Automata interface
template <class T>
class Automata {
public:
    virtual void step(T input) = 0;
    virtual void reset() = 0;
    virtual bool isDone() = 0;
};

template <class T>
class DFA : Automata<T> {

};

template <class Symbol>
class NFA : Automata<Symbol> {
private:
    std::set<int> current_state;
    std::set<int> final_states;
    std::unordered_map<std::pair<int, Symbol>, std::vector<int>> transitions;

public:
    
    NFA(std::unordered_map<std::pair<int, Symbol>, std::vector<int>> transitions, std::set<int> final_states)
    : current_state({0}),transitions(transitions), final_states(final_states) {}
    void reset () {
        this->current_state = {0};
    } 
    bool isDone() {
        for (const int s : current_state) {
            if (final_states.count(s) > 0)  return true;
        }
        return false;
    }
    void step (Symbol symbol) {
        
    }

};


#endif //AUTOMATA_H
