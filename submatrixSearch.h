#ifndef SUBMATRIX_SEARCH_H_
#define SUBMATRIX_SEARCH_H_

#include "structs.h"
#include <stdlib.h>

double matching(int* image, int imageDim, Image* object);

int findObjectInImage(Image* image, Image* object, double threshold, Position* pos);

void findAllObjectsInImage(Image* image, Image** objects, int numOfObs, double threshold, Match* match);

void findAllObjectsInAllImages(Image** images, int numOfPics, Image** objects, int numOfObs, double threshold, Match** matches);

#endif
