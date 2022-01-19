#include "Listes.h" 
#include "Matrice.h" 
#include <limits>
#include <map>
#include <stack>
#include <queue>
#include <iterator>
#include <cmath>

// 1. Fonction pour passer de l'une à l'autre


Matrice Liste_vers_matrice (Liste liste_sommets) {

    // On récupère le nom des sommets et leur indice

    // On parcourt toutes les listes d'adjacence, et on note les valeurs des aretes qui existent dans la matrice à l'aide du dictionnaire pour 
    // passer de l'indice dans la liste d'adjacence à l'indice absolu

    int nb_sommet = liste_sommets.size();

    std::vector<std::string> nom_sommet(nb_sommet, " ");

    std::vector<std::vector<double> > matrice_sommet(nb_sommet, std::vector<double> (nb_sommet, std::numeric_limits<double>::infinity()));

    std::map <std::string, int> indice_sommet; // Le dictionnaire

    for (int i = 0; i < nb_sommet; i++) {

        indice_sommet[liste_sommets.ret(i).Sommet::name()] = i;

        nom_sommet[i] = liste_sommets.ret(i).Sommet::name();

    } 

    for (int i = 0; i < nb_sommet; i++) {

        std::string sommet_i = nom_sommet[i];

        std::vector<Arete> adja_i = liste_sommets.ret(i).Sommet::adja();

        int nb_adja_i = adja_i.size();

        for (int j = 0; j < nb_adja_i; j++) {

            std::string sommet_j = adja_i[j].Arete::sommet2();

            int indice_j = indice_sommet[sommet_j]; 

            matrice_sommet[i][indice_j] = adja_i[j].Arete::value();
        }

    }

    Matrice P(nom_sommet, matrice_sommet);

    return P;

}

void Test1 () {

    Arete a1("A", "B", 1.23);
    Arete a2("A", "C", 2.21);
    Arete b1("B", "C", 3.76);
    Arete c1("C", "A", 2.16);
    Arete c2("C", "B", 0.97);
    
    Sommet A("A", {a1, a2});
    Sommet B("B", {b1});
    Sommet C("C", {c1, c2});
    
    std::vector<Sommet> Liste = {A, B, C};

    Matrice M = Liste_vers_matrice(Liste);

    M.Matrice::print();
}

Liste Matrice_vers_liste (Matrice P) {

    // On récupère le nom des sommets et la matrice

    // On parcourt la matrice ligne par ligne

    // Pour chaque ligne, si la valeur de la colonne j est < inf, on ajoute sommet j dans la liste d'adjacence de i, avec valeur arete

    std::vector<std::string> nom_sommets = P.Matrice::nom_sommets();

    std::vector<std::vector<double> > M = P.Matrice::mat();

    Liste liste_sommets({});

    int n = M.size();

    double inf = std::numeric_limits<double>::infinity(); // l'infini

    for (int i = 0; i < n; i++) {

        std::vector<Arete> adja_i;

        for (int j = 0; j < n; j++) {

            if (M[i][j] < inf) {

                Arete arete_ij(nom_sommets[i], nom_sommets[j], M[i][j]);

                adja_i.push_back(arete_ij);

            }
        }

        Sommet sommet_i(nom_sommets[i], adja_i);

        liste_sommets.push_back(sommet_i);
    }

    return liste_sommets;

}

void Test2 () {

    double inf = std::numeric_limits<double>::infinity();
    
    std::vector<std::vector<double> > M = {{inf, 1.23, 2.21}, {inf, inf, 3.76}, {2.16, 0.97, inf}};

    Matrice P({"A", "B", "C"}, M);

    Liste liste = Matrice_vers_liste(P);

    for (int i = 0; i < 3; i++) {

        liste.Liste::ret(i).Sommet::print();
    }
}


// 2. Construire la représentation à partir d'une représentation par étiquettes


bool is_in_liste (std::string str, std::vector<std::string> liste) {

    for (int i = 0; i < liste.size(); i++) {

        if (liste[i] == str) {

            return true;
        }
    }

    return false;
}

bool is_in_liste_Arete (std::string str, std::vector<Arete> liste) {

    for (int i = 0; i < liste.size(); i++) {

        if (liste[i].Arete::sommet2() == str) {

            return true;
        }
    }

    return false;
}

Liste Construction_graphe_liste (std::vector<std::vector<std::string> > graphe) {

    // On prend un sommet de départ

    // On regarde tous les sommets d'arrivés pour les mettre dans sa liste d'adjacence avec la valeur de leur arête

    // On refait avec le sommet suivant etc.

    int nb_arete = graphe.size();

    std::vector<std::string> nom_sommets;

    Liste liste_sommets({});

    for (int i = 0; i < nb_arete; i++) {

        std::string sommet_i = graphe[i][0];

        if (!is_in_liste(sommet_i, nom_sommets)) { // On vérifie que le sommet n'aie pas déjà été étudié

            nom_sommets.push_back(sommet_i);

            std::vector<Arete> adja_i; // Liste d'adjacence du sommet i

            for (int j = 0; j < nb_arete; j++) {

                if (graphe[j][0] == sommet_i) { 
                    
                    adja_i.push_back(Arete (sommet_i, graphe[j][1], std::stod(graphe[j][2])));

                }
            }

            liste_sommets.push_back(Sommet (sommet_i, adja_i));
        
        }

    }

    return liste_sommets;

}

void Test3 () {

    std::vector<std::vector<std::string> > graphe = {{"A", "B", "1.23"}, {"A", "C", "2.21"}, {"B", "C", "3.76"}, {"C", "A", "2.16"}, {"C", "B", "0.97"}};

    Liste liste = Construction_graphe_liste(graphe);

    for (int i = 0; i < 3; i++) {

        liste.Liste::ret(i).Sommet::print();
    }

}

Matrice Construction_graphe_matrice (std::vector<std::vector<std::string> > graphe) {

    // On affecte à tous les sommets un indice dans un dictionnaire

    // On re-parcourt le graphe pour appliquer la même méthode qu'au dessus : on regarde l'indice de tous les sommets d'arrivée pour mettre la valeur 
    // de leur arête dans la matrice un par un

    int nb_arete = graphe.size();

    std::vector<std::string> nom_sommets;
    std::map <std::string, int> indice_sommets;

    int k = 0;

    for (int i = 0; i < nb_arete; i++) {

        if (!is_in_liste(graphe[i][0], nom_sommets)) {

            nom_sommets.push_back(graphe[i][0]);

            indice_sommets[graphe[i][0]] = k;

            k++;
        }
    }

    int nb_sommets = nom_sommets.size();

    std::vector<std::vector<double> > M(nb_sommets, std::vector<double> (nb_sommets, std::numeric_limits<double>::infinity()));

    for (int i = 0; i < nb_sommets; i++) {

        std::string sommet_i = nom_sommets[i];

        for (int j = 0; j < nb_arete; j++) {

            if (graphe[j][0] == sommet_i) {

                int indice_j = indice_sommets[graphe[j][1]]; // indice relatif -> indice absolu

                M[i][indice_j] = std::stod(graphe[j][2]);
            }
        }
    }

    Matrice P(nom_sommets, M);

    return P;

}

void Test4 () {

    std::vector<std::vector<std::string> > graphe = {{"A", "B", "1.23"}, {"A", "C", "2.21"}, {"B", "C", "3.76"}, {"C", "A", "2.16"}, {"C", "B", "0.97"}};

    Matrice P = Construction_graphe_matrice(graphe);

    P.Matrice::print();

    Liste liste = Construction_graphe_liste(graphe);

    Matrice P_prime = Liste_vers_matrice(liste);

    P_prime.Matrice::print();

}


// 3. Parcours récursif


Sommet name_to_Sommet (Liste liste_sommets, std::string nom_sommet) {

    int i = 0;
    
    while (i < liste_sommets.size()) {

        if (liste_sommets.ret(i).Sommet::name() == nom_sommet) {

            return liste_sommets.ret(i);
        }

        i++;

    }

}

int indice_Arete_anterieure (std::vector<Arete> liste, std::string name) {
    
    for (int i = 0; i < liste.size(); i++) {

        if (liste[i].Arete::sommet2() == name) {

            return i;
        }
    }

    return 0;

}

int Visite_recursive (Liste liste_sommets, std::string nom_sommet, std::vector<std::string> sommets_visites = {}, std::vector<Arete> a_visiter = {}) {

    // On récupère le sommet correspondant au nom entré

    Sommet S = name_to_Sommet(liste_sommets, nom_sommet);

    sommets_visites.push_back(nom_sommet);

    // On le marque comme visité et on récupère sa liste d'adjacence

    std::vector<Arete> adja = S.Sommet::adja();

    // On remplit la liste "à visiter" et on l'actualise au besoin

    for (int j = 0; j < adja.size(); j++) {
        
        std::string nom = adja[j].Arete::sommet2(); // Sommet 1 correspond au nom de S le sommet d'origine 

        if (!is_in_liste(nom, sommets_visites)) {
            
            if (is_in_liste_Arete(nom, a_visiter)) {

                int k = indice_Arete_anterieure(a_visiter, nom);

                auto it = a_visiter.begin() + k;

                a_visiter.erase(it);
                
            } // On actualise l'arête précédente qui menait au sommet à visiter avec la nouvelle arête plus proche du dernier sommet
            
            a_visiter.push_back(adja[j]);

        }

    }
    
    if (a_visiter.size() == 0) {
        
        std::cout << "END" << std::endl;
        
        return 1;
    }

    // Quand la liste à visiter est vide, on termine le programme
    
    else {

        std::string prochain_sommet = a_visiter[a_visiter.size() - 1].Arete::sommet2();

        a_visiter[a_visiter.size() - 1].Arete::print();

        a_visiter.pop_back();

        return Visite_recursive(liste_sommets, prochain_sommet, sommets_visites, a_visiter);
    
    }

    // Si elle n'est pas vide, on recommence avec le sommet en haut de la liste à visiter

}

int Test5 () {

    Arete a1("A", "B", 1.23);
    Arete a2("A", "D", 2.21);
    Arete b1("B", "A", 3.76);
    Arete b2("B", "C", 2.16);
    Arete c1("C", "A", 0.97);
    Arete c2("C", "D", 1.87);
    Arete d1("D", "B", 0.86);
    Arete d2("D", "C", 0.04);
    
    Sommet A("A", {a1, a2});
    Sommet B("B", {b1, b2});
    Sommet C("C", {c1, c2});
    Sommet D("D", {d1, d2});
    
    Liste liste({A, B, C, D});
    
    Visite_recursive(liste, "A");

}


// 4. Parcours itératif pile


void print(std::vector<std::string> liste) {

    // Utile pour vérifier où se situe le problème 

    for (int i = 0; i < liste.size(); i++) {

        std::cout << liste[i] << ' ';
    }
    
    std::cout << std::endl;
}

void Visite_iterative_pile(Liste liste_sommets, std::string nom_sommet) {

    // On accède à la liste d'adjacence du sommet choisi

    // On ajoute les sommets adjacents NON PARCOURUS à la pile 

    // On reprend le premier sommet adjacent, on vérifie qu'il ne soit pas parcouru (car le parcours a pu se faire entre l'ajout et la "remontée" du sommet dans la pile)

    // Si oui : pop(); sinon, pop() + on répète.

    std::vector<std::string> sommets_visites = {};

    Sommet S = name_to_Sommet(liste_sommets, nom_sommet);

    sommets_visites.push_back(nom_sommet);

    std::vector<Arete> adja = S.Sommet::adja();

    std::stack<Arete> a_visiter;

    for (int i = 0; i < adja.size(); i++) {

        if (!is_in_liste(adja[i].Arete::sommet2(), sommets_visites)) {

            a_visiter.push(adja[i]);

        }
    }

    // Tant que la liste n'est pas vide

    while (!a_visiter.empty()) {

        Arete A = a_visiter.top();

        a_visiter.pop();

        std::vector<Arete> adja_A = name_to_Sommet(liste_sommets, A.Arete::sommet2()).Sommet::adja();

        if (!is_in_liste(A.Arete::sommet2(), sommets_visites)) {

            sommets_visites.push_back(A.Arete::sommet2());
            
            for (int j = 0; j < adja_A.size(); j++) {

                if (!is_in_liste(adja_A[j].Arete::sommet2(), sommets_visites)) {

                    a_visiter.push(adja_A[j]);

                }
            }

            A.Arete::print();

        }

    }

    std::cout << "END" << std::endl;

}

void Test6 () {

    Arete a1("A", "B", 1.23);
    Arete a2("A", "D", 2.21);
    Arete b1("B", "A", 3.76);
    Arete b2("B", "C", 2.16);
    Arete c1("C", "A", 0.97);
    Arete c2("C", "D", 1.87);
    Arete d1("D", "B", 0.86);
    Arete d2("D", "C", 0.04);
    
    
    Sommet A("A", {a1, a2});
    Sommet B("B", {b1, b2});
    Sommet C("C", {c1, c2});
    Sommet D("D", {d1, d2});
    
    Liste liste({A, B, C, D});

    Visite_iterative_pile(liste, "A");
}


// 5. Parcours itératif file


void Visite_iterative_file(Liste liste_sommets, std::string nom_sommet, int niveau) {

    // Initialisation : on commence par récupérer la liste d'adjacence du premier sommet, on met ces arêtes dans une file

    // Puis on passe au niveau 1 : on fait de même avec ces sommets recueillis en prenant soin d'éliminer la liste d'adjacence du sommet de l'initialisation

    // Idem niveau 2, etc.

    Sommet S = name_to_Sommet(liste_sommets, nom_sommet);

    std::queue<Arete> a_visiter;
    
    for (int i = 0; i < S.Sommet::adja().size(); i++) {
    
        a_visiter.push(S.Sommet::adja()[i]);
    
    }

    for (int i = 0; i < niveau; i++) {

        const int len = a_visiter.size();

        for (int j = 0; j < len; j++) {

            Arete A_j = a_visiter.front();

            A_j.Arete::print();

            a_visiter.pop();

            std::vector<Arete> adja_j = name_to_Sommet(liste_sommets, A_j.Arete::sommet2()).Sommet::adja();

            for (int k = 0; k < adja_j.size(); k++) {

                a_visiter.push(adja_j[k]);

            }
        }

    }

}

void Test7 () {

    Arete a1("A", "B", 1.23);
    Arete a2("A", "D", 2.21);
    Arete b1("B", "A", 3.76);
    Arete b2("B", "C", 2.16);
    Arete c1("C", "A", 0.97);
    Arete c2("C", "D", 1.87);
    Arete d1("D", "B", 0.86);
    Arete d2("D", "C", 0.04);
    
    
    Sommet A("A", {a1, a2});
    Sommet B("B", {b1, b2});
    Sommet C("C", {c1, c2});
    Sommet D("D", {d1, d2});
    
    Liste liste({A, B, C, D});

    Visite_iterative_file(liste, "A", 2);

    // Fils et petits-fils du sommet A

}

// 6. Djikstra

void initDijkstra (std::string depart, Liste & liste_sommet, std::map<std::string, double> & d) {

    std::vector<std::string> P = {};

    std::map <std::string, double> dist;

    double inf = std::numeric_limits<double>::infinity();

    for (int i = 0; i < liste_sommet.size(); i++) {

        d[liste_sommet.ret(i).Sommet::name()] = inf;

    }

    d[depart] = 0;

}

Sommet trouve_min(Liste & liste_sommets, std::map<std::string, double> d) {

    double min = std::numeric_limits<double>::infinity();

    Sommet Som(" ", {});

    for (int i = 0; i < liste_sommets.size(); i++) {

        if (d[liste_sommets.ret(i).Sommet::name()] < min) {

            min = d[liste_sommets.ret(i).Sommet::name()];

            Som = liste_sommets.ret(i);
        }
    }

    return Som;
}

void mise_a_jour_distances(std::string S1, std::string S2, std::map<std::string, double> & d, double poids, std::map<std::string, std::string> & predecesseur) {

    if (d[S2] > d[S1] + poids) {

        d[S2] = d[S1] + poids;

        predecesseur[S2] = S1;
    }
}

int indice(Sommet S, Liste L) {

    for (int i = 0; i < L.size(); i++) {

        if (S.Sommet::name() == L.ret(i).Sommet::name()) {

            return i;
        }
    }

    return 0;
}

void Dijkstra(Liste liste_sommets, std::string depart, std::string arrivee) {

    double min = std::numeric_limits<double>::infinity();

    std::map<std::string, double> d; 

    std::map<std::string, std::string> predecesseur;

    initDijkstra(depart, liste_sommets, d);

    while (liste_sommets.size() != 0) {

        Sommet S1 = trouve_min(liste_sommets, d);

        std::vector<Arete> Adja = S1.Sommet::adja();

        int k = indice(S1, liste_sommets);

        auto it = liste_sommets.begin() + k;

        liste_sommets.erase(it); 
                
        for (int j = 0; j < Adja.size(); j++) {

            mise_a_jour_distances(Adja[j].Arete::sommet1(), Adja[j].Arete::sommet2(), d, Adja[j].Arete::value(), predecesseur);
        }
    } 

    // A ce stade, il ne reste plus qu'à remonter les prédecesseurs!

    std::vector<std::string> A = {};

    std::string S = arrivee;

    while (S != depart) {

        A.push_back(S);

        S = predecesseur[S];
    }

    A.push_back(depart);

    for (int k = A.size() - 1; k > -1 ; k = k - 1) {

        std::cout << A[k] << std::endl;
    }

    std::cout << "END" << std::endl;

}

void Test8 () {

    Arete a1("A", "B", 3);
    Arete a2("A", "C", 1);
    Arete b1("B", "C", 7);
    Arete b2("B", "D", 5);
    Arete b3("B", "E", 1);
    Arete c1("C", "D", 2);
    Arete d1("D", "E", 7);

    Sommet A("A", {a1, a2});
    Sommet B("B", {b1, b2, b3});
    Sommet C("C", {c1});
    Sommet D("D", {d1});
    Sommet E("E", {});

    Liste G({A, B, C, D, E});

    Dijkstra(G, "A", "E");
    Dijkstra(G, "A", "D");
    Dijkstra(G, "C", "E");
}

// 7. Floyd-Warshall

double min (double a, double b) {

    if (a < b) {

        return a;

    }

    return b;
}

void Floyd_Warshall (Liste graphe) {

    double inf = std::numeric_limits<double>::infinity();

    Matrice mat = Liste_vers_matrice(graphe);

    for (int k = 0; k < mat.mat().size(); k++) {
        
        for (int i = 0; i < mat.mat().size(); i++) {

            for (int j = 0; j < mat.mat().size(); j++) {

                mat.modif(i, j, min(mat.mat()[i][j], mat.mat()[i][k] + mat.mat()[k][j]));

            }

        }

    }

    std::vector<std::string> liste = mat.nom_sommets();

    for (int i = 0; i < mat.mat().size(); i++) {

        for (int j = i; j < mat.mat().size(); j++) {

            if (mat.mat()[i][j] < inf) {

                std::cout << liste[i] << ", " << mat.mat()[i][j] << ", " << liste[j] << std::endl;

            }
        }

    }

}

void Test9 () {

    Arete a1("A", "B", 3);
    Arete a2("A", "C", 1);
    Arete b1("B", "C", 7);
    Arete b2("B", "D", 5);
    Arete b3("B", "E", 1);
    Arete c1("C", "D", 2);
    Arete d1("D", "E", 7);

    Sommet A("A", {a1, a2});
    Sommet B("B", {b1, b2, b3});
    Sommet C("C", {c1});
    Sommet D("D", {d1});
    Sommet E("E", {});

    Liste G({A, B, C, D, E});

    Floyd_Warshall(G);
}

// APPLICATION : 

int main () {

    //Question 1

    //Test1(); 
    //Test2();

    //Question 2

    //Test3();
    //Test4();

    //Question 3

    //Test5();
    
    //Question 4

    //Test6();

    //Question 5

    //Test7();

    //Question 6

    //Test8();

    //Question 7

    //Test9();
}