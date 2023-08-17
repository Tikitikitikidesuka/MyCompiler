#ifndef AUTOMATA_H
#define AUTOMATA_H


// Automata interface
class Automata {
public:
    virtual int step() = 0;
    virtual int reset() = 0;
};

class DFA : Automata {

};

class NFA : Automata {

};


#endif //AUTOMATA_H
