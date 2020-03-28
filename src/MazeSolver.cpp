
#include "MazeSolver.h"

MazeSolver::MazeSolver() { 
   this->solution = new Trail();
}

MazeSolver::~MazeSolver() { 
   delete solution;
}

void MazeSolver::solve(Maze maze) {
   Breadcrumb* b = getLocation('S', maze);
   int bX = b->getX();
   int bY = b->getY();
   delete b;

   Breadcrumb* end = getLocation('E', maze);
   int eX = end->getX();
   int eY = end->getY();

   std::string s;
   int directIndex = 0;

   while (bX != eX || bY != eY) {
      int north = bY-1;
      int east = bX+1;
      int south = bY+1;
      int west = bX-1;

      if (isFree(bX, north, maze) && (north >= 0) && (!solution->contains(bX, north))) {
         Breadcrumb* c = new Breadcrumb(bX, north, false);
         solution->addCopy(c);
         bX = c->getX();
         bY = c->getY();
         delete c;

         s = "north";
         directions[directIndex] = s;
         directIndex = directIndex + 1;
         directions[directIndex] = "\0";

      }  else if (isFree(east, bY, maze) && (east <= 19) && (!solution->contains(east, bY))) {
         Breadcrumb* c = new Breadcrumb(east, bY, false);
         solution->addCopy(c);
         bX = c->getX();
         bY = c->getY();
         delete c;

         s = "east";
         directions[directIndex] = s;
         directIndex = directIndex + 1;
         directions[directIndex] = "\0";

      } else if (isFree(bX, south, maze) && (south <= 19) && (!solution->contains(bX, south))) {
         Breadcrumb* c = new Breadcrumb(bX, south, false);
         solution->addCopy(c);
         bX = c->getX();
         bY = c->getY();
         delete c;

         s = "south";
         directions[directIndex] = s;
         directIndex = directIndex + 1;
         directions[directIndex] = "\0";

      } else if (isFree(west, bY, maze) && (west >= 0) && (!solution->contains(west, bY))) {
         Breadcrumb* c = new Breadcrumb(west, bY, false);
         solution->addCopy(c);
         bX = c->getX();
         bY = c->getY();
         delete c;

         s = "west";
         directions[directIndex] = s;
         directIndex = directIndex + 1;
         directions[directIndex] = "\0";

      } else {
         int index = solution->getIndex(bX, bY);
         Breadcrumb *current = solution->getPtr(index);
         current->setStale(true);
         int fresh = solution->lastFresh();
         Breadcrumb *lastFresh = solution->getPtr(fresh);
         Breadcrumb* c = new Breadcrumb(lastFresh->getX(), lastFresh->getY(), lastFresh->isStale());
         bX = c->getX();
         bY = c->getY();
         delete c;

         directIndex = directIndex - 1;
         directions[directIndex] = "\0";

      }
   }
}

Trail* MazeSolver::getSolution() {
   Trail* solutionCopy = new Trail(*solution);
   return solutionCopy;
}

std::string* MazeSolver::getDirections() {
   return directions;
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

