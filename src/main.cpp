/*  

To implement this assignment, I took a method of compartmentalising the assignment by 
first milestones, and then by classes. In order to do this, I completed the milestones
in the given order, and implemented the breadcrumb class first, followed by the trail
class. After using the given tests to ensure these classes were working, I then implemented
maze solver, and proceeded to implement the main class incorporating the reading in and 
printing out to/from standard input. I then implemented milestone 3 by slightly adjusting
the maze solver class, adding a string array to hold the ordered directions, and updating
this array the same way the trail solution was updated each iteration through the solve
loop.

Each class was implemented by the simple method of using the algorithm given in the assignment
sheet, as well as checking the methods already given in the header files, and implementing them
each one by one. In order to test my program, my sample tests involve a increasingly more difficult
test on the program, in a step by step manner to ensure the program works for one specific solve 
method before moving on to the next. It can be seen that test00 simply tests a straight line
maze/solution, where as test08 tests both back tracking, multidirectional movement, having the 
maze route pass along the boundaries of the maze, and a start and end point that are not located
on rows 0 and 19 respectively.

The 2 major issues I encountered in my implementation involved the maze solver class, and the solve
function. The first one involved testing test08.maze, whereby my solve function was written incorrectly
and was proceeding to attempt to access boundaries outside the maze. This was simply because I had the 
"<" and ">" signs switched. The second issue involved milestone 3, whereby my solve function would
incorrectly remove elements of the directions array even tho these directions were still true in the 
solution. This was because I did not account for the fact that the "last breadcrumb" in the trail may 
not necessarily be a "fresh" crumb, such as the case of a 4 way intersection, with north and east being 
dead ends. To solve this, I implemented a function that searches the array for the last "fresh" breadcrumb,
so that the solve function can go straight there after backtracking, instead of proceeding to alter the 
directions array while backtracking an already known "stale" route.

Most of the choices I made throughout my program were rooted in the concept of ensuring code is only written
once. Hence there are a number of added functions throughout each class which are used to ensure the efficiency
of the code.

Throughout my classes, it can be seen that code has been used very efficiently with very little occurrence 
of rewriting the same code twice. In this way, a large portion of the program runs very streamlined and
adheres to good programming practices. This being said, I could not think of a way to write solve function 
in maze solver without having to write a function that took in 6 parameters. In order to avoid writing 
such a function, I simply rewrote the code inside the "if" function for each different direction. Appreciating
this is not necessarily the best practice, however it was the only way i could think of without writing an equally
problematic void function that accepts 6 parameters. As this is the only inefficient part of the program, I still
stand by the statement of my program being to a high quality. 

*/


#include <iostream>
#include <string>

#include "Types.h"
#include "MazeSolver.h"

// Helper test functions
void testBreadcrumb();
void testTrail();

// Read a maze from standard input.
void readMazeStdin(Maze maze);

// Print out a Maze to standard output.
void printMazeStdout(Maze maze, Trail* solution);

int main(int argc, char** argv) {
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    /*
    std::cout << std::endl << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    testBreadcrumb();
    testTrail();
    std::cout << "DONE TESTING" << std::endl << std::endl;
    */

    // Load Maze from stdin
    Maze maze;
    readMazeStdin(maze);

    // Solve using MazeSolver
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    MazeSolver* solver = new MazeSolver();
    Trail* solution = nullptr;
    solver->solve(maze);
    solution = solver->getSolution();

    // Print Maze to stdout
    printMazeStdout(maze, solution);

    std::string* directions = solver->getDirections();

    int i = 0;
    while(directions[i] != "\0") {
        std::cout << directions[i] << std::endl;
    i++;
    }

    delete solver;

    return EXIT_SUCCESS;
}

void readMazeStdin(Maze maze) {
    std::string str[MAZE_DIM] = {};

    for (int i = 0; i < MAZE_DIM; i++) {
        getline(std::cin, str[i]);
    }

    for (int i = 0; i < MAZE_DIM; i++) {
        for (int j = 0; j < MAZE_DIM; j++) {
            maze[i][j] = str[i][j];
        }
    }
}


void printMazeStdout(Maze maze, Trail* solution) {
    for (int i = 0; i < MAZE_DIM; i++) {
        for (int j = 0; j < MAZE_DIM; j++) {
            if ((solution->contains(j, i))) {
                int index = solution->getIndex(j, i);
                if ((maze[i][j] == OPEN) && (!(solution->getPtr(index)->isStale()))) {
                    maze[i][j] = ROUTE;
                }
            }
        }
    }

    for(int i = 0; i < MAZE_DIM; i++) {
        for(int j = 0; j < MAZE_DIM; j++) {
            std::cout << maze[i][j];
        }
        std::cout << std::endl;
    } 
}

void testBreadcrumb() {
    std::cout << "TESTING BREADCRUMB" << std::endl;

    // Make a breadcrumb and print out the contents
    Breadcrumb* breadcrumb = new Breadcrumb(1, 1, false);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;

    // Change breadcrumb stale-ness and print again
    breadcrumb->setStale(true);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;
}

void testTrail() {
    std::cout << std::endl << "TESTING TRAIL" << std::endl;

    // Make a simple trail, should be empty size
    Trail* trail = new Trail();
    std::cout << "Trail size: " << trail->size() << std::endl;

    // Add a breadcrumb to the trail, print size, check contains
    Breadcrumb* b1 = new Breadcrumb(1, 1, false);
    trail->addCopy(b1);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0,0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1,1) << std::endl << std::endl;

    // Add second breadcrumb
    Breadcrumb* b2 = new Breadcrumb(0, 0, true);
    trail->addCopy(b2);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0,0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1,1) << std::endl;

    // Test Get-ith - should be 0,0,true
    Breadcrumb* getB = trail->getPtr(1);
    std::cout << getB->getX() << ",";
    std::cout << getB->getY() << ",";
    std::cout << getB->isStale() << std::endl << std::endl;

    // Print out the trail
    std::cout << "Print Trail:" << std::endl;
    int size = trail->size();
    for (int i = 0; i < size; i++) {
        Breadcrumb* getB = trail->getPtr(i);
        std::cout << getB->getX() << ",";
        std::cout << getB->getY() << ",";
        std::cout << getB->isStale() << std::endl;
    }
    std::cout << std::endl;
}
