#include <stdio.h>
#include <time.h>
#include "generalFunctions.h"
#include "submatrixSearch.h"

// Ron Lulwi 205857394

int main(int argc, char* argv[])
{
	double threshold;
	int numOfPics; 
	Image** images; 
	int numOfObs; 
	Image** objects;
	Match** matches;
	
	// start timer
	clock_t begin = clock();
	
	// read input file
	readFile(&threshold, &numOfPics, &images, &numOfObs, &objects);
	
	// init matches
	initMatches(&matches, numOfPics);
	
	// search objects in images
	findAllObjectsInAllImages(images, numOfPics, objects, numOfObs, threshold, matches);
	
	// print results
	printResultsToFile(matches, numOfPics);
	
	//free allocated memory
	freeAll(images, numOfPics, objects, numOfObs, matches);
	
	// stop timer
	clock_t end = clock();
	
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time = %lf seconds\n", time_spent);
	
	return 0;
}

