#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "Sommet.h"

class Liste {

private :

    std::vector<Sommet> list;


public :

    Liste(std::vector<Sommet> l) :
        list(l) {}
    

    void push_back(Sommet S) {

        list.push_back(S);
    }

    void print() {

        for (int i = 0; i < list.size(); i++) {

            std::cout << list[i].Sommet::name() << std::endl;
        }
    }

    Sommet ret(int i) {

        return list[i];

    }

    int size() {

        return list.size();
    }

    std::vector<Sommet>::iterator begin () {

        return list.begin();
    }

    void erase (std::vector<Sommet>::iterator it) {

        list.erase(it);
    }

};