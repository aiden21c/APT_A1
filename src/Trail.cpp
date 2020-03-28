#include "Trail.h"


Trail::Trail() { 
   this->length = 0;
}

Trail::Trail(Trail& other) :
length(other.length)
{
   for (int i = 0; i < other.length; i++) {
      breadcrumbs[i] = new Breadcrumb(*other.breadcrumbs[i]);
   }
}

Trail::~Trail() { 
   for (int i = length; i > 0; i--) {
      delete breadcrumbs[i - 1];
   }
}

int Trail::size() {
   return length;
}

Breadcrumb* Trail::getPtr(int i) {
   Breadcrumb* ptr = breadcrumbs[i];
   return ptr;
}

void Trail::addCopy(Breadcrumb* t) {
   Breadcrumb* b = new Breadcrumb(*t);
   breadcrumbs[length] = b;
   length++;
}

bool Trail::contains(int x, int y) {
   bool cont = false;
   int x1, y1;
   for (int i = 0; i < length; i++) {
      x1 = breadcrumbs[i]->getX();
      y1 = breadcrumbs[i]->getY();

      if ((x == x1) && (y == y1)) {
         cont = true;
         i = length;
      }
   }
   return cont;
}

int Trail::getIndex(int x, int y) {
   int x1, y1, j;
   for (int i = 0; i < length; i++) {
      x1 = breadcrumbs[i]->getX();
      y1 = breadcrumbs[i]->getY();

      if ((x1 == x) && (y1 == y)) {
         j = i;
         i = length;
      }
   }
   return j;
}

int Trail::lastFresh() {
   int fresh = 0;
   for (int i = length-1; i > -1; i--) {
      if (!(breadcrumbs[i]->isStale())){
         fresh = i;
         i = 0;
      }
   }
   return fresh;
}