#include "submatrixSearch.h"

double matching(int* image, int imageDim, Image* object)
{
	double matching = 0;
	int objectDim = object->dim;
	double diff;
	int p;
	int o;
	int k = 0;
	
	for (int i = 0; i < objectDim; i++)
	{
		for (int j = 0; j < objectDim; j++, k++)
		{
			p = *(image + imageDim *  i + j);
			o = (object->image)[k];
			diff = abs(p-o) / (double) p;
			matching = matching + diff;
		}
	}
	
	return matching;
}

int findObjectInImage( Image* image, Image* object, double threshold, Position* pos)
{
	int found = 0;
	int edge = image->dim - object->dim + 1;
	int* currentPos;
	
	pos->i = -1;
	pos->j = -1;
	
	for (int i = 0; i < edge && !found; i++)
	{
		for (int j = 0; j < edge && !found; j++)
		{
			currentPos = image->image + image->dim *  i + j;
			found = (matching(currentPos, image->dim, object) <= threshold);
			if (found)
			{
				pos->i = i;
				pos->j = j;
			}
		}
	}
	
	return found;
}

void findAllObjectsInImage(Image* image, Image** objects, int numOfObs, double threshold, Match* match)
{
	match->imageId = image->id;
	match->objectId = -1;
	
	for (int i = 0; i < numOfObs; i++)
	{
		if(findObjectInImage(image, objects[i], threshold, match->pos))
		{
			match->objectId = (objects[i])->id;
			return;
		}
	}
	
}

void findAllObjectsInAllImages(Image** images, int numOfPics, Image** objects, int numOfObs, double threshold, Match** matches)
{
	for (int i = 0; i < numOfPics; i++)
	{
		findAllObjectsInImage(images[i], objects, numOfObs, threshold, matches[i]);
	}
}
