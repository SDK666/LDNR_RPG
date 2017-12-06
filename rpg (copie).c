#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
/*
 * author:	Lethael
 * date:	171204
 * 
 * base de jeu type RPG simplifié
 */

struct Personnages //Héro + mobs
{
	char nom[30];
	int vie;
	int attaque;
	int defense;	
};

void InitPersonnages(struct Personnages *perso); 
void InfligerDegats(struct Personnages attaquant, struct Personnages *defenseur);

main()
{
	srand(time(NULL)); //Fonction rnd à n'appeler qu'une seule fois
	struct Personnages hero;
	struct Personnages monstre;
	
	char choix = 'z';
	
	InitPersonnages(&hero); // A modifier pour mettre en dur juste pour le héro
	InitPersonnages(&monstre);
	
	
	//Boucle combat à inclure dans fonc Combat
	do
	{
		choix = 'z';
		printf("C'est votre tour d'attaquer, que voulez-vous faire?\n[A]ttaquer\n[D]efendre\nVotre choix? : ");
		scanf("%c", &choix);
		getchar();
		printf("Vous avez entre %c\n", choix);
		
		if(choix != 'a')
				printf("Mauvais choix \n");
		
		if (choix == 'a')
			InfligerDegats(hero, &monstre);
		
		printf("%d vie monstre\n", monstre.vie);
	}while(hero.vie >= 0 && monstre.vie >= 0);
}

void InitPersonnages(struct Personnages *perso)
{
	printf("Veuillez saisir le nom du hero : \n");
	scanf("%s", perso->nom);
	getchar();
	perso->vie = 100;
	perso->attaque = (rand() % (10 - 1 + 1)) + 1; //Entre 10 et 1
	perso->defense = (rand() % (7 - 1 + 1)) + 1;
}

void InfligerDegats(struct Personnages attaquant, struct Personnages *defenseur)
{
	int deg;
	deg = (attaquant.attaque + (rand() % (7 - 1 + 1)) + 1) - defenseur->defense;
	printf("%d degats !\n", deg);
	defenseur->vie -= deg;
}	
