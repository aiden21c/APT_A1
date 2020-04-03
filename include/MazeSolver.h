
#ifndef COSC_ASS_ONE_PARTICLE_FILTER
#define COSC_ASS_ONE_PARTICLE_FILTER

#include "Breadcrumb.h"
#include "Trail.h"
#include "Types.h"

class MazeSolver {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */


   // Constructor/Destructor
   MazeSolver();
   ~MazeSolver();

   // Solve the maze
   void solve(Maze maze);

   // Get a DEEP COPY of the solution
   Trail* getSolution();

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

   // Returns a string array containing the directions
   std::string* getDirections();

private:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // Trail of breadcrumbs from the start to end
   Trail* solution;


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

   // Returns the location of a specific character in the maze
   Breadcrumb* getLocation(char x, Maze maze);

   // Checks if the location is OPEN
   bool isFree(int x, int y, Maze maze);

   // Returns the character at a location in the maze
   char getCharacterAt(int x, int y, Maze maze);

   // A string array containing the directions from start to end
   std::string directions[TRAIL_ARRAY_MAX_SIZE];
};

#endif // COSC_ASS_ONE_PARTICLE_FILTER
