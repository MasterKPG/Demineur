#include <stdlib.h>  // rand
#include <stdio.h>   // printf
#include "demineur.h"
#include <time.h>
#include <unistd.h>


void initialisation(int * t , int grille );
void Pmines (int * t, int mines,int grille);
int regarder(int * a, int i,int b);
void calcul (int * t,int grille);
void placer (int * g , int c);
void retirer(int * g , int c );
void afficherf (int * t,int * g, int grille);
void explo  (int * t,int * g, int n);
int gagner(int * t,int * g,int grille, int mines);
int IA (int * t,int * g,int grille);
int score(int * t, int grille);
int score_temps(time_t debut, time_t fin);



	

int main (){

	time_t debut, fin;
    time(&debut); // commencer le chrono

	// initialisation des variables
	srand(time( NULL ) );
	int grille = 10;
	int mines = 20;
	int t[grille*grille];
	int g[grille*grille];
	clock_t debut = clock();
	//initialisation du jeux 
	initialisation(t,grille);
	initialisation(g,grille);
	Pmines(t,mines,grille);
	calcul(t,grille);
	afficherf(t,g,grille);
	int joue=0;
	while (joue==0){
		int reponse=0;
		int c=-1;
		int gagne=0;
		printf("Que faire :\n 1. Révéler une case. \n 2. Placer un drapeau. \n 3. Retirer un drapeau. \n 4. IA? \n");
		scanf("%d",&reponse);
		if (reponse==4)c = IA(t,g,grille);
		else {
		printf("case ?");
		scanf("%d",&c);
		}
		switch (reponse){
		case 1 : explo(t,g,c);if (t[c]==-1)joue=1;break;
		case 2 : placer(g,c);break;
		case 3 : retirer(g,c);break;
		}
		afficherf(t,g,grille);
		gagne = gagner(t,g,grille,mines);
		if (gagne==1)joue=2;

		
	}
	switch (joue){
		case 1:printf("\nperdu\n");break;
		case 2:printf("\ngagné");break;
	}

	time(&fin); // arreter le chrono
	int score_joueur = score(t,grille) + score_temps(debut, fin);
	printf("Score : %d\n",score_joueur);

printf("\n");
return 0;
}