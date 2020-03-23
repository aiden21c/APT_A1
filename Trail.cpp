
#include "Trail.h"


Trail::Trail() { }

Trail::~Trail() { }

int Trail::size() {
   return length;
}

Breadcrumb* Trail::getPtr(int i) {
   Breadcrumb* ptr = breadcrumbs[i];
   return ptr;
}

void Trail::addCopy(Breadcrumb* t) {
   Breadcrumb** tPtr = &t;
   Breadcrumb* b = new Breadcrumb(**tPtr);
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

void Trail::removeCrumb(){
   length--;
   delete breadcrumbs[length];
}
