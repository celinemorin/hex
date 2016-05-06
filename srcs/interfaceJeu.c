#include "interfaceJeu.h"

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
  
  posRes.x=posRes.x/30;
  posRes.y=posRes.y/25;
  
  printf("\n%d ; %d\n",posRes.x,posRes.y);
  posRes.x=1;
  return posRes;
}



Axe attente_evenement_jeu(SDL_Surface *ecran)
{    

  bool attente;
  SDL_Event evenement; 
  Axe clic;

  attente = true; 
  SDLKey key_pressed ;
  while (attente)
    {
    while ( SDL_PollEvent(&evenement))
    {
      switch (evenement.type)
      {
	case SDL_MOUSEMOTION:
	  //printf("Ça bouge\n"); // sans intérêt, c'est juste pour montrer
	  break;
	case SDL_MOUSEBUTTONDOWN:
	  if (evenement.button.button == SDL_BUTTON_LEFT)
	  {   
	  clic.x = evenement.motion.x;
	  clic.y = evenement.motion.y;
	  printf("X=%d Y=%d\n",clic.x,clic.y); // on récupère les coordonnées du clic
	  recuperationCellule(clic);
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
	  exit(0);
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

Axe creation_interface_jeu(int numMenu)
{
  Uint32 initflags = SDL_INIT_VIDEO; 
  SDL_Surface *ecran; 

  Dimensions fenetre; // main window

  fenetre.h = HAUTEUR; 
  fenetre.w = LARGEUR;   
  Uint8  video_bpp = 32; // 32 bits de couleur

  Uint32 videoflags = SDL_HWSURFACE;  
  SDL_WM_SetCaption("Jeu de Hex", NULL); 

  /* Initialize the SDL library */
  if ( SDL_Init(initflags) < 0 )
  {
    fprintf(stderr, "N'arrive pas a` initialiser la SDL : %s\n", SDL_GetError());
    exit(1);
  }

  /* Set video mode */
  ecran = SDL_SetVideoMode(fenetre.w, fenetre.h, video_bpp, videoflags); // surface principale
  if (ecran == NULL)
  {
    fprintf(stderr, "N'arrive pas a` etablir mode video%dx%dx%d : %s\n", fenetre.w, fenetre.h, video_bpp, SDL_GetError());
    SDL_Quit();
    exit(2);
  }

  Uint32 grey = SDL_MapRGB(ecran->format,173,173,173); // c'est du gris
  SDL_FillRect(ecran,NULL,grey); // de la couleur dans le fond de la fenêtre principale
  
  initialisationImage(ecran,numMenu);
  Axe res = attente_evenement_jeu(ecran);


  /* Free SDL library */
  SDL_FreeSurface(ecran);
  return(res);
}