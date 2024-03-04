#include<stdio.h>
#include<malloc.h>
struct Magazin {
	int cod;
	char* denumire;
	int nrProduse;
	float* preturi;
};
//Functie pentru alocarea dinamica a unui magazin
struct Magazin* alocareMagazin(int cod, const char* denumire, int nrProduse, const float* preturi) {
	struct Magazin* magazin = (struct Magazin*)malloc(sizeof(struct Magazin));
	magazin->cod = cod;
	magazin->denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(magazin->denumire, denumire);
	magazin->nrProduse = nrProduse;
	magazin->preturi = (float*)malloc(nrProduse * sizeof(float));
	memcpy(magazin->preturi, preturi, nrProduse * sizeof(float));
	return magazin;


}
//Functie pentru elberarea memoriei alocate pentru un magazin
void elibereazaMemorie(const struct Magazin* magazin) {
	free(magazin->denumire);
	free(magazin->preturi);
	free(magazin);

}
//Functie care returneaza 1 daca magazinul are codul mai mic decat 50, altfel returneaza 0
int codMaiMicDecat50(const struct Magazin* magazin) {
	return magazin->cod < 50 ? 1 : 0;

}
//Functie care filtreaza un vector de magazine si returneaza un nou vector cu magazinele care au codul mai mic decat 50
struct Mgaazin** filtreazaMagazine(struct Magazin** magazine, int dimensiune, int* dimensiuneNoua) {
	struct Magazin** rezultat = (struct Magazin**)malloc(dimensiune * sizeof(struct Magazin*));
	*dimensiuneNoua = 0;
	for (int i = 0; i < dimensiune; i++) {
		if (codMaiMicDecat50(magazine[i]) == 1) {
			rezultat[*dimensiuneNoua] = magazine[i];
			(*dimensiuneNoua)++;
		}
	}
	return rezultat;
}
//Functie care muta magazinele cu codul ai mare sau egal cu 50 intr-un nou vector
struct Magazin** mutaMagazine(struct Magazin** magazine, int dimensiune, int* dimensiuneNoua) {
	struct Magazin** rezultat = (struct Magazin**)malloc(dimensiune * sizeof(struct Magazin*));
	*dimensiuneNoua = 0;
	for (int i = 0; i < dimensiune; i++) {
		if (!codMaiMicDecat50(magazine[i])) {
			rezultat[*dimensiuneNoua] = magazine[i];
			(*dimensiuneNoua)++;
		}
	}
	return rezultat;
}

//Functie care concateneaza doi vectori de magazine
struct Magazin** concateneazaMagazine(struct Magazin** magazine1, int dimensiune1, struct Magazin** magazine2, int dimensiune2, int* dimensiuneNoua) {
	struct Magazin** rezultat = (struct Magazin**)malloc((dimensiune1 + dimensiune2) * sizeof(struct Magazin*));
	*dimensiuneNoua = 0;
	for (int i = 0; i < dimensiune1; i++) {
		rezultat[*dimensiuneNoua] = magazine1[i];
		(*dimensiuneNoua)++;
	}
	for (int i = 0; i < dimensiune2; i++) {
		rezultat[*dimensiuneNoua] = magazine2[i];
		(*dimensiuneNoua)++;

	}
	return rezultat;
	
}

//Functie care afiseaza un vector de magazine
void afiseazaMagazine(struct Magazin** magazine, int dimensiune) {
	for (int i = 0; i < dimensiune; i++) {
		printf("Cod: %d, Denumire: %s, Nr. produse: %d, Preturi: ", magazine[i]->cod, magazine[i]->denumire, magazine[i]->nrProduse);
		for (int j = 0; j < magazine[i]->nrProduse; j++) {
			printf("%.2f", magazine[i]->preturi[j]);
		}
		printf("\n");
	}
}
void main() {
	//Creare unui vector de 5 obiecte de tip Magazin
	struct Magazin** magazine = (struct Magazin*)malloc(5 * sizeof(struct Magazin*));
	magazine[0] = alocareMagazin(10, "Magazin 1", 3, (float[]) { 11.2, 21.45, 38.0 });
	magazine[1] = alocareMagazin(20, "Magazin 2", 2, (float[]) { 19.3, 29.5 });
	magazine[2] = alocareMagazin(30, "Magazin 3", 5, (float[]) { 13.9, 24.4, 45.0,15.5,36.8 });
	magazine[3] = alocareMagazin(40, "Magazin 4", 3, (float[]) { 50.7,7.5,8.0 });
	magazine[4] = alocareMagazin(50, "Magazin 5", 3, (float[]) { 26.60,35.8,10, });
	int dimensiune = 5;
	//Filtreaza magazinele cu codul mai mic decat 50
	int dimensiuneFiltrata = 0;
	struct Magazin** magazineFiltrate = filtreazaMagazine(magazine, dimensiune, &dimensiuneFiltrata);
	printf("Magazinele cu codul mai mic decat 50:\n");
	afiseazaMagazine(magazineFiltrate, dimensiuneFiltrata);
	printf("\n");
	//Mutarea magazinelor cu codul mai mare sau egal cu 50 intr-un alt vector
	int dimensiuneMutare = 0;
	struct Magazin** magazineMutate = mutaMagazine(magazine, dimensiune, &dimensiuneMutare);
	printf("Magazinele cu codul mai mare sau egal cu 50:\n");
	afiseazaMagazine(magazineMutate, dimensiuneMutare);
	printf("\n");
	//Concatenarea a doi vectori de magazine
	int dimensiuneConcatenare = 0;
	struct Magazin** magazineConcatenate = concateneazaMagazine(magazineFiltrate, dimensiuneFiltrata, magazineMutate, dimensiuneMutare, &dimensiuneConcatenare);
	printf("Magazinele concatenate:\n");
	afiseazaMagazine(magazineConcatenate, dimensiuneConcatenare);
	printf("\n");
	//Eliberarea memoriei alocate
	for (int i = 0; i < dimensiune; i++) {
		elibereazaMemorie(magazine[i]);

	}
	free(magazine);
	free(magazineFiltrate);
	free(magazineMutate);
	free(magazineConcatenate);

}
