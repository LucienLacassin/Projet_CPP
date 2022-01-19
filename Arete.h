#include <iostream>
#include <string>

class Arete {

private : 

    std::string sommet_origine;
    std::string sommet_adja;
    double valeur_arete;

public :

    Arete(std::string o, std::string a, double v) :
        sommet_origine(o),
        sommet_adja(a),
        valeur_arete(v) {}

    void print() {

        std::cout << sommet_origine << ", " << valeur_arete << ", " << sommet_adja << std::endl;

    }

    double value() {

        return valeur_arete;

    }

    std::string sommet1() {

        return sommet_origine;
    }
    
    std::string sommet2() {

        return sommet_adja;
    }
    
};