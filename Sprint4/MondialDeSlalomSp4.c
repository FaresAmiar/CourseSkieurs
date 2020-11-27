#pragma warning(disable : 4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define lgMot 30 // Taille maximale d’une chaine de caractères
#define maxSkieurs 50 // Nombre maximal de skieurs
#define minPortes 2 // Nombre minimal de portes
#define maxPortes 20 // Nombre maximal de portes

/*
* MondialDeSlalomSp4.c
* AMIAR Fares, YANG Jie-Jacques 106
* date de création
*/


/* structure du skieur
nom : nom du skieur
pays : pays du skieur
dossard : numero de dossard du skieur
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
/* une définition plus courte pour la structure */
typedef struct inscrits Inscrits;

struct mesure
{
	double temps;
	unsigned int numDossard;
	unsigned int numPorte;
};
/* une définition plus courte pour la structure */
typedef struct mesure Mesure;


struct course
{
	Mesure data[maxPortes*maxSkieurs];
	unsigned int nbPortes; // entre 2 et 20
	unsigned int nbTemps;
};
/* une définition plus courte pour la structure */
typedef struct course Course;

/* le type complexe */
struct skieurs
{
	Inscrits *insc;
};
/* une défition plus courte pour la structure */
typedef struct skieurs Skieurs;



void inscription_skieur(Inscrits* ins);
void affichage_inscrits(const Inscrits* ins);

void definition_course(Course* crs);
void enregistrement_temps(Course* crs);
void affichage_temps(const Course* crs);
void disqualification(Course* crs);
void affichage_classement(const Skieurs* sks, const Course* crs);

int main() {
	char mot[lgMot + 1]; // mot de commande à lire

	Inscrits *ins = malloc(sizeof *ins);
	Course *crs = malloc(sizeof *crs);
	Skieurs *skies = malloc(sizeof *skies);

	ins->nbInscrits = 0;
	crs->nbTemps = 0;

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
		else if (0 == strcmp(mot, "definir_course")) {
			definition_course(crs);


		}
		else if (0 == strcmp(mot, "enregistrer_temps")) {
			enregistrement_temps(crs);

		}
		else if (0 == strcmp(mot, "afficher_temps")) {
			affichage_temps(crs);

		}
		else if (0 == strcmp(mot, "disqualification")) {
			disqualification(crs);

		}
		else if (0 == strcmp(mot, "afficher_classement")) {
			skies->insc = ins;
			affichage_classement(skies, crs);

		}
		else if (0 == strcmp(mot, "exit")) {
			free(ins);
			free(crs);
			exit(0);

		}
		else {
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

void definition_course(Course* crs) {
	unsigned int nbPortes;

	scanf("%d", &nbPortes);

	if (nbPortes >= 2 && nbPortes <= 20) {
		crs->nbPortes = nbPortes;
	}
	else {
		printf("nombre de portes entre 2 et 20.\n");
	}

}
void enregistrement_temps(Course* crs) {
	double temps;
	unsigned int porte;
	unsigned int dossard;
	scanf("%lf %d %d", &temps, &porte, &dossard);

	Mesure mesure;
	mesure.numDossard = dossard;
	mesure.numPorte = porte;
	mesure.temps = temps;

	crs->data[crs->nbTemps] = mesure;

	crs->nbTemps++;

}
void affichage_temps(const Course* crs) {
	unsigned int dossard;
	scanf("%d", &dossard);

	for (unsigned int i = 0; i < crs->nbTemps; i++)
	{
		if (crs->data[i].numDossard == dossard) {
			if (crs->data[i].temps == -1)
			{
				printf("%d %d disqualification\n", crs->data[i].numPorte, crs->data[i].numDossard);
			}
			else
			{
				printf("%d %d %.2lf\n", crs->data[i].numPorte, crs->data[i].numDossard, crs->data[i].temps);
			}
		}
	}

}

void disqualification(Course* crs) {
	unsigned int porte;
	unsigned int dossard;
	scanf("%d %d", &porte, &dossard);


	crs->data[crs->nbTemps].numDossard = dossard;
	crs->data[crs->nbTemps].numPorte = porte;


	crs->data[crs->nbTemps].temps = -1;

	crs->nbTemps++;

}

void affichage_classement(const Skieurs* sks, const Course* crs) {
	int tDos[maxSkieurs];
	double tTps[maxSkieurs];
	unsigned int porte;
	
	scanf("%d", &porte);

	for (unsigned int i = 0; i < sks->insc->nbInscrits; ++i) {
		int indiceMesurePorte = 0;
		double tps = 0.0;

		tDos[i] = sks->insc->data[i].dossard;

		for (unsigned int j = 0; j < crs->nbTemps && indiceMesurePorte == 0; ++j) {
			
			if (tDos[i]== crs->data[j].numDossard)
			{

				if (crs->data[j].numPorte == porte) {
					tps = crs->data[j].temps - tps;
					indiceMesurePorte = j;

				}
				if (crs->data[j].numPorte == 0) {
						tps = crs->data[j].temps;

				}
			}
			else {

				if (j == crs->nbTemps - 1) {
					tps = 0.0;
				}
			}
			
		}

		tTps[i] = tps;

	}


	// tri par insertion

	for (unsigned int i = 1; i < sks->insc->nbInscrits; i++)
	{
		int vDos, j;
		double vTps;

		vDos = tDos[i];
		vTps = tTps[i];
		j = i;

		while (j > 0 && tTps [j - 1] > vTps)
		{
			tTps[j] = tTps[j - 1];
			tDos[j] = tDos[j - 1];
			j = j - 1;
		}

		tTps[j] = vTps;
		tDos[j] = vDos;

	}

	for (unsigned int i = 0; i < sks->insc->nbInscrits; ++i) {
		if (tTps[i] > 0.0) {
			for (unsigned int j = 0; j < sks->insc->nbInscrits; ++j) {
				if (sks->insc->data[j].dossard == tDos[i]) {
					printf("%d %d %s %s %.2lf\n", porte, tDos[i], sks->insc->data[j].nom, sks->insc->data[j].pays, tTps[i]);
				}


			}
		}
	
	}
}