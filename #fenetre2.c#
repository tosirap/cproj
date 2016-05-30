#include <SDL2/SDL.h>
#include <stdio.h>
#include "Parserproj.h"
#include <SDL2/SDL2_gfxPrimitives.h> 
#include <math.h>

//int main(int argc, char** argv)

int main(int argc, char **argv){
  
  int quit =0;
  /* Initialisation simple */
  if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
      fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
      return -1;
    }
  
  {
    parser(argc, argv);
    /* Création de la fenêtre */
    SDL_Window* pWindow = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Renderer * renderer;
    SDL_Point* points;
    SDL_Point* lines;
    listPoint * listePoint;
    int x = 500;
    float n= ((x-80) /(maxlat-minlat));
    int y =  (int) (n *(maxlon-minlon)) ;
    printf("%f %i \n", n,y);
    
    SDL_CreateWindowAndRenderer(y, x, 0, &pWindow, &renderer);
   
    
    if( pWindow )
      {
        
	  SDL_SetWindowTitle(pWindow,"FENETRE OSM");

	  
	  //RENDERER
	  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	  SDL_RenderClear(renderer);
	  
	  
	  //afficher les Nodes
	  points = malloc(compteurNode*sizeof(SDL_Point));
	  listePoint= malloc(compteurNode*sizeof(listPoint));
	  float a= maxlat-minlat;
	  float b =maxlon-minlon;
	  int i;
	  for (i=0;i<compteurNode;i++){
	    float longi= atof ( listNode[i].lon);
	    float lati= atof ( listNode[i].lat);
	    float aa=maxlat-lati;
	    float bb=(minlon-longi)*(-1);
	    
	    points[i].y= (int) (((aa/a)*(x)));
	    points[i].x= (int) (((bb/b)*y));

	    //on enregistre les points dans la liste
	    listePoint[i].id=listNode[i].id;
	    listePoint[i].point=points[i];
	  }
	  SDL_SetRenderDrawColor(renderer, 55, 255, 0, 0);
	  SDL_RenderDrawPoints(renderer, points, compteurNode);
	  free(points);

	  //affiche ways
	  Sint16 * pointx ;
	  Sint16 * pointy ;
	  int red,green,blue;
	  int fill=0;
	  for(i=0;i<compteurStruct;i++){
	    lines=malloc(liststruct[i].curs*sizeof(SDL_Point));
	    pointx=malloc(liststruct[i].curs*sizeof(Sint16));
	    pointy=malloc(liststruct[i].curs*sizeof(Sint16));

	    
	    red=100;
	    green=100;
	    blue=100;
	    fill=0;
	    int l;
	    for(l=0;l<liststruct[i].curstag;l++){
	      if(strcmp(liststruct[i].liste_tag[l].k,"waterway")==0||
		strcmp(liststruct[i].liste_tag[l].v,"water")==0){
		red=0;
		green=0;
		blue=255;
		fill=0;
		//break;
	      }
	       if(strcmp(liststruct[i].liste_tag[l].k,"building")==0
		 ||strcmp(liststruct[i].liste_tag[l].k,"shop")==0
		 ||strcmp(liststruct[i].liste_tag[l].k,"amenity")==0
		 ||strcmp(liststruct[i].liste_tag[l].k,"boundary")==0
		 ||strcmp(liststruct[i].liste_tag[l].k,"office")==0
		 ||strcmp(liststruct[i].liste_tag[l].k,"building:part")==0
		 ||strcmp(liststruct[i].liste_tag[l].k,"historic")==0){
		red=100;
		green=100;
		blue=100;
		fill=0;
		//break;
		}
	      if(strcmp(liststruct[i].liste_tag[l].k,"highway")==0){
		red=255;
		green=0;
		blue=0;
		fill=1;
		//break;
	      }

	      if(strcmp(liststruct[i].liste_tag[l].v,"bridge")==0 || strcmp(liststruct[i].liste_tag[l].k,"bridge")==0 ){
		red=255;
		green=255;
		blue=255;
		fill=0;
		//break;
	      }
	      if(strcmp(liststruct[i].liste_tag[l].k,"barrier")==0){
		red=250;
		green=0;
		blue=250;
		fill=0;
		//break;
	      }
	      if(strcmp(liststruct[i].liste_tag[l].k,"boundary")==0){
		red=250;
		green=100;
		blue=250;
		fill=0;
		//break;
	      }
	      if(strcmp(liststruct[i].liste_tag[l].v,"beach")==0){
		red=50;
		green=10;
		blue=250;
		fill=0;
		//break;
	      }
	      if(strcmp(liststruct[i].liste_tag[l].k,"landuse")==0){
		red=20;
		green=60;
		blue=20;
		fill=1;
		//break;
	      }

	      if(strcmp(liststruct[i].liste_tag[l].k,"leisure")==0){
		red=50;
		green=250;
		blue=5;
		fill=0;  
		//break;
	      }
	      if(strcmp(liststruct[i].liste_tag[l].k,"parking")==0){
		red=50;
		green=200;
		blue=255;
		fill=0;
		//break;
	      }
	      if(strcmp(liststruct[i].liste_tag[l].k,"surface")==0){
		if(strcmp(liststruct[i].liste_tag[l].v,"wood")==0){
		
		  red=30;
		  green=250;
		  blue=5;
		  fill=0;
		  //break;
		}
	      }

	      
	      if(strcmp(liststruct[i].liste_tag[l].v,"locality")==0){
		red=50;
		green=200;
		blue=255;
		fill=1;;
		//break;
	      }
	      
	      /* else{
		red=100;
		green=100;
		blue=100;
		fill=0;
		}*/
	      
	    }
	      
	    int j;
	    for(j=0;j<liststruct[i].curs;j++){
	      int k;
	      if(strcmp(liststruct[i].visible,"true")==0){
		for(k=0;k<compteurNode;k++){
		  if(strcmp(listePoint[k].id,liststruct[i].liste_ref[j].ref)==0){
		    lines[j].x=listePoint[k].point.x;
		    lines[j].y=listePoint[k].point.y;
		    pointx[j]=(Sint16)lines[j].x;
		    pointy[j]=(Sint16)lines[j].y;
		    break;
		  }
		 
		}
	      }
	    }
	    
	    if(strcmp(liststruct[i].liste_ref[(liststruct[i].curs)-1].ref,liststruct[i].liste_ref[0].ref)==0){
	      if(fill==0){
		filledPolygonRGBA(renderer,pointx,pointy,liststruct[i].curs,red,green,blue,100);
	      }
	      else{
		polygonRGBA(renderer,pointx,pointy,liststruct[i].curs,red,green,blue,100);
	      }	      
	    }
	    else{
	      int parcours;
	      for (parcours=0; parcours<liststruct[i].curs-1;parcours++){
		thickLineRGBA(renderer,pointx[parcours],pointy[parcours],pointx[parcours+1],pointy[parcours+1],3,red,green,blue,100);
	      }
	    }
	   
	    free(lines);
	    free(pointx);
	    free(pointy);
	  }

	  SDL_RenderPresent(renderer);

	  SDL_UpdateWindowSurface( pWindow );
	  free(listePoint);
	  while(!quit){
	    SDL_Event event;
	    SDL_WaitEvent(&event); /* On attend un événement qu'on récupère dans event */
	  

	    
	    switch(event.type)
	      {
	      case SDL_QUIT: // Clic sur la croix
		quit=1;
		break;
	      }
	  }
	  SDL_DestroyRenderer(renderer);
	  SDL_DestroyWindow(pWindow);
      }
    else
      {
	fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
      }
  }
  
  SDL_Quit();
  
  return 0;
}

