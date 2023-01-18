#ifndef GENERAL_FUNCTIONS_H_
#define GENERAL_FUNCTIONS_H_

#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

void readFile(double* threshold, int* numOfPics, Image*** images, int* numOfObs, Image*** objects);

void readImage(FILE* file, Image** image);

void initMatches(Match*** matches, int numOfPics);

void initMatch(Match** match);

void printResultsToFile(Match** matches, int numOfPics);

void freeAll(Image** images, int numOfPics, Image** objects, int numOfObs, Match** matches);

void freeImage(Image* image);

void freeMatch(Match* match);

#endif
