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
using Index = int;
using Configuration =array<unsigned, TAILLE_GRILLE * TAILLE_GRILLE>;

const Configuration SOLUTION = {0, 1, 2, 3, 4, 5, 6, 7, 8};
using Sommets = map<Configuration, Configuration>; // ConfigCourant,configParent
enum Directions {
    HAUT = -3, DROITE = 1, BAS = 3, GAUCHE = -1
};

class GraphConfigs {
private:
    vector<list<Configuration>> adjcendyLists;
    Sommets sommetList;
    Configuration configurationInitial;

    bool compareConfig(Configuration, Configuration) const;

public:


    vector<Configuration> createAdjacents(Configuration c);

    Configuration createChild(Configuration c, unsigned position, unsigned
    direction) const;


    //const list<Configuration> adjacents(Configuration Configuration) const;

    //void addEdge(Configuration configuration1, Configuration configuration2);

    void BFSWithParent();

    bool checkSolution(Configuration s) const;

    void configInit();

    void affichageSolution(Configuration c) const;
};

/*void GraphConfigs::addEdge(Configuration configuration1, Configuration configuration2) {
    adjcendyLists.at(configuration1).push_back(configuration2);
    if (configuration1 != configuration2) {
        adjcendyLists.at(configuration2).push_back(configuration1);
    }
}

const list<Index> GraphConfigs::adjacents(Index index) const {
    return adjcendyLists.at(index);
}*/

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

vector<Configuration> GraphConfigs::createAdjacents(Configuration c) {
    auto itElemVide = find(c.begin(), c.end(),
                           ELEM_VIDE); // trouve position vide ptr
    size_t indexElemVide = distance(c.begin(), itElemVide);

    vector<Configuration> adjacentsFromIndex;

    if (indexElemVide < TAILLE_GRILLE * (TAILLE_GRILLE - 1)) {
        adjacentsFromIndex.push_back(createChild(c, indexElemVide, BAS));
    }

    if (indexElemVide % TAILLE_GRILLE != (TAILLE_GRILLE - 1)) {
        adjacentsFromIndex.push_back(createChild(c, indexElemVide, DROITE));
    }

    if (indexElemVide > (TAILLE_GRILLE - 1)) {
        adjacentsFromIndex.push_back(createChild(c, indexElemVide, HAUT));
    }

    if ((indexElemVide%TAILLE_GRILLE) != 0) {
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
        adjacentsFromIndex = createAdjacents(temp);
        for (size_t i = 0; i < adjacentsFromIndex.size(); ++i) {
            if (sommetList.find(adjacentsFromIndex.at(i)) == sommetList.end()) {
                sommetList.insert(make_pair(adjacentsFromIndex.at(i), temp));
                queue.push(adjacentsFromIndex.at(i));
                if (checkSolution(adjacentsFromIndex.at(i))) {
                    affichageSolution(adjacentsFromIndex.at(i));
                    return;
                }
            }
        }
        //create childrend and push if not in map
        //sommetList inseter makepair(nouveau, temp)
        // if check ok break return
    }

}

Configuration GraphConfigs::createChild(Configuration c, unsigned position,
                                        unsigned direction) const {
    Configuration temp = c;
    std::swap(temp.at(position), temp.at(position + direction));
    return temp;
}

void GraphConfigs::affichageSolution(Configuration c) const {

    Configuration parent = (*sommetList.find(c)).second;
    if (compareConfig(c, parent) == false) {
        cout << distance(parent.begin(),
                         find(parent.begin(), parent.end(), ELEM_VIDE))
             << " ";
        affichageSolution(parent);

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

int main() {

    GraphConfigs configs;

    configs.configInit();

    configs.BFSWithParent();




    return EXIT_SUCCESS;
}

