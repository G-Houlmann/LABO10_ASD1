#include <cstdlib>
#include <cstdio>
#include <list>
#include <queue>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

const unsigned TAILLE_GRILLE = 3;
using Index = int;
using Configuration = array<array<unsigned, TAILLE_GRILLE>, TAILLE_GRILLE>;
//= unsigned[TAILLE_GRILLE][TAILLE_GRILLE];
using Sommets = map<Configuration, Configuration>; // ConfigCourant,configParent


class GraphConfigs {
private:
    vector<list<Index>> adjcendyLists;
    Sommets sommetList;
    Configuration configurationInitial;

public:

    void createChlidren(Configuration);

    const list<Index> adjacents(Index index) const;

    void addEdge(Index index1, Index index2);

    Index BFSAvecParent() const;

    bool checkSolution(Configuration s) const;

    void configInit();

    void affichageSolution(Sommets) const;
};

void GraphConfigs::addEdge(Index index1, Index index2) {
    adjcendyLists.at(index1).push_back(index2);
    if (index1 != index2) {
        adjcendyLists.at(index2).push_back(index1);
    }
}

const list<Index> GraphConfigs::adjacents(Index index) const {
    return adjcendyLists.at(index);
}

bool GraphConfigs::checkSolution(Configuration s) const {
    for (size_t i = 0; i < TAILLE_GRILLE; ++i) {
        for (size_t j = 0; j < TAILLE_GRILLE; ++j) {
            if (s.at(i).at(j) != i * TAILLE_GRILLE + j) {
                return false;
            }
        }
    }
    return true;
}

void GraphConfigs::configInit() {
    for (size_t i = 0; i < TAILLE_GRILLE; ++i) {
        for (size_t j = 0; j < TAILLE_GRILLE; ++j) {
            cin >> configurationInitial.at(i).at(j);
        }
    }
}

int main() {

    GraphConfigs configs;

    configs.configInit();

    return 0;
}

