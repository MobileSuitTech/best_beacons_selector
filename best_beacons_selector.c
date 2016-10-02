/* Copyright (C) 2016 "owner of MobileSuitTech Github account */

/* 
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* this programs solves the following problem:
You have eight angles around a point which is your robot location.
Each angle represents the angular position of a beacon that is
around the robot. Out of these eight(or more) angles, find the best 
three angles. Best here means that they should be as spread apart from 
each other as possible. The ultimate combination for instance would be 
if your angles were spread apart by 120 degrees.
*/
/* credit for the algorithm to enumerate all possible combinations of 
a set of things goes to these guys:
https://www.cs.utexas.edu/users/djimenez/utsa/cs3343/lecture25.html
*/
/* by the way: this program not final and very prototypy, the algo 
used is not the fastest, increasing the length of combinations is not 
handled for more than 3. These will be object of future improvements 
of the source code.
*/

#include <stdio.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define ALL_EQUAL(a,b,c,d) ((a==b) && (a==c) && (a==d)))

#define MAXCOMBS 56
#define NBANGLES 8
#define SUBANGLES 3

int main(void){

	int n, k, i, j, row, col, c;
	int weight1, weight2, weight3, new_weight, best_weight, best_index;
	float angles[NBANGLES] = {40.000000, 31.000000, 109.000000, 347.000000, 30.000000, 114.000000, 36.000000, 41.000000 };
	//{ 126.000000, 244.000000, 311.000000, 232.000000, 262.000000, 277.000000, 169.000000, 343.000000 };
	//{ 340.000000, 322.000000, 89.000000, 11.000000, 308.000000, 89.000000, 102.000000, 68.000000 };
	//{ 298.0, 17.0, 235.0, 207.0, 253.0, 282.0, 249.0, 265.0 }
	//{ 298.0, 17.0, 235.0, 207.0, 253.0, 90.0, 210.0, 330.0 }
	float angles_combinations[MAXCOMBS][NBANGLES] = { 0 };

	int firstabs, secondabs;

	n = NBANGLES;
	k = SUBANGLES;
	//create the list of combinations of angles from the array of angles
	for (i = 0, row = 0; i < (1 << n); i++) {

		for (j = 0, c = 0; j < 32; j++) if (i & (1 << j)) c++;

		if (c == k) {
			for (j = 0, col = 0; j < 32; j++){
				if (i & (1 << j)){
					angles_combinations[row][col] = angles[j];
					col++;
				} 
			} 
			//increment the combinations index to fill the next row
			row++;
		}
	}
	//now display all the combinations:
	for(i = 0; i < MAXCOMBS; i++){
		//print the row elements
		for(j = 0; j < SUBANGLES; j++){
			//print element and a space
			printf("%f ", angles_combinations[i][j]);
		}
		//put a new line
		puts("");
	}

	//now pick the best of these combinations
	best_index = 0;
	best_weight = 1000;//to make a real value replace this one
	for(i = 0; i < MAXCOMBS; i++){
		// calculate weights 1 2 3, add them for the final weight,
		firstabs = abs((int) angles_combinations[i][0] - (int) angles_combinations[i][1]);
		if(firstabs > 180){
			firstabs = abs(firstabs - 360);
		}
		weight1 = abs(firstabs - 120);
		if(90 == (int)angles_combinations[i][0] && 210 == (int)angles_combinations[i][1] && 330 == (int)angles_combinations[i][2]){
			puts("here we go 90 210 330");
			puts("this is the interesting case");
			printf("firstabs and secondabs are %d %d\n", firstabs, secondabs);
		}		
		firstabs = abs((int) angles_combinations[i][1] - (int) angles_combinations[i][2]);
		if(firstabs > 180){
			firstabs = abs(firstabs - 360);
		}
		weight2 = abs(firstabs - 120);
		firstabs = abs((int) angles_combinations[i][2] - (int) angles_combinations[i][0]);
		if(firstabs > 180){
			firstabs = abs(firstabs - 360);
		}
		weight3 = abs(firstabs - 120);
		// store the current weight
		new_weight = weight1 + weight2 + weight3;
		//do more stuff here to find if this weight is the best
		if(new_weight < best_weight){
			best_weight = new_weight;
			best_index = i;
			printf("best_weight is %d\n", new_weight);
		}
	}
	printf("the best index found was: %d \n", best_index);
	//display the angles at the index we found
	puts("");
	printf("the best combination of angles (there may be more equally as good) is: %f %f %f\n",
	 angles_combinations[best_index][0],
	  angles_combinations[best_index][1],
	   angles_combinations[best_index][2]);

	return 0;
}