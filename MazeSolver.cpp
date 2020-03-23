
#include "MazeSolver.h"

MazeSolver::MazeSolver() { }

MazeSolver::~MazeSolver() { 
   delete solution;
}

void MazeSolver::solve(Maze maze) {
   Breadcrumb* b = getLocation('S', maze);
   solution->addCopy(b);
   int bX = b->getX();
   int bY = b->getY();

   Breadcrumb* end = getLocation('E', maze);
   int eX = end->getX();
   int eY = end->getY();

   while (bX != eX || bY != eY) {

   }





















}

Trail* MazeSolver::getSolution() {
   // TODO
   return solution;
}

Breadcrumb* MazeSolver::getLocation(char x, Maze maze) {
   bool sFound = false;
   Breadcrumb* b;

   while (!sFound) {
      for (int i = 0; i < MAZE_DIM; i++) {
         for (int j = 0; j < MAZE_DIM; j++) {
            if (maze[i][j] == x) {
               b = new Breadcrumb(j, i, false);
               sFound = true;
            }
         }
      }
   }
   return b;
}


