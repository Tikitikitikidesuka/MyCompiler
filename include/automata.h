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

class DFA : Automata {

};

class NFA : Automata {

};


#endif //AUTOMATA_H
