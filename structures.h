#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

typedef struct {
  xmlChar * ref;



}nd;

typedef struct{
  xmlChar * k;
  xmlChar * v;
}tag;

typedef struct{
  xmlChar * id;
  SDL_Point point;
}listPoint;


struct node{
  xmlChar * id;
  xmlChar * visible;
  xmlChar * lat;
  xmlChar * lon;
};
typedef struct node nodes;


struct list_node{
  nodes n;
  struct list_node * suivant;

};
  typedef struct list_node list_node;

struct list_nd{
  nd a;
  struct list_nd * suivant;
};

typedef struct list_nd list_nd;




typedef struct {
  xmlChar * id;
  xmlChar * visible;
  nd * liste_ref;
  int curs;
  int taille;
  tag * liste_tag;
  int curstag;
  int tailletag;
  int isArea;
}way;


struct list_way{
  way w;
  struct list_way * suivant;

};
  typedef struct list_way list_way;
