#include "structures.h"

float minlat,minlon,maxlat,maxlon;
way current;
way * liststruct;
nodes * listNode;
int compteurStruct;
int taille_struct;
int compteurNode;
int taille_malloc;


int parser(int argc, char **argv);
