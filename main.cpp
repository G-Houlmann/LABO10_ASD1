

#include <cstdlib>
#include <cstdio>

using namespace std;

const unsigned TAILLE_GRILLE = 3;
using sommet = unsigned[TAILLE_GRILLE][TAILLE_GRILLE];


class GraphConfigs{
private:
   queue<sommet> sommetsExistants;
   using parents = queue<sommet> ;
   
   createChlidren(sommet);
   const list<sommet> adjacents(sommet);
   void addEdge(sommet s);
   parents BFS(sommet s);
   bool checkSolution(sommet s);
   void configInit(sommet);
   void affichageSolution(parents p);
};

int main() {

   
   
   return 0;
}