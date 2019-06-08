#include <cstdlib>
#include <cstdio>
#include <list>
#include <queue>
#include <map>
#include <vector>

using namespace std;

const unsigned TAILLE_GRILLE = 3;
using Index = int;
using Configuration = array<array<unsigned , TAILLE_GRILLE>,TAILLE_GRILLE>;
//= unsigned[TAILLE_GRILLE][TAILLE_GRILLE];
using Sommets = map<Index, Configuration>;


class GraphConfigs {
private:
    vector<list<Index>> adjcendyLists;

public:

    void createChlidren(Configuration, Sommets);

    const list<Index> adjacents(Index index) const;

    void addEdge(Index index1, Index index2);

    Index BFS(Sommets sommets);

    bool checkSolution(Configuration s);

    void configInit(Configuration);

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

int main() {


    return 0;
}

