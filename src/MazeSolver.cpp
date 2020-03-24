
#include "MazeSolver.h"

MazeSolver::MazeSolver() { 
   this->solution = new Trail();
}

MazeSolver::~MazeSolver() { 
   delete solution;
}

void MazeSolver::solve(Maze maze) {
   Breadcrumb* b = getLocation('S', maze);
   solution->addCopy(b);
   int bX = b->getX();
   int bY = b->getY();
   delete b;

   Breadcrumb* end = getLocation('E', maze);
   int eX = end->getX();
   int eY = end->getY();

   while (bX != eX || bY != eY) {
      int north = bY++;
      int east = bX++;
      int south = bY--;
      int west = bX--;

      if (isFree(bX, north, maze) && (north >= 0)) {
         Breadcrumb* c = new Breadcrumb(bX, north, false);
         solution->addCopy(c);
         bX = c->getX();
         bY = c->getY();
         delete c;
      }  else if (isFree(east, bY, maze) && (east >= 0)) {
         Breadcrumb* c = new Breadcrumb(east, bY, false);
         solution->addCopy(c);
         bX = c->getX();
         bY = c->getY();
         delete c;
      } else if (isFree(bX, south, maze) && (south >= 0)) {
         Breadcrumb* c = new Breadcrumb(bX, south, false);
         solution->addCopy(c);
         bX = c->getX();
         bY = c->getY();
         delete c;
      } else if (isFree(west, bY, maze) && (west >= 0)) {
         Breadcrumb* c = new Breadcrumb(west, bY, false);
         solution->addCopy(c);
         bX = c->getX();
         bY = c->getY();
         delete c;
      } else {
         //TODO
      }
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

bool MazeSolver::isFree(int x, int y, Maze maze) {
   bool free = false;
   if ((getCharacterAt(x, y, maze) == OPEN) || (getCharacterAt(x, y, maze) == 'E')) {
      free = true;
   }
   return free;
}

char MazeSolver::getCharacterAt(int x, int y, Maze maze) {
   char c = maze[y][x];
   return c;
}

