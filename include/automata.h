#ifndef AUTOMATA_H
#define AUTOMATA_H


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

template <class T>
class NFA : Automata<T> {

};


#endif //AUTOMATA_H
