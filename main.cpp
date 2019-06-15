/**
 * Chau Ying KOT, Teo Ferrari, Gildas Houlmann
 *
 * Commentaire :    Pour une config 4x4, il faudrai modifier la taille de la grille
 *
 *
 */

#include <cstdlib>
#include <cstdio>
#include <list>
#include <queue>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const unsigned TAILLE_GRILLE = 3;
const unsigned ELEM_VIDE = 0;

using Configuration = array<unsigned, TAILLE_GRILLE * TAILLE_GRILLE>;

Configuration createSolution();

const Configuration SOLUTION = createSolution();

using Sommets = map<Configuration, Configuration>; // ConfigCourant,configParent

enum Directions {
    HAUT = -TAILLE_GRILLE, DROITE = 1, BAS = TAILLE_GRILLE, GAUCHE = -1
};

class GraphConfigs {

private:
    //Contient la liste des sommets
    Sommets sommetList;

    //Configuration a résoudre
    Configuration configurationInitial;

    /**
     * Compare deux configurations
     * @param c1
     * @param c2
     * @return
     */
    bool compareConfig(Configuration c1, Configuration c2) const;

    /**
     * Retourne une liste de configurations possible selon celui passé en paramètre
     * @param c
     * @return un vecteur de configuration voisin
     */
    vector<Configuration> createAdjacents(Configuration c) const;

    /**
     * Crée une configuration voisin en indiquand le pièce à deplacer
     * @param c
     * @param position position de la case vide
     * @param direction la position de la pièce à déplacer
     * @return
     */
    Configuration
    createChild(Configuration c, unsigned position, unsigned direction) const;

    /**
     * Checker si la configuration est la solution
     * @param s
     * @return
     */
    bool checkSolution(Configuration s) const;

    /**
     * Affachage des deplacement de parent en parent depuis la configuration
     * @param c
     */
    void affichageSolution(Configuration c) const;


public:

    /**
     * Crée la liste des voisins en fesait un parcour en largeur
     */
    void BFSWithParent();

    /**
     * stocke la configuration donnée
     */
    void configInit();

};

bool GraphConfigs::checkSolution(Configuration s) const {
    return compareConfig(s, configurationInitial);
}

void GraphConfigs::configInit() {
    for (size_t i = 0; i < TAILLE_GRILLE; ++i) {
        for (size_t j = 0; j < TAILLE_GRILLE; ++j) {
            cin >> configurationInitial.at(i * TAILLE_GRILLE + j);
        }
    }
}

vector<Configuration> GraphConfigs::createAdjacents(Configuration c) const {
    // Trouve l'indice de la position vide
    auto itElemVide = find(c.begin(), c.end(), ELEM_VIDE);
    size_t indexElemVide = (size_t) distance(c.begin(), itElemVide);

    vector<Configuration> adjacentsFromIndex;

    //La position vide ne se trouve pas sur la dernière ligne
    if (indexElemVide < TAILLE_GRILLE * (TAILLE_GRILLE - 1)) {
        adjacentsFromIndex.push_back(createChild(c, indexElemVide, BAS));
    }

    //La position vide ne se trouve pas sur la dernière colonne
    if (indexElemVide % TAILLE_GRILLE != (TAILLE_GRILLE - 1)) {
        adjacentsFromIndex.push_back(createChild(c, indexElemVide, DROITE));
    }

    //La position vide ne se trouve pas sur la première ligne
    if (indexElemVide > (TAILLE_GRILLE - 1)) {
        adjacentsFromIndex.push_back(createChild(c, indexElemVide, HAUT));
    }

    //La position vide ne se trouve pas sur la première colonne
    if ((indexElemVide % TAILLE_GRILLE) != 0) {
        adjacentsFromIndex.push_back(createChild(c, indexElemVide, GAUCHE));
    }

    return adjacentsFromIndex;
}

void GraphConfigs::BFSWithParent() {
    queue<Configuration> queue;
    queue.push(SOLUTION);
    sommetList.insert(make_pair(SOLUTION, SOLUTION));

    vector<Configuration> adjacentsFromIndex;

    Configuration temp;

    while (queue.empty() == false) {
        temp = queue.front();
        queue.pop();
        // crée la liste des mouvements possible
        adjacentsFromIndex = createAdjacents(temp);
        for (size_t i = 0; i < adjacentsFromIndex.size(); ++i) {
            //Si la confige crée n'est pas déjà marqué
            if (sommetList.find(adjacentsFromIndex.at(i)) == sommetList.end()) {

                sommetList.insert(make_pair(adjacentsFromIndex.at(i), temp));
                queue.push(adjacentsFromIndex.at(i));

                if (checkSolution(adjacentsFromIndex.at(i))) {
                    cout << "Solution : ";
                    affichageSolution(adjacentsFromIndex.at(i));
                    return;
                }
            }
        }
    }
    cout << "Pas de solution" << endl;
}

Configuration GraphConfigs::createChild(Configuration c, unsigned position,
                                        unsigned direction) const {
    Configuration temp = c;
    std::swap(temp.at(position), temp.at(position + direction));
    return temp;
}

void GraphConfigs::affichageSolution(Configuration c) const {

    Configuration parent = (*sommetList.find(c)).second;
    while (compareConfig(c, parent) == false) {
        cout << distance(parent.begin(),
                         find(parent.begin(), parent.end(), ELEM_VIDE))
             << " ";
        c = parent;
        parent = (*sommetList.find(c)).second;
    }
}

bool GraphConfigs::compareConfig(Configuration c1, Configuration c2) const {
    for (size_t i = 0; i < TAILLE_GRILLE; ++i) {
        for (size_t j = 0; j < TAILLE_GRILLE; ++j) {
            if (c1.at(i * TAILLE_GRILLE + j) != c2.at
                    (i * TAILLE_GRILLE + j)) {
                return false;
            }
        }
    }
    return true;
}

/**
 * Crée la configuration solution pour la taille de la grille
 * @return
 */
Configuration createSolution() {
    Configuration temp;
    for (size_t i = 0; i < TAILLE_GRILLE * TAILLE_GRILLE; ++i) {
        temp.at(i) = i;
    }
    return temp;
}

int main() {

    GraphConfigs configs;

    cout << "Configuration a resoudre : ";
    configs.configInit();

    configs.BFSWithParent();

    return EXIT_SUCCESS;
}

