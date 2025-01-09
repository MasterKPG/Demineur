#include <stdlib.h>  // rand
#include <stdio.h>   // printf
#include "demineur.h"
#include <time.h>








void initialisation(int * t , int grille ){
	int * i;
	for(i=t;i<=t+grille*grille;i++){
		*i = 0;
	} 
}

void Pmines (int * t, int mines,int grille){
	int m;
	int i;
	t[1]=-1;
	for (i=0;i<mines;i++){
		m = rand()%(grille*grille);
		if (t[m]!=-1){
		t[m]=-1;
		}
		else i--;
	}
}	

void calcul (int * t,int grille){
	int i;
	for(i=0;i<grille*grille;i++){
		if (t[i] == -1 );
		else {	
			if ( i%10 != 0 && i>9 && t[i-11]==-1 )t[i]=t[i]+1;	// en haut à gauche
			if ( i>10 && t[i-10]==-1 )t[i]=t[i]+1;			// en haut 
			if ( i%10 != 9 && i>9 && t[i-9]==-1 )t[i]=t[i]+1;	// en haut à droite
			if ( i%10 != 0 && t[i-1]==-1 )t[i]=t[i]+1;		// à gauche 
			if ( i%10 != 9  && t[i+1]==-1 )t[i]=t[i]+1;		// à droite
			if ( i%10 != 0 && i<90 && t[i+9]==-1 )t[i]=t[i]+1;	// en bas à gauche 
			if ( i<90 && t[i+10]==-1 )t[i]=t[i]+1;			// en bas
			if ( i%10 != 9 && i<90 && t[i+11]==-1 )t[i]=t[i]+1;	// en bas à droite
		}
		printf("%d\n",i);
	}
}



void placer (int * g , int c){
	if (g[c]==0)g[c]=2;
}


void retirer(int * g , int c ){
	if (g[c]==2)g[c]=0;
	else printf("Pas de drapeau en casse %d \n",c);
} 

void afficher (int * t, int grille){
	int * i;
	printf("\n");
	int a = 0;
	for(i=t;i<t+grille*grille;i++){
		switch (*i){
		case -1:printf(" M ");break;
		case -2:printf(" D ");break;
		case -3:printf("   ");break;
		case 0:printf(" 0 ");break;
		default : printf(" %d ",*i);break;
		}
		a = a+1;
		if (a%grille==0)printf("\n\n");
	}

}

void afficherf (int * t,int * g, int grille){
	int i;
	printf("\n");
	int a = 0;
	for(i=0;i<grille*grille;i++){
		switch (g[i]){
		case 0 : printf(" ▓ ");break;
		case 1 :
			switch (t[i]){
			case -1:printf(" M ");break;
			default : printf(" %d ",t[i]);break;
			}
			break;
		case 2 :printf(" D ");break;
		}
		a = a+1;
		if (a%grille==0)printf("\n\n");
		
	}
}

void explo  (int * t,int * g, int n){
	printf("explo case ; %d g : %d t : %d\n",n,g[n],t[n]);
	g[n]=1;
	if (t[n]==0){
		if ( n%10 != 0 && n>9 && t[n-11]!=-1 && g[n-11]==0)explo(t,g,n-11);	// en haut à gauche
		if ( n>10 && t[n-10]!=-1 && g[n-10]==0)explo(t,g,n-10);			// en haut 
		if ( n%10 != 9 && n>9 && t[n-9]!=-1 && g[n-9]==0)explo(t,g,n-9);	// en haut à droite
		if ( n%10 != 0 && t[n-1]!=-1 && g[n-1]==0)explo(t,g,n-1);		// à gauche 
		if ( n%10 != 9 && t[n+1]!=-1 && g[n+1]==0)explo(t,g,n+1);		// à droite
		if ( n%10 != 0 && n<90 && t[n+9]!=-1 && g[n+9]==0)explo(t,g,n+9);	// en bas à gauche 
		if ( n<90 && t[n+10]!=-1 && g[n+10]==0)explo(t,g,n+10);			// en bas
		if ( n%10 != 9 && n<90 && t[n+11]!=-1 && g[n+11]==0)explo(t,g,n+11);	// en bas à droite
	}
} 

int gagner(int * t,int * g,int grille, int mines){
	int i;
	int oui=1;
	for(i=0;i<grille*grille;i++){
		if (t[i]!=-1 && g[i]!=1)oui=0;
	}
	return oui ;
}
int main (){
	srand(time( NULL ) );
	int grille = 10;
	int mines = 10;
	int t[grille*grille];
	int g[grille*grille];
	initialisation(t,grille);
	initialisation(g,grille);
	Pmines(t,mines,grille);
	calcul(t,grille);
	afficher(t,grille);
	afficher(g,grille);
	afficherf(t,g,grille);
	int joue=0;
	while (joue==0){
		int reponse=0;
		int c=-1;
		int gagne=0;
		printf("Que faire :\n 1. Révéler une case. \n 2. Placer un drapeau. \n 3. Retirer un drapeau. \n");
		scanf("%d",&reponse);
		printf("case ?");
		scanf("%d",&c);
		switch (reponse){
		case 1 : explo(t,g,c);
		if (t[c]==-1)joue=1;
		break;
		case 2 : placer(g,c);break;
		case 3 : retirer(g,c);break;
		case 4 : joue = 3;break;
		}
		afficherf(t,g,grille);
		gagne = gagner(t,g,grille,mines);
		if (gagne==1)joue=2;
	}
	switch (joue){
		case 1:printf("\nperdu\n");break;
		case 2:printf("\ngagné\n");break;
	}
	
void IA (int * t,int * g,int grille){
	int i;
	int trouve=0;
	for (i=0;i<grille*grille;i++){
		if (g[i]==1 && t[i]>0){
			int compteur=0;
			if ( i%10 != 0 && i>9 && g[i-11]==0 )compteur++;	// en haut à gauche
			if ( i>10 && g[i-10]==0 )compteur++;			// en haut 
			if ( i%10 != 9 && i>9 && g[i-9]==0 )compteur++;	// en haut à droite
			if ( i%10 != 0 && g[i-1]==0 )compteur++;		// à gauche 
			if ( i%10 != 9  && g[i+1]==0 )compteur++;		// à droite
			if ( i%10 != 0 && i<90 && g[i+9]==0 )compteur++;	// en bas à gauche 
			if ( i<90 && g[i+10]==0 )compteur++;			// en bas
			if ( i%10 != 9 && i<90 && g[i+11]==0 )compteur++;	// en bas à droite
		}	
	}	
}	

printf("\n");
return 0;
}


//int dialogue (){return 0;}
//int score(){return 0;}

