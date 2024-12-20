#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE_O 15
#define TRUE 1
#define FALSE 0

typedef int boolean;

typedef struct
{
  int etat;
  boolean destroy;
}square;

typedef struct
{
  char nom[20];
  int len;
  int lenRemain;
}boat;

typedef square tocean[SIZE_O][SIZE_O];
typedef boat tflotte[5];

typedef struct
{
  tocean ocean;
  int boatRemain;
  tflotte flotte;
}profil;

int my_rand (int);
int lireClavier(void);
void init_game(profil*, profil*);
  void init_ocean(tocean, tocean);
  void init_boat(tflotte, tflotte);

void deploy_boat(profil*, profil*);
  void mission1_msg(void);
  void player_dplymt(profil*);
    void print_ocean(tocean);
    void mission1_1_msg(boat);
    void get_coordinates(tocean, boat, int*, int*, boolean[]);
      void read_coordinates(int*, int*);
      boolean check_coordinates(tocean, int, int, int, boolean[], boolean);
    int get_direction(boolean[],char[]);
      boolean msg_direction(boolean[],char[]);
      int read_cardinal(boolean[]);
    void set_map(tocean, int, int, int, int, int);
  void computer_dplymt(profil*);
    void getIA_coordinates(tocean,int, int*, int*, boolean[]);
    int getIA_direction(boolean[]);

void player_round(profil,profil*);
  void print_opponent_ocean(tocean);
  void set_attack(profil*, int, int);

void computer_round(profil*);
  void getAttack_coord(profil*, int*, int*);
  void setIA_attack(profil*, int,int);
  void set_aura(tocean, int, int, int);
  void set_aura_border(tocean, int,int,int);

int main(int argc, char* argv[])
{
  srand(time(NULL));
  profil computer, player;
  init_game(&player, &computer);
  deploy_boat(&player, &computer);
  while(player.boatRemain > 0 && computer.boatRemain > 0)
  {
    player_round(player, &computer);
    if(computer.boatRemain > 0)
    {
      computer_round(&player);
      printf("Votre Ocean : \n");
      print_ocean(player.ocean);
    }
  }
  if(computer.boatRemain > 0)
    printf("Vous avez perdu\n");
  else printf("Vous avez gagne\n");
  exit(EXIT_SUCCESS);
}
//----------------------ATTACK------------------------------------

void player_round(profil gamer, profil* computr)
{
  int x,y;
  printf("Ocean de l'adversaire !\n\n");
  print_opponent_ocean(computr->ocean);
  do
  {
    printf("Navigateur : Veuillez entrer la coordonnée de la zone a torpillee <A1 a %c%d> : ", 64+SIZE_O, SIZE_O);
    read_coordinates(&x, &y);
  }
  while(x<0 || x >= SIZE_O || y<0 || y>= SIZE_O);
  if (computr->ocean[y][x].destroy == FALSE)
    set_attack(computr,x,y);
  else printf("Cannonier : Vous aviez deja torpille cette case ! Faites plus attention a l'avenir ! \n");
}

void set_attack(profil* ordi, int xi, int yi)
{
  ordi->ocean[yi][xi].destroy = TRUE;
  int state = ordi->ocean[yi][xi].etat;
  if (state-- > 0)  // parce que state va de 1 a 5, tab de 0 a 4;
  {
    ordi->flotte[state].lenRemain--;
    if (ordi->flotte[state].lenRemain > 0)
      printf("Cannonier : Vous venez de touche le %s de l'adversaire.\n",ordi->flotte[state].nom);
    else  {
      printf("Cannonier : Vous venez de coule le %s de l'adversaire. Exellente strategie !\n",ordi->flotte[state].nom);
      ordi->boatRemain--;
    }
  }
  else  printf("Cannonier : Vous venez de torpille une case vide ! Reprenez vous commandant !\n");
}

void computer_round(profil* gamer)
{
  int xa,ya;
  getAttack_coord(gamer, &xa, &ya);
  setIA_attack(gamer, xa, ya);
}

void setIA_attack(profil* player, int x,int y)
{
  player->ocean[y][x].destroy = TRUE;
  printf("L'ordinateur vient de vous torpiller aux coordonnées : %c%d.\n",65+y,x+1);
  int state = player->ocean[y][x].etat;
  if(state < 1)
  {
    printf("Centre de controle : L'adversaire vient de torpille une case vide, il semble faible mon commandant !\n");
  }
  else
  { --state;// parce que state va de 1 a 5, tab de 0 a 4;
    player->flotte[state].lenRemain = player->flotte[state].lenRemain  - 1;
    int lenDestroy = player->flotte[state].len - player->flotte[state].lenRemain;
    if (lenDestroy == 1)  {printf("Centre de controle : Votre %s vient d'etre touche !\n", player->flotte[state].nom);}
    else
    {
      if (player->flotte[state].lenRemain > 0)
        printf("Centre de controle : Votre %s vient d'etre touche !\n", player->flotte[state].nom);
      else
      {
        printf("Centre de controle : Votre %s vient d'etre coule !\n", player->flotte[state].nom);
        player->boatRemain = player->boatRemain - 1;
      }
    }
  }
}

void getAttack_coord(profil* player, int*x, int*y)
{
  do
  {
    *x = my_rand(SIZE_O);
    *y = my_rand(SIZE_O);
  }while (player->ocean[*y][*x].destroy == TRUE);
}

void print_opponent_ocean(tocean oceanToPrint)
{
  int i,j;
  printf("\t");
  for(i=1; i<=SIZE_O; i++) printf("%d\t",i);
  printf("\n");
  for(i=0; i<SIZE_O ; i++)
  {
    printf("%c\t", (65+i));
    for (j=0; j<SIZE_O; j++)
    {
      if(oceanToPrint[i][j].destroy == FALSE)
        printf(".\t");
      else
        if(oceanToPrint[i][j].etat <= 0)  printf("°\t");
        else printf("*\t");
    }
    printf("\n");
  }
}

//----------------------DEPLOY------------------------------------

void deploy_boat(profil* gamer, profil* IA)
{
  printf("Mission 1 : Deploiement des bateaux.\n");
  printf("------------------------------------\n");
  player_dplymt(gamer);
  computer_dplymt(IA);
}
//______________________________________________________________________
void computer_dplymt(profil* computer)
{
  int i,x,y,direction;
  boolean directions[4];
  for (i=4; i>=0; i--)
  {
    getIA_coordinates(computer->ocean,computer->flotte[i].len, &x, &y, directions);
    direction = getIA_direction(directions);
    set_map(computer->ocean, x, y, direction, computer->flotte[i].len,(i+1));
  }
}

int getIA_direction(int dir[4])
{
  int direction;
  do
    direction = my_rand(4);
  while (dir[direction] == FALSE);
  return direction;
}
void getIA_coordinates(tocean iOcean, int length, int* x, int* y, boolean directions[4])
{
  boolean verif;
  do{
    *x = my_rand(SIZE_O);
    *y = my_rand(SIZE_O);
    verif = check_coordinates(iOcean,length,*x,*y,directions, FALSE);
    }
  while(verif == FALSE);
}

int my_rand (int max)
{
   return rand() / (double)RAND_MAX * (max);
}
//______________________________________________________________________
void player_dplymt(profil* playr)
{
  int i,x,y,direction;
  boolean directions[4];
  for(i = 0; i<5; i++)
  {
    mission1_1_msg(playr->flotte[i]);
    get_coordinates(playr->ocean, playr->flotte[i], &x,&y,directions);
    direction = get_direction(directions,playr->flotte[i].nom);
    set_map(playr->ocean, x, y, direction, playr->flotte[i].len, i+1);
    print_ocean(playr->ocean);
  }
}
//______________________________________________________________________
void set_map(tocean oceanToSet, int xi, int yi, int dir, int length, int boat_n)
{
  int xShift[] = {0,1,0,-1};
  int yShift[] = {-1,0,1,0};
  int xfShift[] = {0,1,1,1,0,-1,-1,-1};
  int yfShift[] = {-1,-1,0,1,1,1,0,-1};
  int i,j,x,y,xs,ys;
  for (i=0; i<length; i++)
  {
    x = xi + xShift[dir] * i;
    y = yi + yShift[dir] * i;
    oceanToSet[y][x].etat = boat_n;
    for(j=0; j<8; j++)
    {
      xs = x + xfShift[j];
      ys = y + yfShift[j];
      if (xs < SIZE_O && xs >= 0 && ys < SIZE_O && ys >= 0)
        if(oceanToSet[ys][xs].etat == 0)
          oceanToSet[ys][xs].etat = -1;
    }
  }
}

//______________________________________________________________________
int get_direction(boolean direction[4], char nom_[20])
{
  int choix;
  if (msg_direction(direction, nom_)) choix = read_cardinal(direction);
  else  for(choix=0; direction[choix] == FALSE; choix++);
  return choix;
}

boolean msg_direction(boolean dir[4], char name[20])
{
  boolean continuer = TRUE;
  char polaire[4][15] = {"au nord <N>","a l'est <E>","au sud <S>","a l'ouest <O>"};
  int dirRemain=4,i;
  for(i=0; i<4; i++)
    if(dir[i] == FALSE) --dirRemain;
  if(dirRemain > 1)
  {
    printf("Tacticien : Il y a %d directions disponibles : ",dirRemain);
    int cpt;
    for(i=0,cpt=0; i<4; i++)
      if(dir[i] == TRUE)
      {
        printf(" %s",polaire[i]);
        if(++cpt != dirRemain) printf(",");
      }
    printf(".\nCommandant, quel est votre choix ? ");
  }
  else
  {
    for (i = 0; dir[i]==FALSE; i++);
    printf("Tacticien : Le %s a ete place %s.\n",name,polaire[i]);
    continuer = FALSE;
  }
  return continuer;
}

int read_cardinal(boolean dir[4])
{
  char choix[8] = {'N','n','E','e','S','s','O','o'};
  boolean errChoix = TRUE;
  char choice;int i;
  while(errChoix)
  {
    choice = lireClavier();
    for (i = 1; i<=7 && errChoix;i=i+2 )
      if(dir[i/2]==TRUE && (choix[i-1]==choice || choix[i]==choice))
        errChoix = FALSE;
    if(errChoix) printf("Cette direction n'est pas disponible !\nQuelle est votre direction ? ");
  }
  return i/2-1;
}

int lireClavier(void)
{
  int car,c;
  car = c = getchar();
  while (c != '\n' && c != EOF)
    c = getchar();
  return car;
}

void get_coordinates(tocean pOcean, boat bateau, int* xa, int* ya, boolean direction[4])
{
  boolean verif = FALSE;
  while (!verif)
  {
    printf("Navigateur : Veuillez entrer la coordonnée de la proue du %s <A1 a %c%d> : ",bateau.nom, SIZE_O+64,SIZE_O);
    read_coordinates(xa,ya);
    verif = check_coordinates(pOcean,bateau.len,*xa,*ya,direction, TRUE);
  }
}

boolean check_coordinates(tocean oceanToCheck, int len, int x, int y, boolean dir[4], boolean msg)
{
  boolean check = FALSE;
  if(x <SIZE_O && x>=0 && y <SIZE_O && y>=0)
  {
    if(oceanToCheck[y][x].etat == 0)
    {
      int xShift[] = {0,1,0,-1};
      int yShift[] = {-1,0,1,0};
      dir[0] = y-(len-1) >= 0 ? TRUE : FALSE;
      dir[1] = x+ len <= SIZE_O ? TRUE : FALSE;
      dir[2] = y+ len <= SIZE_O ? TRUE : FALSE;
      dir[3] = x-(len-1) >= 0  ? TRUE : FALSE;
      int i,j, dirRemain;
      for(i=0, dirRemain=4; i<4; i++)
      {
        for(j=1; j<len && dir[i]; j++)
          if (oceanToCheck[y + yShift[i] * j]
              [x + xShift[i] * j].etat != 0) dir[i] = FALSE;
        if(dir[i] == FALSE) --dirRemain;
      }
      if (dirRemain > 0)
      {
        check = TRUE;
        if (msg) printf("Centre de control : Coordonnee bien reçue !\n");
      }
      else if (msg)   printf("Navigateur : Espace maritime trop etroit !\n");
    }
    else if (msg)   printf("Navigateur : Cette coordonnee indique une position deja occupe !\n");
  }
  else if(msg)      printf("Explorateur : Coordonnee en Terra incognita\n");
  return check;
}

void read_coordinates(int* x, int*y)
{
  char coord[3] = {'.','.','.'};
  scanf("%s",coord);
  lireClavier();
  *y = coord[0] - 'A';  //lignes
  *x = coord[1] - '1';  //colonnes
  if (coord[2] >= '0' && coord[2] <= '9') *x = (coord[1]-48) * 10 + (coord[2]-48)- 1;
}

void print_ocean(tocean oceanToPrint)
{
  int i,j;
  char caracter[5] = {'D','S','C','B','P'};
  printf("\t");
  for(i=1; i<=SIZE_O; i++) printf("%d\t",i);
  printf("\n");
  for(i=0; i<SIZE_O ; i++)  //ocean[ligne][colonne]
  {
    printf("%c\t", (65+i));
    for (j=0; j<SIZE_O; j++)
    {
      if(oceanToPrint[i][j].destroy == FALSE)
        if(oceanToPrint[i][j].etat <= 0)   printf(".\t");
        else printf("%c\t",caracter[oceanToPrint[i][j].etat - 1]);
      else
        if(oceanToPrint[i][j].etat <= 0)  printf("°\t");
        else printf("*\t");
    }
    printf("\n");
  }
}
void mission1_1_msg(boat bateau)
{
  printf("\nCaracteristiques du bateau : \n\n");
  printf("Nom : %s.\n",bateau.nom);
  printf("Longueur : %d cases.\n\n",bateau.len);
}

//----------------------INIT-----------------------------------
void init_game(profil* gamer, profil* ordi)
{
  gamer->boatRemain = 5;
  ordi->boatRemain = 5;
  init_ocean(gamer->ocean, ordi->ocean);
  init_boat(gamer->flotte, ordi->flotte);
}

void init_ocean(tocean pOcean, tocean cOcean)
{
  int i,j;
  for (i=0; i<SIZE_O; i++)
  {
    for (j=0; j<SIZE_O; j++)
    {
      pOcean[i][j].etat = 0;
      pOcean[i][j].destroy = FALSE;
      cOcean[i][j].etat = 0;
      cOcean[i][j].destroy = FALSE;
    }
  }
}

void init_boat(tflotte pFlotte, tflotte cFlotte)
{
  char boat_names[5][20] = {"destroyer","sous-marin","croiseur","cuirasse","porte-avion"};
  int boat_len[5] = {2,3,3,4,5};
  int i;
  for(i=0; i<5; i++)
  {
    strcpy(pFlotte[i].nom,boat_names[i]);
    pFlotte[i].len = boat_len[i];
    pFlotte[i].lenRemain = boat_len[i];
    strcpy(cFlotte[i].nom,boat_names[i]);
    cFlotte[i].len = boat_len[i];
    cFlotte[i].lenRemain = boat_len[i];
  }
}
