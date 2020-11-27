#pragma warning(disable : 4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define lgMot 30 // Taille maximale d’une chaine de caractères
#define maxSkieurs 50 // Nombre maximal de skieurs

/*
* MondialDeSlalomSp1.c
* AMIAR Fares, YANG Jie-Jacques 106
* date de création
*/


/* le type complexe */
struct skieur
{
	char nom[lgMot + 1];
	char pays[lgMot + 1];
	unsigned int dossard;
};
/* une défition plus courte pour la structure */
typedef struct skieur Skieur;

/*
typedef struct {
	Skieur data[maxSkieurs];
	unsigned int nbInscrits;
} Inscrits;*/

struct inscrits
{
	Skieur data[maxSkieurs];
	unsigned int nbInscrits;
};
/* une défition plus courte pour la structure */
typedef struct inscrits Inscrits;


void inscription_skieur(Inscrits* ins);
void affichage_inscrits(const Inscrits* ins);

int main() {
	char mot[lgMot + 1]; // mot de commande à lire

	Inscrits *ins = malloc(sizeof *ins);
	ins->nbInscrits = 0;

	do {
		// Lecture de la commande (mot)
		scanf("%s", mot);
		// si commande est "inscrire_skieur "
		// appeler la fonction inscription_skieur
		// si la commande est "afficher_inscrits"
		// appeler la fonction affichage_inscrits
		// …
		// si la commande est "exit"
		// sortir du programme par exit(0);)

		if (0 == strcmp(mot, "inscrire_skieur")) {
			inscription_skieur(ins);

		}
		else if (0 == strcmp(mot, "afficher_inscrits") || 0 == strcmp(mot, "afficher_skieurs")) {

			affichage_inscrits(ins);

		}
		else if (0 == strcmp(mot, "exit")) {
			free(ins);
			exit(0);

		}
		else
		{
			printf("%s commande non connue \n", mot);
		}


	} while (1);
	system("pause");
	return 0;
}

/**/
void inscription_skieur(Inscrits* ins) {
	char nom[lgMot + 1];
	char pays[lgMot + 1];
	scanf("%s %s", nom, pays);

	if (ins->nbInscrits < 50) {
		ins->nbInscrits++;
		Skieur skie;
		strcpy(skie.nom, nom);
		strcpy(skie.pays, pays);
		skie.dossard = 100 + ins->nbInscrits;
		ins->data[ins->nbInscrits - 1] = skie;
		printf("inscription dossard %d\n", skie.dossard);
	}
	else {
		printf("il ne faut pas depasser 50 inscrits.\n");

	}
	
}

/**/
void affichage_inscrits(const Inscrits* ins) {
	for (unsigned int i = 0; i < ins->nbInscrits; i++)
	{
		printf("%s %s %d\n", ins->data[i].nom, ins->data[i].pays, ins->data[i].dossard);
	}
}