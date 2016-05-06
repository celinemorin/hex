#include "interface.h"
#include "interfaceJeu.h"
 
#define HAUTEUR 600 
#define LARGEUR 800 
#define PLACEMENTHAUT 135
#define PLACEMENTLARG 100
#define PI 3.14159265

int main()
{
  int res;
  do
  {
  res = creation_interface(1);
  if(res==1)
    res = creation_interface(2);
  }while(res==4);
  
  if(res==5)
    creation_interface_jeu(3);

}