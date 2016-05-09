#include "interface.h"
#include <unistd.h>

Axe recuperationCellule(Axe position)
{
  Axe posRes;
  
  // On enlève le nombre de pixel ajouté par le placement de l'image + 19 pixel ajouté par l'image
  posRes.y = (position.y - 19 - POSJEUY);
  
  // On enlève le nombre de pixel ajouté par le placement de l'image + 19 pixel ajouté par l'image + le décalage de chaque Y
  posRes.x=(position.x - 150 - 19 - (15 * (posRes.y/25)));
  
  // Si le curseur se trouve dans le petit rectangle du haut du carré il faut calculer si il est a sa place ou pas
  if(posRes.y%25<6)
  {
    // Si on est dans le petit triangle de droite on réduit y de y (donc on enlève 25)
    if(posRes.x%30 < 13-(posRes.y%25)*2)
    {
      posRes.y=posRes.y - 25;
    }
    // Si on est dans le petit triangle de gauche ça réduit x de 1 (donc on enlève 30) et y de 1 (donc on enlève 25)
    if(posRes.x%30 > 15+(posRes.y%25)*2)
    {
      posRes.x=posRes.x+30;
      posRes.y=posRes.y-25;
    }
    // Si c'est plus petit que 0 et qu'on le divise on aura 0 mais on veut -1 donc on enlève 25
    else
    {
      if(posRes.x < 0)
	posRes.x=posRes.x-30;
    }
  }
  // Si c'est plus petit que 0 et qu'on le divise on aura 0 mais on veut -1 donc on enlève 25
  else
  {
    if(posRes.x < 0)
      posRes.x=posRes.x-30;
  } 
  
  // Si c'est plus petit que 0 et qu'on le divise on aura 0 mais on veut -1 donc on enlève 25
  if(posRes.y<0)
    posRes.y=posRes.y-25;
  
  // On divise par 30 ou 25 et on ajoute 1 pour avoir des cases comprises entre 1 et 11
  posRes.x=(posRes.x/30)+1;
  posRes.y=(posRes.y/25)+1;

  return posRes;
}

void placement_pion(SDL_Surface *ecran, Axe position, int couleur)
{
  position.x = (position.x * 30) + POSX + 39 + ((position.y - 1)*15);
  position.y = (position.y * 25) + POSJEUY -6 ;
  if((couleur == 0) || (couleur == 1) || (couleur == 2))
    chargementUneImage(ecran,"Images/HexaGris.png",position.x,position.y);
  if(couleur == 1)
  {
    position.x=position.x+4;
    position.y=position.y+5;
    chargementUneImage(ecran,"Images/button-red22.png",position.x,position.y);
  }
  if(couleur == 2)
  {
    position.x=position.x+4;
    position.y=position.y+5;
    chargementUneImage(ecran,"Images/button-blue22.png",position.x,position.y);
  }
  if(couleur == 3)
    chargementUneImage(ecran,"Images/HexaJaune.png",position.x,position.y);
    
}

void affichageGeneral(SDL_Surface *ecran, Infos varInfo)
{
  int i,j;
  Axe caseEnCours;
  for(i=0;i<11;i++)
  {
    caseEnCours.x=i+1;
    for(j=0;j<11;j++)
    {
      caseEnCours.y=j+1;
      placement_pion(ecran,caseEnCours,varInfo->plateau[i][j]);
    }
  }

  chargementUneImage(ecran,"Images/Gris.png",0,480);
  chargementUneImage(ecran,"Images/Gris.png",100,480);
  TTF_Init();
  SDL_Rect posTexte;
  SDL_Surface *texte;

  TTF_Font *policeTexte = TTF_OpenFont("Font/Arvo-Regular.ttf",20);
  SDL_Color couleurTexte = {255,255,255};
  int *tab = historique (1);

  if((tab[0]<3) && (tab[0]>0))
  {
    char leTexte[50]="Dernier coup joue : ";
  
    char inter[5];
    sprintf(inter,"%d",tab[1]);
    strcat(leTexte,inter);
    strcat(leTexte," ; ");
    sprintf(inter,"%d",tab[2]);
    strcat(leTexte,inter);

    texte = TTF_RenderText_Blended(policeTexte,leTexte,couleurTexte);

    posTexte.x = 10;
    posTexte.y = 480;

    SDL_BlitSurface(texte,NULL,ecran,&posTexte);
  }

}

void interfaceHistorique(SDL_Surface *ecran, Infos varInfo)
{  
  int *tab = historique (1);
  if((tab[0]<3) && (tab[0]>0))
  {
    TTF_Init();
    SDL_Rect posTexte;
    SDL_Surface *texte;
    
    TTF_Font *policeTexte = TTF_OpenFont("Font/Arvo-Regular.ttf",20);
    SDL_Color couleurTexte = {255,255,255};
    int i;
    char leTexte[50];
    char inter[5];
    
    strcpy(leTexte,"Historique : ");
    posTexte.x = 10;
    posTexte.y = 300;
    Axe dernierCoup;
    texte = TTF_RenderText_Blended(policeTexte,leTexte,couleurTexte);
    SDL_BlitSurface(texte,NULL,ecran,&posTexte);
    chargementUneImage(ecran,"Images/Gris.png",0,320);
    chargementUneImage(ecran,"Images/Gris.png",0,380);
    chargementUneImage(ecran,"Images/Gris.png",0,420);
    dernierCoup.x=0;
    dernierCoup.y=0;
    
    
    for(i=1;i<6;i++)
    {
      strcpy(leTexte,"");
      tab = historique (i);
      snprintf(inter,sizeof(inter),"%d",tab[1]);
      strcat(leTexte,inter);
      strcat(leTexte," ; ");
      snprintf(inter,sizeof(inter),"%d",tab[2]);
      strcat(leTexte,inter);
      if((dernierCoup.x!=tab[1]) || (dernierCoup.y!=tab[2]))
      {
	posTexte.x = 10;
	posTexte.y = (i*25)+300;
	texte = TTF_RenderText_Blended(policeTexte,leTexte,couleurTexte);
	SDL_BlitSurface(texte,NULL,ecran,&posTexte);
	dernierCoup.x=tab[1];
	dernierCoup.y=tab[2];
      }
   
    }
  }
  
}

Axe allerSuivante(SDL_Surface *ecran, int joueur,Infos varInfo)
{
  
  Axe casePrec;
  
 
  casePrec.x=1;
  casePrec.y=1;
  while(varInfo->plateau[casePrec.x-1][casePrec.y-1] !=0)
  {
    casePrec.x++;
    if(casePrec.x >11)
    {
      casePrec.x=1;
      casePrec.y++;
    }
  }
  placement_pion(ecran,casePrec, joueur );

  return casePrec; 
}

Axe attente_evenement_jeu(SDL_Surface *ecran, Infos varInfo, int joueur)
{    

  SDL_Event evenement; 
  Axe clic,position,casePrecedente;
  casePrecedente.x=0;
  casePrecedente.y=0;
  SDLKey key_pressed ;
  while (1)
  {
    while ( SDL_PollEvent(&evenement))
    {
      switch (evenement.type)
      {
	case SDL_MOUSEMOTION:
	  position.x = evenement.motion.x;
	  position.y = evenement.motion.y;
	  if((position.x >270) && (position.x <440) && (position.y>535) && (position.y<570))
	    chargementUneImage(ecran,"Images/Annuler4.png",50,500);
	  else
	    chargementUneImage(ecran,"Images/Annuler3.png",50,500);
	  if((position.x >540) && (position.x <760) && (position.y>535) && (position.y<570))
	    chargementUneImage(ecran,"Images/Historique4.png",350,505);
	  else
	    chargementUneImage(ecran,"Images/Historique3.png",350,505);
	    
	  position = recuperationCellule(position);
	  if((position.x > 0) && (position.x < 12) && (position.y > 0) && (position.y < 12) && (varInfo->plateau[position.x-1][position.y-1] == 0))
	  {
	    placement_pion(ecran,casePrecedente,0);
	    casePrecedente.x=position.x;
	    casePrecedente.y=position.y;
	    placement_pion(ecran,position, joueur );
	  }
	  break;
	case SDL_MOUSEBUTTONDOWN:
	  if (evenement.button.button == SDL_BUTTON_LEFT)
	  {   
	    clic.x = evenement.motion.x;
	    clic.y = evenement.motion.y;
	    if((clic.x >270) && (clic.x <440) && (clic.y>535) && (clic.y<570))
	    {
	      clic.x=-1;
	      return clic;
	    }
	    if((clic.x >540) && (clic.x <760) && (clic.y>535) && (clic.y<570))
	    {
	      interfaceHistorique(ecran,varInfo);
	    }
	    else
	    {
	      chargementUneImage(ecran,"Images/Gris.png",0,300);
	      chargementUneImage(ecran,"Images/Gris.png",0,350);
	      chargementUneImage(ecran,"Images/Gris.png",0,400);
	    }
	    //if((clic.x >540) && (clic.x <760) && (clic.y>535) && (clic.y<570))
	    clic = recuperationCellule(clic);
	    if((clic.x > 0) && (clic.x < 12) && (clic.y > 0) && (clic.y < 12))
	      return clic;
	  }
	  break;
	case SDL_KEYDOWN:
	  key_pressed = evenement.key.keysym.sym; // on récupère la touche
	  switch (key_pressed)
	  {
	    case SDLK_ESCAPE: /* Esc keypress quits the app... */
	      exit(0);
	      break;
	    case SDLK_LEFT:
	      if((casePrecedente.x ==0) &&(casePrecedente.y==0))
		casePrecedente= allerSuivante(ecran,joueur,varInfo);
	      else
	      {
		placement_pion(ecran,casePrecedente, 0 );
		do
		{
		  casePrecedente.x--;
		  if(casePrecedente.x <1)
		    casePrecedente.x=11;
		}while(varInfo->plateau[casePrecedente.x-1][casePrecedente.y-1] !=0);
		placement_pion(ecran,casePrecedente, joueur );
	      }
	      break;
	    case SDLK_RIGHT:
	      if((casePrecedente.x ==0) &&(casePrecedente.y==0))
		casePrecedente= allerSuivante(ecran,joueur,varInfo);
	      else
	      {
		placement_pion(ecran,casePrecedente, 0 );
		do
		{
		  casePrecedente.x++;
		  if(casePrecedente.x >11)
		    casePrecedente.x=1;
		}while(varInfo->plateau[casePrecedente.x-1][casePrecedente.y-1] !=0);
		placement_pion(ecran,casePrecedente, joueur );
	      }
	      break;
	    case SDLK_UP:
	      if((casePrecedente.x ==0) &&(casePrecedente.y==0))
		casePrecedente= allerSuivante(ecran,joueur,varInfo);
	      else
	      {
		placement_pion(ecran,casePrecedente, 0 );
		do
		{
		  casePrecedente.y--;
		  if(casePrecedente.y <1)
		    casePrecedente.y=11;
		}while(varInfo->plateau[casePrecedente.x-1][casePrecedente.y-1] !=0);
		placement_pion(ecran,casePrecedente, joueur );
	      }
	      break;
	    case SDLK_DOWN:
	      if((casePrecedente.x ==0) &&(casePrecedente.y==0))
		casePrecedente= allerSuivante(ecran,joueur,varInfo);
	      else
	      {
		placement_pion(ecran,casePrecedente, 0 );
		do
		{
		  casePrecedente.y++;
		  if(casePrecedente.y <1)
		    casePrecedente.y=11;
		}while(varInfo->plateau[casePrecedente.x-1][casePrecedente.y-1] !=0);
		placement_pion(ecran,casePrecedente, joueur );
	      }
	      break;
	    default:
	      break;
	    case SDLK_RETURN:
	      if((casePrecedente.x!=0) &&(casePrecedente.y!=0))
		return casePrecedente;
	    case SDLK_KP_ENTER:
	      if((casePrecedente.x!=0) &&(casePrecedente.y!=0))
		return casePrecedente;
	  }
	  break;
	case SDL_QUIT:
	  exit(0);
	  break;
	default:
	  break;
      }
    }
    SDL_Flip(ecran); 
  }
  return clic;
}

void creation_interface_jeu(SDL_Surface *ecran,int numMenu)
{
  

  Uint32 grey = SDL_MapRGB(ecran->format,173,173,173); // c'est du gris
  SDL_FillRect(ecran,NULL,grey); // de la couleur dans le fond de la fenêtre principale

  
  initialisationImage(ecran,numMenu);


  /* Free SDL library */
  SDL_FreeSurface(ecran);
}
