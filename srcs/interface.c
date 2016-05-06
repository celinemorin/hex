#include "interface.h"



void chargementUneImage(SDL_Surface *ecran, char * emplacement,int x,int y)
{
  /* Déclaration des variables */
  SDL_Surface *image;
  SDL_Rect posBoard; 
  
  /* On ajouter l'image */
  image = IMG_Load(emplacement);                     
  posBoard.x = x;
  posBoard.y = y;
  SDL_BlitSurface(image,NULL,ecran,&posBoard);
  
  /* On free la surface */
  SDL_FreeSurface(image);  
}

void initialisationImage(SDL_Surface *ecran, int numeroMenu)
{
  /* On s'occupe du titre */ 
  TTF_Init();
  SDL_Rect posTexte;
  SDL_Surface *texte;
  
  TTF_Font *policeTexte = TTF_OpenFont("Font/Orange.ttf",120);
  SDL_Color couleurTexte = {255,255,255};
  texte = TTF_RenderText_Blended(policeTexte,"Jeu du Hex",couleurTexte);

  posTexte.x = 130;
  posTexte.y = 35;

  SDL_BlitSurface(texte,NULL,ecran,&posTexte);

  if(numeroMenu == 1)
  {
    chargementUneImage(ecran,"Images/MenuJouer1.png",POSX,POSJOUERY);
    chargementUneImage(ecran,"Images/MenuChargement1.png",POSX,POSCHARGY);
    chargementUneImage(ecran,"Images/MenuQuitter1.png",POSX,POSQUITY);
  }
  else if(numeroMenu == 2)
  {
    chargementUneImage(ecran,"Images/MenuHumainVsHumain1.png",POSX,POSHVHY);
    chargementUneImage(ecran,"Images/MenuHumainVsIA1.png",POSX,POSHV1Y);
    chargementUneImage(ecran,"Images/MenuHumainVsIA3.png",POSX,POSHV2Y);
    chargementUneImage(ecran,"Images/MenuRetour1.png",POSX,POSRETOURY);
  }
  else if(numeroMenu == 3)
  {
    chargementUneImage(ecran,"Images/hex.png",POSX+50,POSJEUY);
  }
  
  SDL_FreeSurface(texte);
  TTF_CloseFont(policeTexte);
}


void souriPos(SDL_Surface *ecran,Axe pos,int numeroMenu)
{
  if(numeroMenu==1)
  {
    if((pos.x > 310) && (pos.x < 490) && (pos.y >230) && (pos.y< 280))
      chargementUneImage(ecran,"Images/MenuJouer2.png",POSX,POSJOUERY);
    else
      chargementUneImage(ecran,"Images/MenuJouer1.png",POSX,POSJOUERY);
    if((pos.x > 210) && (pos.x < 560) && (pos.y >320) && (pos.y< 370))
      chargementUneImage(ecran,"Images/MenuChargement2.png",POSX,POSCHARGY);
    else
      chargementUneImage(ecran,"Images/MenuChargement1.png",POSX,POSCHARGY);
    if((pos.x > 290) && (pos.x < 480) && (pos.y >480) && (pos.y< 530))
      chargementUneImage(ecran,"Images/MenuQuitter2.png",POSX,POSQUITY);
    else
      chargementUneImage(ecran,"Images/MenuQuitter1.png",POSX,POSQUITY);
  }
  if(numeroMenu==2)
  {
    if((pos.x > 140) && (pos.x < 660) && (pos.y >220) && (pos.y< 280))
      chargementUneImage(ecran,"Images/MenuHumainVsHumain2.png",POSX,POSHVHY);
    else
      chargementUneImage(ecran,"Images/MenuHumainVsHumain1.png",POSX,POSHVHY);
    if((pos.x > 180) && (pos.x < 620) && (pos.y >330) && (pos.y< 380))
      chargementUneImage(ecran,"Images/MenuHumainVsIA2.png",POSX,POSHV1Y);
    else
      chargementUneImage(ecran,"Images/MenuHumainVsIA1.png",POSX,POSHV1Y);
    if((pos.x > 180) && (pos.x < 620) && (pos.y >430) && (pos.y< 480))
      chargementUneImage(ecran,"Images/MenuHumainVsIA4.png",POSX,POSHV2Y);
    else
      chargementUneImage(ecran,"Images/MenuHumainVsIA3.png",POSX,POSHV2Y);
    if((pos.x > 300) && (pos.x < 510) && (pos.y >520) && (pos.y< 580))
      chargementUneImage(ecran,"Images/MenuRetour2.png",POSX,POSRETOURY);
    else
      chargementUneImage(ecran,"Images/MenuRetour1.png",POSX,POSRETOURY);
  }
}


int attente_evenement_menu(SDL_Surface *ecran, int numeroMenu)
{    

  bool attente = true;
  SDL_Event evenement;
  Axe clic,position;

  SDLKey key_pressed ;
  while (attente)
  {
    while ( SDL_PollEvent(&evenement))
    {
      switch (evenement.type)
      {
	case SDL_MOUSEMOTION:
	  position.x = evenement.motion.x;
	  position.y = evenement.motion.y;
	  souriPos(ecran,position,numeroMenu);
	  break;
	case SDL_MOUSEBUTTONDOWN:
	  if (evenement.button.button == SDL_BUTTON_LEFT)
	  {
	    if(numeroMenu==1)
	    {
	      if((evenement.motion.x > 310) && (evenement.motion.x < 490) && (evenement.motion.y >230) && (evenement.motion.y< 280))
		return JOUER;
	      if((evenement.motion.x > 210) && (evenement.motion.x < 560) && (evenement.motion.y >320) && (evenement.motion.y< 370))
		return CHARGEMENT;
	      if((evenement.motion.x > 290) && (evenement.motion.x < 480) && (evenement.motion.y >480) && (evenement.motion.y< 530))
		return QUITTER;
	    }
	    else if(numeroMenu==2)
	    {
	      if((evenement.motion.x > 140) && (evenement.motion.x < 660) && (evenement.motion.y >220) && (evenement.motion.y< 280))
		return NEWGAME;
	      if((evenement.motion.x > 300) && (evenement.motion.x < 510) && (evenement.motion.y >520) && (evenement.motion.y< 580))
		return RETOUR;
	    }
	  }
	  break;
	case SDL_KEYDOWN:
	  key_pressed = evenement.key.keysym.sym; // on récupère la touche
	  switch (key_pressed)
	  {
	  case SDLK_ESCAPE: /* Esc keypress quits the app... */
	    attente = false;
	    break;
	  case SDLK_LEFT:
	    printf("left +1\n"); // par exemple
	    break;
	  case SDLK_RIGHT:
	    printf("right +1\n"); 
	    break;
	  case SDLK_UP:
	    printf("up +1\n");
	    break;
	  case SDLK_DOWN:
	    printf("down +1\n");
	    break;
	  }
	  break;
	case SDL_QUIT:
	  exit(1);
	  break;
	default:
	  break;
      }
    }
    // refresh screen
    // mettre ici tous les blit utiles s'il y a des changements dans les surfaces, board, nouveaux pions
    SDL_Flip(ecran); //maj des surfaces pour affichage
  }
}


int creation_interface(SDL_Surface *ecran,int numMenu)
{
 
  initialisationImage(ecran,numMenu);
  int res = attente_evenement_menu(ecran,numMenu);


  /* Free SDL library */
  SDL_FreeSurface(ecran);

  return(res);
}

/*
int main()
{
  creation();
}
*/



