#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
struct Magazin {
	int cod;
	char* denumire;
	int nrProduse;
	float* preturi;

};
//Functie de adaugare a unui obiect de tip Magazin in fisier
struct Magazin* adaugaMagazin(struct Magazin* vector, struct Magazin magazin, int* dimensiune) {
	struct Magazin* copie = (struct Magazin*)malloc(sizeof(struct Magazin) * ((*dimensiune) + 1));
	copie[(*dimensiune)] = magazin;
	for (int i = 0; i < (*dimensiune); i++) {
		copie[i] = vector[i];
	}
	if (vector) {
		free(vector);
	}
	(*dimensiune)++;
	return copie;

}
//Functie pt a citi obiectele din fisier si a le salva intr-un vector
struct Magazin* citireFisier(const char* numeFisier, int* nrMagazine) {
	struct Magazin* vectorMagazine;
	vectorMagazine = NULL;
	FILE* f = fopen(numeFisier, "r");
	
	if (f != NULL) {
		(*nrMagazine) = 0;
		char buffer[100];
		while (fgets(buffer, 99, f) != NULL) {
			struct Magazin magazin;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			magazin.cod = atoi(token);
			token = strtok(NULL, delimitator);
			magazin.denumire = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(magazin.denumire, token);
			token = strtok(NULL, delimitator);
			magazin.nrProduse = atoi(token);
			token = strtok(NULL, delimitator);
			magazin.preturi =(float*) malloc(sizeof(float) * magazin.nrProduse);
			for (int i = 0; i < magazin.nrProduse; i++) {
				
				magazin.preturi[i] = atof(token);
				token = strtok(NULL, delimitator);
			}
			vectorMagazine = adaugaMagazin(vectorMagazine, magazin, nrMagazine);
		}
		fclose(f);
	}
	return vectorMagazine;
	


}
void afisareMagazin(struct Magazin* magazin) {
	

		printf("Magazinul cu codul: %d cu numele: %s are %d produse\n ", magazin->cod, magazin->denumire, magazin->nrProduse);

		printf("Preturile produselor sunt:\n");
		for (int i = 0; i < magazin->nrProduse; i++) {
			printf("%5.2f", magazin->preturi[i]);

			printf("\n");
		

	}
		
		
}
void afisareVectorMagazine(struct Magazin* magazine, int dim) {
	printf("Afisare vector:\n");
	for (int i = 0; i < dim; i++) {
		afisareMagazin(&magazine[i]);
	}

}
void dezalocareVector(struct Magazin** magazine, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		free((*magazine)[i].denumire);
		free((*magazine)[i].preturi);
	}
	free(*magazine);
	(*magazine) = NULL;
	(*dim) = 0;
}
//Functie pentru copierea elementelor din vector intr-o matrice alocata dinamic, organizata pe linii in functie de cel mai mic pret al produselor
float** copiazaInMatrice(struct Magazin* vectorMagazine, int nrMagazine) {
	//Aloc memorie pentru matricea de preturi
	float** matriceMagazine = (float**)malloc(nrMagazine * sizeof(float*));
	//Initializez un vector de indici care vor tine evidenta ordinei magazinelor in functie de pret
	int* indici = (int*)malloc(nrMagazine * sizeof(int));
	for (int i = 0; i < nrMagazine; i++) {
		indici[i] = i;
	}
	//Sortez vectorul de indici in functie de preturi
	for (int i = 0; i < nrMagazine - 1; i++) {
		for (int j = i + 1; j < nrMagazine; j++) {
			if (vectorMagazine[indici[i]].preturi[0] > vectorMagazine[indici[j]].preturi[0]) {
				int temp = indici[i];
				indici[i] = indici[j];
				indici[j] = temp;

			}
		}
	}
	//Copiem preturile in matriceMagazine, in ordinea determinata de vectorul de indici
	for (int i = 0; i < nrMagazine; i++) {
		int indexMagazin = indici[i];
		matriceMagazine[i] = (float*)malloc((vectorMagazine[indexMagazin].nrProduse + 1) * sizeof(float));
		matriceMagazine[i][0] = vectorMagazine[indexMagazin].nrProduse;//Prima valoare din linie va fi numarul de preturi
		for (int j = 1; j <= vectorMagazine[indexMagazin].nrProduse; j++) {
			matriceMagazine[i][j] = vectorMagazine[indexMagazin].preturi[j - 1];

		}
	}
	//Eliberez memoria alocata pentru vectorul de indici
	free(indici);
	return matriceMagazine;
}
//Functie pt mutarea liniilor din matrice, astfel incat acestea sa fie sortate dupa numarul de elemente de pe linie
void sorteazaLiniiMatrice(float** matriceMagazine, int nrMagazine) {
	//Sortarea liniilor matricei in functie de numarul de elemente de pe linie
	for (int i = 0; i < nrMagazine - 1; i++) {
		for (int j = i + 1; j < nrMagazine; j++) {
			if (matriceMagazine[i][0] > matriceMagazine[j][0]) {
				//Schimbam liniile i si j
				float* temp = matriceMagazine[i];
				matriceMagazine[i] = matriceMagazine[j];
				matriceMagazine[j] = temp;
			}
		}
	}
}
	//Functie pentru afisarea elementelor dintr-o matrice
	void afisareMatrice(float** matriceMagazine, int nrMagazine) {
		for (int i = 0; i < nrMagazine; i++) {
			printf("Magazin %d (%d produse): ", i + 1, (int)matriceMagazine[i][0]);
			for (int j = 1; j <=(int) matriceMagazine[i][0]; j++) {
				printf(" %5.2f ", matriceMagazine[i][j]);
			}
			printf("\n");
		}
	}

void main() {
	int dimensiune = 10;
	struct Magazin* magazine = NULL;
	magazine = citireFisier("magazine.txt", &dimensiune);
	afisareVectorMagazine(magazine, dimensiune);
	//dezalocareVector(&magazine, &dimensiune);
	//Copiez magazinele intr-o matrice organizat dupa cel mai mic pret
	float** matriceMagazine = copiazaInMatrice(magazine, dimensiune);
	//Sortam liniile matricei in functie de numarul de elemente de pe linie(numarul de produse)
	sorteazaLiniiMatrice(matriceMagazine, dimensiune);
	//Afisam matricea rezultata
	printf("\nMatricea rezultata este:\n");
	afisareMatrice(matriceMagazine, dimensiune);
	//Eliberez memoria alocata
	for (int i = 0; i < dimensiune; i++) {
		free(magazine[i].denumire);
		free(magazine[i].preturi);
		free(matriceMagazine[i]);
	}
	free(magazine);
	free(matriceMagazine);

}