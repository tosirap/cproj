#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "structures.h"
//#include "fenetre1.h"

float minlat,minlon,maxlat,maxlon;

way current;
way * liststruct;
nodes * listNode;
int compteurStruct=0;
int taille_struct=100;
int compteurNode=0;
int taille_malloc = 100;


//fonction affichant un élément du noeud 
void affiche(xmlNodePtr node){
  xmlChar *id;
  xmlChar *lat;
  xmlChar *lon;
  xmlChar *visible;
  nodes n;

  /*xmlNodePtr n=node;
    n= node ->xmlChildrenNode;*/
  if((!xmlStrcmp(node->name,(const xmlChar *)"bounds"))){
    minlat= atof(xmlGetProp(node,"minlat"));
    minlon= atof(xmlGetProp(node,"minlon"));
    maxlat= atof(xmlGetProp(node,"maxlat"));
    maxlon= atof(xmlGetProp(node,"maxlon"));

    printf("minlat : %f\n",minlat);
  }

  if ((!xmlStrcmp(node->name, (const xmlChar *)"node"))) {
    if(compteurNode>=taille_malloc-2){
      taille_malloc = taille_malloc*2;
      listNode=realloc(listNode, taille_malloc*sizeof(nodes));
      
    }
    id = xmlGetProp(node, "id");
    lat = xmlGetProp(node, "lat");
    lon=xmlGetProp(node, "lon");
    visible=xmlGetProp(node, "visible");
    
    
    //printf("node_id: %s", id);
    //printf("  node_lat: %s\n", lat);
    // xmlFree(id);
    n.id=id;
    n.visible=visible;
    n.lat=lat;
    n.lon=lon;
    
    listNode[compteurNode] = n;
    // printf("test n %i \n",sizeof(listNode));
    compteurNode ++;
    
    
  }
  else if ((!xmlStrcmp(node->name, (const xmlChar *)"way"))) {
    if(compteurStruct>=taille_struct-2){
      taille_struct = taille_struct*2;
      liststruct=realloc(liststruct, taille_struct*sizeof(way));
      
    }

    id = xmlGetProp(node, "id");
    visible= xmlGetProp(node,"visible");
    //printf("way: %s\n", id);
    way w;
    w.id=id;
    w.visible=visible;
    w.curs=0;
    w.taille=100;
    w.liste_ref= malloc(w.taille*sizeof(nd));
    w.curstag=0;
    w.tailletag=100;
    w.liste_tag=malloc(w.taille*sizeof(tag));
    current=w;
    liststruct[compteurStruct]=w;
    compteurStruct++;
    //xmlFree(id);
  }
  else if ((!xmlStrcmp(node->name, (const xmlChar *)"nd"))) {
    if(current.curs>=current.taille-1){
      current.taille = current.taille*2;
      current.liste_ref=realloc(current.liste_ref, current.taille*sizeof(nd));
      
    }
    
    id = xmlGetProp(node, "ref");
    //printf("nd: %s\n", id);

    nd temp;
    temp.ref=id;
    current.liste_ref[current.curs]=temp;
    current.curs++;
    liststruct[compteurStruct-1]=current;
    // xmlFree(id);
  }

  else if(compteurStruct!=0 && (!xmlStrcmp(node->name,(const xmlChar *)"tag"))){
    if(current.curstag>=current.tailletag){
      current.tailletag=current.tailletag*2;
      current.liste_tag=realloc(current.liste_tag,current.tailletag*sizeof(tag));				
    }
    xmlChar * k;
    xmlChar * v;
    k=xmlGetProp(node,"k");
    v=xmlGetProp(node,"v");
    current.liste_tag[current.curstag].k=k;
    current.liste_tag[current.curstag].v=v;
    current.curstag++;
    liststruct[compteurStruct-1]=current;
  }
}

//affiche liste node
void afficheListe(){
  int i;
  for(i=0;i<compteurNode;i++){
    printf("id node = %s \n",listNode[i].id);
  }
}

//affiche liste way
void affichelistway(){
  int i;
  int j;
  for (i=0; i<compteurStruct; i++){
    printf("voici l'id de la way : %s\n",liststruct[i].id);
    printf("debut de la list nd\n");
    for(j=0;j<liststruct[i].curs;j++){
      printf("nd ref: %s\n",liststruct[i].liste_ref[j].ref);
    }
  }
}



// fonction parcourant l'arbre en entier
void parcours(xmlNodePtr node){
  xmlNodePtr n= node;
  while(n!=NULL){
    affiche (n);
    if ((n->type == XML_ELEMENT_NODE) && (n->children != NULL)) {
      parcours(n->children);
    }
    n=n->next;
  }

}


int parser(int argc, char **argv){
  char *docname;
  xmlDocPtr doc;
  xmlNodePtr cur;

  listNode=malloc(taille_malloc*sizeof(nodes));
  liststruct= malloc(taille_struct*sizeof(way));
  
  if(argc<=1){
    printf("Usage: %s docname\n",argv[0]);
    return 0;
  }
  
  docname= argv[1];
  doc= xmlParseFile(docname);
  cur= xmlDocGetRootElement(doc);
  parcours(cur);
  //afficheListe();
  //affichelistway();
  
  
  
  return 0;
}





