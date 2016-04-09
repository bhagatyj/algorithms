#include <stdio.h>
#include <assert.h>

// Find the missing number in an array of consecutive positive integers
int
find( int *a, int size) {

	int start = 0;
    int end = size-1;
    int mid;

    if ( ( a == NULL ) || ( size <= 1 ) ) { return 0; }

    while ( start <= end ) {

      	mid = (start + end)/2;
      	int predictedVal = a[0] + mid;

		// The below checks work on finding a miss in a 3 element set.
		//
		//    (start)   (mid)  (end)
		//
		// If the mid-point is not the start, compare with mid-1.
		// If the mid-point is not the end, compare with mid+1.
	  	if ( mid > start ) {
      		if ( ( a[mid] != predictedVal ) && ( a[mid-1] == predictedVal-1 ) ) {
       	  		return predictedVal;
			}
      	}
	  	if ( mid < end ) {
      	 	if ( ( a[mid] == predictedVal ) && ( a[mid+1] != predictedVal+1 ) ) {
            	return predictedVal+1;
		 	}
      	}

		// If there are three or less elements, we are done
	  	if ( end < (start+2) ) {
		 	return 0;
      	}
      	
		// There are more than three elements.
		// Find the section to target next.
      	if ( a[mid] > predictedVal ) {
         	end = mid;
      	} else {
         	start = mid;
      	}
   }
   return 0;

}

typedef struct ads_t_ {
	int *array;
	int length;
	int answer;
} ads_t;

int main() {

	ads_t ads[9];
	int a1[1];
	int a2[2][2];
	int a3[5][5];
	int i;

	ads[0].array = NULL; ads[0].length = 0; ads[0].answer = 0;

	a1[0] = 100;
	ads[1].array = a1; ads[1].length = 1; ads[1].answer = 0;


	a2[0][0] = 2; a2[0][1] = 3;
	a2[1][0] = 2; a2[1][1] = 4;
	ads[2].array = &a2[0][0]; ads[2].length = 2; ads[2].answer = 0;
	ads[3].array = &a2[1][0]; ads[3].length = 2; ads[3].answer = 3;

	a3[0][0] = 1; a3[0][1] = 3; a3[0][2] = 4; a3[0][3] = 5; a3[0][4] = 6;
	a3[1][0] = 1; a3[1][1] = 2; a3[1][2] = 4; a3[1][3] = 5; a3[1][4] = 6;
	a3[2][0] = 1; a3[2][1] = 2; a3[2][2] = 3; a3[2][3] = 5; a3[2][4] = 6;
	a3[3][0] = 1; a3[3][1] = 2; a3[3][2] = 3; a3[3][3] = 4; a3[3][4] = 6;
	a3[4][0] = 1; a3[4][1] = 2; a3[4][2] = 3; a3[4][3] = 4; a3[4][4] = 5;

	ads[4].array = &a3[0][0]; ads[4].length = 5; ads[4].answer = 2;
	ads[5].array = &a3[1][0]; ads[5].length = 5; ads[5].answer = 3;
	ads[6].array = &a3[2][0]; ads[6].length = 5; ads[6].answer = 4;
	ads[7].array = &a3[3][0]; ads[7].length = 5; ads[7].answer = 5;
	ads[8].array = &a3[4][0]; ads[8].length = 5; ads[8].answer = 0;

	for (i=0; i<9; i++) {
		int answer = find( ads[i].array, ads[i].length);
		printf("%d : %d \n", answer, ads[i].answer );
		assert( answer == ads[i].answer);
	}
	
}
