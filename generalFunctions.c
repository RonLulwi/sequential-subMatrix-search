#include "generalFunctions.h"


void readFile(double* threshold, int* numOfPics, Image*** images, int* numOfObs, Image*** objects)
{
	// open input file
	FILE* file = fopen(INPUT_FILE_NAME, "r");
	
	if (!file)
	{
		fprintf(stderr, "file can't be opened \n");
		exit(1);
	}
	
	// matching value
	fscanf(file, "%lf", threshold);
	
	// number of pictures
	fscanf(file, "%d", numOfPics);
	
	// allocate images array
	*images = (Image**) malloc(*numOfPics * sizeof(Image*));
	if (! (*images) )
	{
		fprintf(stderr, "Problem to allocate memory\n");
		exit(1);
	}
	
	// images
	for (int i = 0; i < *numOfPics; i++)
	{
		readImage(file, (*images) + i);
	}
	
	// number of objects
	fscanf(file, "%d", numOfObs);
	
	// allocate abjects array
	*objects = (Image**) malloc(*numOfObs * sizeof(Image*));
	if (! (*objects) )
	{
		fprintf(stderr, "Problem to allocate memory\n");
		exit(1);
	}
	
	// objects
	for (int i = 0; i < *numOfObs; i++)
	{
		readImage(file, (*objects) + i);
	}
	
	// close input file
	fclose(file);
}

void readImage(FILE* file, Image** image)
{
	// allocate image
	*image = (Image*) malloc(sizeof(Image));
	
	if (! (*image) )
	{
		fprintf(stderr, "Problem to allocate memory\n");
		exit(1);
	}
	
	// image id
	fscanf(file, "%d", &((*image)->id));
	
	// image dimension
	fscanf(file, "%d", &((*image)->dim));
	
	int numOfElements = ((*image)->dim) * ((*image)->dim);
	
	// allocate image elements
	(*image)->image = (int*) malloc(numOfElements * sizeof(int));
	if (! ((*image)->image) )
	{
		fprintf(stderr, "Problem to allocate memory\n");
		exit(1);
	}
	
	// image elements
	for (int i = 0; i < numOfElements; i++)
	{
		fscanf(file, "%d", ((*image)->image) + i);
	}
}

void initMatches(Match*** matches, int numOfPics)
{
	*matches = (Match**) malloc(numOfPics * sizeof(Match*));
	if (! (*matches) )
	{
		fprintf(stderr, "Problem to allocate memory\n");
		exit(1);
	}
	
	for (int i = 0; i < numOfPics; i++)
	{
		initMatch((*matches) + i);
	}
}

void initMatch(Match** match)
{
	*match = (Match*) malloc(sizeof(Match));
	if (! (*match) )
	{
		fprintf(stderr, "Problem to allocate memory\n");
		exit(1);
	}
	
	(*match)->pos = (Position*) malloc(sizeof(Position));
	if (! ((*match)->pos) )
	{
		fprintf(stderr, "Problem to allocate memory\n");
		exit(1);
	}
}

void printResultsToFile(Match** matches, int numOfPics)
{
	// open output file
	FILE* file = fopen(OUTPUT_FILE_NAME, "w");
	
	if (!file)
	{
		fprintf(stderr, "file can't be opened \n");
		exit(1);
	}
	
	// print results
	for (int i = 0; i < numOfPics; i++)
	{
		int imageId = (matches[i])->imageId;
		int objectId = (matches[i])->objectId;
		Position* pos = (matches[i])->pos;
		
		if (objectId != -1) // object was found in image
		{
			fprintf(file, "Picture %d found Object %d in Position (%d,%d)\n", imageId,  objectId, pos->i, pos->j);
		}
		else // no object was found in image
		{
			fprintf(file, "Picture %d No Objects were found\n", imageId);
		}
	}
	
	// close output file
	fclose(file);	
}


void freeAll(Image** images, int numOfPics, Image** objects, int numOfObs, Match** matches)
{
	// images
	for (int i = 0; i < numOfPics; i++)
	{
		freeImage(images[i]);
	}
	free(images);
	
	// objects
	for (int i = 0; i < numOfObs; i++)
	{
		freeImage(objects[i]);
	}
	free(objects);
	
	// matches
	for (int i = 0; i < numOfPics; i++)
	{
		freeMatch(matches[i]);
	}
	free(matches);
}

void freeImage(Image* image)
{
	free(image->image);
	free(image);
}

void freeMatch(Match* match)
{
	free(match->pos);
	free(match);
}


