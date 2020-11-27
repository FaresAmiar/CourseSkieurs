/*
* MondialDeSlalomSp5.c
* AMIAR Fares, YANG Jie-Jacques 106
* 14/10/2018
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#pragma warning(disable : 4996)

#define lgMot 30 // Taille maximale d’une chaine de caractères
#define maxSkieurs 50 // Nombre maximal de skieurs
#define minPortes 2 // Nombre minimal de portes
#define maxPortes 20 // Nombre maximal de portes



/* structure du skieur
 *nom : nom du skieur
 *pays : pays du skieur
 *dossard : numero de dossard du skieur
 */
struct skieur
{
	char nom[lgMot + 1]; // Tableau des noms de taille lgMot +1 (31) 
	char pays[lgMot + 1]; // Tableau des pays de taille lgMot +1 (31)
	unsigned int dossard; // Variable dossard pour stocker les dossards
};
typedef struct skieur Skieur;

// Type des inscrits 
struct inscrits
{
	Skieur data[maxSkieurs]; // Tableau de data de taille maxSkieurs (50)
	unsigned int nbInscrits; // Variable nombre d'inscrits pour stocker le 
						 // nombre d'inscrits
};
typedef struct inscrits Inscrits;

// Type de mesure des skieurs à une porte donnée
struct mesure
{
	double temps; // Variable temps de type double
	unsigned int numDossard; // Variable des numéro de Dossard
	unsigned int numPorte; // Variable du numéro de porte pour stocker le
						   // numéro de porte 
};
typedef struct mesure Mesure;

// Type de course 
struct course
{
	Inscrits *insc; // Pointeur insc de la structure inscrits

	/*Tableau de data depuis la structure mesure
	 *Mesure de taille maxPortes+1 * maxSkieurs
	 *pour stocker le temps, numDossard et numPorte
	 */

	Mesure data[(maxPortes + 1)*maxSkieurs];
	unsigned int nbPortes; // Variable du nombre de porte entre 2 et 20
	unsigned int nbTemps; // Variable du nombre de Temps pour stocker le nombre 
						  // de temps des skieurs
};
typedef struct course Course;

// Type des skieurs
struct skieurs
{
	Inscrits *insc; // Pointeur insc de la structure inscrits
	unsigned int porte; // Variable de porte
};
typedef struct skieurs Skieurs;



void inscription_skieur(Inscrits* ins); // void inscription_skieur(Inscrits*);

void affichage_inscrits(const Inscrits* ins); // void afficahge_inscrits(const Inscrits*);

void definition_course(Course* crs); // void definition_course(Course*);

void enregistrement_temps(Course* crs); // void enregistrement_temps(Course*);

void detection_fin_course(const Course* crs); // void detection_fin_course(const Course*);

void affichage_temps(const Course* crs); // void affichage_temps(const Course*);

void disqualification(Course* crs); // void disqualification(Course*);

void affichage_classement(const Skieurs* sks, const Course* crs);
		// void afficahge_classement(const Skieurs*, const Course*);

int main() {
	char mot[lgMot + 1]; // mot de commande à lire

	Inscrits *ins = malloc(sizeof *ins);
	Course *crs = malloc(sizeof *crs);
	Skieurs *skies = malloc(sizeof *skies);

	ins->nbInscrits = 0;//init des nombres inscrits
	crs->nbTemps = 0;//init du nombre de temps enregistrés
	crs->insc = ins; //pointeur des inscrits

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
		else if (0 == strcmp(mot, "afficher_inscrits")
			|| 0 == strcmp(mot, "afficher_skieurs")) {

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
			scanf("%d", &skies->porte);
			affichage_classement(skies, crs);

		}
		else if (0 == strcmp(mot, "exit")) {
			if (ins != NULL) free(ins);
			if (crs != NULL) free(crs);
			if (skies != NULL) free(skies);
			exit(0);

		}
		else {
			printf("%s commande non connue\n", mot);
		}


	} while (1);
	system("pause");
	return 0;
}

/*
 *Description : Permet d'ajouter un nouveau skieur dans la liste des inscriptions
 *à partir de son nom, pays
 *[in-out] Pointeur ins de la strucutre Inscrits
 */
void inscription_skieur(Inscrits* ins) {
	char nom[lgMot + 1];
	char pays[lgMot + 1];
	scanf("%s %s", nom, pays);

	// Ne pas inscrire plus que le nombre maximum de skieurs
	if (ins->nbInscrits < maxSkieurs) {
		ins->nbInscrits++;
		Skieur skie;
		strcpy(skie.nom, nom);
		strcpy(skie.pays, pays);
		skie.dossard = 100 + ins->nbInscrits;
		// Pointeur ins attribue le tableau de nbInscrits -1 dans la variable skie
		ins->data[ins->nbInscrits - 1] = skie;
		printf("inscription dossard %d\n", skie.dossard);
	}
	else {
		printf("il ne faut pas depasser 50 inscrits.\n");

	}

}

/*
 *Affichage de la liste des skieurs inscrits
 *[in-out] (Constante) Pointeur ins de la strucutre Inscrits
 */
void affichage_inscrits(const Inscrits* ins) {
	for (unsigned int i = 0; i < ins->nbInscrits; i++)
	{
		printf("%s %s %d\n",
			ins->data[i].nom, ins->data[i].pays, ins->data[i].dossard);
	}
}

/*Initialiser la course avec le nombre de portes
 *[in-out] Pointeur crs de la strucutre Course
 */
void definition_course(Course* crs) {
	unsigned int nbPortes;

	scanf("%d", &nbPortes);

	assert(nbPortes < maxPortes + 1 && nbPortes > minPortes - 1);
	//vérifier que les bornes des nombres de portes sont respectees
	if (nbPortes >= minPortes && nbPortes <= maxPortes) {
		crs->nbPortes = nbPortes;
	}
	else {
		printf("nombre de portes entre 2 et 20.\n");
	}

}

/*Enregistre le temps d'un skieur à une porte specifique
 *[in-out] Pointeur crs de la strucutre Course
 */
void enregistrement_temps(Course* crs) {
	double temps;
	unsigned int porte;
	unsigned int dossard;
	scanf("%lf %d %d", &temps, &porte, &dossard);

	Mesure mesure;
	mesure.numDossard = dossard;
	mesure.numPorte = porte;
	mesure.temps = temps;
	// Pointeur crs attribue le tableau de nbTemps dans la variable mesure
	crs->data[crs->nbTemps] = mesure;

	crs->nbTemps++;

	detection_fin_course(crs);
}

/*Detecter que la course est terminee car disqualification
 *et/ou derniere porte atteinte pour tous les skieurs
 *[in-out] (Constante) Pointeur crs de la strucutre Course
 */
void detection_fin_course(const Course* crs) {
	int nb_fin_course = 0; // compter le nombre de skieurs 
				//ayant termine la course avec les disqualifies

	for (unsigned int i = 0; i < crs->insc->nbInscrits; ++i) {
		for (unsigned int j = 0; j < crs->nbTemps; ++j) {

			if (crs->data[j].numDossard == crs->insc->data[i].dossard) {
				if (crs->data[j].numPorte == crs->nbPortes || crs->data[j].temps == -1) {
					nb_fin_course++;
				}
			}

		}
	}

	// verifier que la course est finie et donc tout le monde est compte
	if (nb_fin_course == crs->insc->nbInscrits) {
		printf("detection_fin_course\n");

		Skieurs *sks = malloc(sizeof *sks);
		sks->porte = crs->nbPortes;
		sks->insc = crs->insc;
		affichage_classement(sks, crs);
		if (sks != NULL) free(sks);
		exit(0);
	}
}


/*Afficher le temps d'un skieur depuis son dossard à une porte
 *[in-out] (Constante) Pointeur crs de la strucutre Course
 */
void affichage_temps(const Course* crs) {
	unsigned int dossard;
	scanf("%d", &dossard);

	for (unsigned int i = 0; i < crs->nbTemps; i++)
	{
		if (crs->data[i].numDossard == dossard) {
			// skieur est disqualifie
			if (crs->data[i].temps == -1)
			{
				printf("%d %d disqualification\n",
					crs->data[i].numPorte, crs->data[i].numDossard);
			}
			else
			{
				printf("%d %d %.2lf\n",
					crs->data[i].numPorte,
					crs->data[i].numDossard, crs->data[i].temps);
			}
		}
	}

}


/*disqualifier un skieur à partir de son dossard à la porte donnee
 *[in-out] Pointeur crs de la strucutre Course
 */
void disqualification(Course* crs) {
	unsigned int porte;
	unsigned int dossard;
	scanf("%d %d", &porte, &dossard);


	crs->data[crs->nbTemps].numDossard = dossard;
	crs->data[crs->nbTemps].numPorte = porte;


	crs->data[crs->nbTemps].temps = -1;

	crs->nbTemps++;
}

/*Afficher le classement des skieurs a une porte
 *[in-out] (Constante) Pointeur sks de la strucutre Skieurs
 *[in-out] Pointeur crs de la strucutre Course
 */
void affichage_classement(const Skieurs* sks, const Course* crs) {
	int tDos[maxSkieurs];
	double tTps[maxSkieurs];
	double tTpsDisq[maxSkieurs];
	int tDosDisq[maxSkieurs], tPorteDisq[maxSkieurs], idisqualifie = 0;

	unsigned int porte = sks->porte;

	// remplir les tableaux de dossard et de temps à partir des mesures de temps de la course
	for (unsigned int i = 0; i < sks->insc->nbInscrits; ++i) {
		int indiceMesurePorte = 0;
		double tps = 0.0;
		// pour chaque skieur inscrit
		tDos[i] = sks->insc->data[i].dossard;

		//Parcourir les mesures de temps
		for (unsigned int j = 0; j < crs->nbTemps && indiceMesurePorte == 0; ++j) {

			if (tDos[i] == crs->data[j].numDossard)
			{
				// la mesure de temps a la porte demandee
				if (crs->data[j].numPorte == porte) {
					tps = crs->data[j].temps - tps;
					indiceMesurePorte = j;

				}
				// mesure de temps au point de depart de la course
				if (crs->data[j].numPorte == 0) {
					tps = crs->data[j].temps;

				}
				// si skieur disqualifie durant sa course
				if (crs->data[j].temps == -1) {
					tDosDisq[idisqualifie] = crs->data[j].numDossard;
					tPorteDisq[idisqualifie] = crs->data[j].numPorte;
					idisqualifie++;
				}

			}
			else {
				//pas encore de temps enregistre durant sa course
				if (j == crs->nbTemps - 1) {
					tps = 0.0;
				}
			}

		}

		tTps[i] = tps;
	}

	// tri par insertion
	int vDos, vPorte, j;
	double vTps;

	for (unsigned int i = 1; i < sks->insc->nbInscrits; i++)
	{

		vDos = tDos[i];
		vTps = tTps[i];
		j = i;

		while (j > 0 && tTps[j - 1] > vTps)
		{
			tTps[j] = tTps[j - 1];
			tDos[j] = tDos[j - 1];
			j = j - 1;
		}

		tTps[j] = vTps;
		tDos[j] = vDos;

	}

	//Trier les disqualifies
	for (int i = 1; i < idisqualifie; i++)
	{

		vDos = tDosDisq[i];
		vPorte = tPorteDisq[i];
		
		j = i;

		/*Trier sur les portes*/
		while (j > 0 && tPorteDisq[j - 1] > vPorte)
		{
			tPorteDisq[j] = tPorteDisq[j - 1];
			tDosDisq[j] = tDosDisq[j - 1];
			j = j - 1;

		}

		
		tPorteDisq[j] = vPorte;
		tTpsDisq[j] = vTps;

		/*Trier les disqualifies sur une même porte par nom*/
		while (j > 0 && tPorteDisq[j - 1] == vPorte && tTpsDisq[j - 1] > vTps)
		{
			tPorteDisq[j] = tPorteDisq[j - 1];
			tTpsDisq[j] = tTpsDisq[j - 1];
			j = j - 1;
		}

		tPorteDisq[j] = vPorte;
		tTpsDisq[j] = vTps;
	}


	//affichage du classement des skieurs à une porte demandée
	for (unsigned int i = 0; i < sks->insc->nbInscrits; ++i) {

		if (tTps[i] > 0.0) {
			printf("%d %d %s %s %.2lf\n", porte, tDos[i],
				sks->insc->data[tDos[i] - 101].nom,
				sks->insc->data[tDos[i] - 101].pays, tTps[i]);
		}

	}

	//liste des disqualifiés quand nous sommes à la dernière porte
	if (porte == crs->nbPortes) {
		while (idisqualifie > 0) {
			printf("disqualifie %d %s %s\n",
				tDosDisq[idisqualifie - 1],
				sks->insc->data[tDosDisq[idisqualifie - 1] - 101].nom, 
				sks->insc->data[tDosDisq[idisqualifie - 1] - 101].pays);
			idisqualifie--;
		}
	}
}