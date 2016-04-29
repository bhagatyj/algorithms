#include <iostream>
#include <vector>
#include <map>
#include <math.h>

using namespace std;

int **solutions;
// Solution is based on the equation:
//
// eggdrop(e, f) = 1 + min (  max( eggdrop( e-1, x-1 ), eggdrop( e, f-x ) ) for all x from 1 to f )
//
// Initial conditions:
// eggdrop(1, 0) = 0
// eggdrop(1, x) = x   for all x from 1 to f
// eggdrop(x, y) = log2 y for all log2 y > x`
#define OPTIMIZATION

int main( ) {

    int numEggs, numFloors, e, f, x;
    int *workingSet;

    numEggs = 20;
    numFloors = 100;
    
    if ( numEggs < 1 ) {
        return -1;
    }
    // Allocate with one extra element to make it sound logical
    // as floors 1 to f
    // and eggs 1 to e. 
    // ( not using zero index )
    // initialize with -1.
    solutions = (int **) malloc( sizeof(int *) * (numEggs+1) );
    for ( e=0; e<=numEggs; e++) {
        solutions[e] = (int *) malloc( sizeof(int) * (numFloors+1) );
    }
    workingSet = ( int *) malloc( sizeof(int) * (numFloors+1) );
    for ( e=0; e<=numEggs; e++) {
        for ( f=0; f<=numFloors; f++) {
            solutions[e][f] = -1;
        }
    }

    // If there is only one egg, answer is the number of floors.
    for ( f=1; f<=numFloors; f++) {
        solutions[1][f] = f;
    }
    // If there is no more floors, answer is 0.
    // If there is only one floor, answer is 1.
    for ( e=1; e<=numEggs; e++) {
        solutions[e][0] = 0;
        solutions[e][1] = 1;
    }

#ifdef OPTIMIZATION
    // Additional optimization : not needed.
    //
    // If the number of floors is less than pow(2, e), then this
    // can be solved by binary search. For example, 100 floors and
    // 7 eggs can be solved by 7 drops.
    for ( e=1; e<=numEggs; e++) {
        for ( f=1; f<=numFloors; f++) {
            if ( f < pow(2, e) ) {
                // I can use binary division
                solutions[e][f] = ceil( log ( f ) / log (2 ) );
            }
        }
    }
#endif

    // Solve for the remaining cases
    for ( e=1; e<=numEggs; e++) {
        for ( f=1; f<=numFloors; f++) {
            if ( solutions[e][f] != -1 ) {
                // Already solved.
                continue;
            }
            
            for (x=1; x<=numFloors; x++) {
                workingSet[x] = 1 + max( solutions[e-1][x-1], solutions[e][f-x] );
            }

            int minSoFar = workingSet[1];
            for (x=1; x<=numFloors; x++) {
                if ( workingSet[x] < minSoFar ) {
                    minSoFar = workingSet[x];
                }
            }
            solutions[e][f] = minSoFar;
        }
    }
    cout << "Solving for 100 floors " << endl;
    for ( e=1; e<=numEggs; e++) {
        cout << "With " << e << " eggs, I need " 
             << solutions[e][100] << "  drops" << endl;
    }
}
