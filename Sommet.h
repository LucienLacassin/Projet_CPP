#include <iostream>
#include <vector>
#include <string>
#include "Arete.h"

class Sommet {

private :

    std::string nom;
    std::vector<Arete> adjacence;
    
public :

    Sommet(std::string n, std::vector<Arete> a) :
        nom(n),
        adjacence(a) {}

    void print() {

        int S_range = adjacence.size();

        std::cout << nom << ' ' << std::endl;

        int i = 0;

        while (i < S_range - 1) {

            adjacence[i].Arete::print();

            std::cout << ',';

            i++;
        }

        adjacence[i].Arete::print();

        std::cout << std::endl;
    }

    std::string name() {

        return nom;

    }

    std::vector<Arete> adja() {

        return adjacence;

    }

} ;




