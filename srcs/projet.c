#include "interface.h"
#include "interfaceJeu.h"
 
#define HAUTEUR 600 
#define LARGEUR 800 
#define PLACEMENTHAUT 135
#define PLACEMENTLARG 100
#define PI 3.14159265

int main()
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
  ecran = SDL_SetVideoMode(fenetre.w, fenetre.h, video_bpp, videoflags); 
  if (ecran == NULL)
  {
    fprintf(stderr, "N'arrive pas a` etablir mode video%dx%dx%d : %s\n", fenetre.w, fenetre.h, video_bpp, SDL_GetError());
    SDL_Quit();
    exit(2);
  }  
  
  bool gagnant = false;
  int res;
  Axe unClicValide;
  
  // Tant que le joueur reste dans le menu (si il clique sur jouer/retour) on reste ici
  do
  {
    res = creation_interface(ecran,1); // interface de menu n°1
    if(res==1) // res == 1 si il a cliqué sur jouer
    {
      ecran = SDL_SetVideoMode(fenetre.w, fenetre.h, video_bpp, videoflags); // reset de l'écran
      res = creation_interface(ecran,2); // interface de menu n°2
    }
  }while(res==4); //  res == 4 si il a cliqué sur retour
  
  if(res==5) // si le joueur a choisi humain vs humain
  {
    creation_interface_jeu(ecran,3);
    while(gagnant == false)
    {
      unClicValide = attente_evenement_jeu(ecran);
      placement_pion(ecran,unClicValide,1);
      unClicValide = attente_evenement_jeu(ecran);
      placement_pion(ecran,unClicValide,2);
      
    }
  }

}