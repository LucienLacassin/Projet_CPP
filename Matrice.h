#include <iostream>
#include <vector>
#include <string>

class Matrice {

private :

    std::vector<std::string> liste_sommets;
    std::vector<std::vector<double> > matrice;

public :

    Matrice(std::vector<std::string> l, std::vector<std::vector<double> > m) :
        liste_sommets(l),
        matrice(m) {}

    void print() {
        
        int lignes = matrice.size();
        int colonnes = matrice[0].size();

        for (int i = 0; i < lignes; i++) {

            for (int j = 0; j < colonnes; j++) {

                std::cout << matrice[i][j] << ' ';
            }

            std::cout << std::endl;
        }

    }

    std::vector<std::string> nom_sommets () {

        return liste_sommets;
    }

    std::vector<std::vector<double> > mat () {

        return matrice;
    }

    void modif (int i, int j, double d) {

        matrice[i][j] = d;
        
    }

} ;