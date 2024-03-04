#include<stdio.h>
#include<malloc.h>
#include<string.h>
struct Magazin {
	int cod;
	char* denumire;
	int nrProduse;
	float* preturi;
};
//Functie de citire a unui magazin de la tastatura
struct Magazin citesteMagazin() {
	struct Magazin magazin;
	printf("Introduceti codul magazinului: ");
	scanf_s("%d", &magazin.cod);
	printf("Introduceti denumirea magazinului: ");
	char den[100];
	scanf_s("%s", den,100);
	magazin.denumire = (char*)malloc(strlen(den) + 1);
	strcpy(magazin.denumire, den);
	printf("Introduceti numarul de produse: ");
	scanf_s("%d", &magazin.nrProduse);
	magazin.preturi = (float*)malloc(magazin.nrProduse * sizeof(float));
	printf("Introduceti preturile produselor:\n");
	for (int i = 0; i < magazin.nrProduse; i++) {
		printf("Pretul produsului %d: ", i + 1);
		scanf_s("%f", &magazin.preturi[i]);
	}
	return magazin;
}
//Functie care calculeaza pretul minim din magazin.
float calculeazaPretMinim(struct Magazin magazin) {
	float pretMinim = 999;
	for (int i = 0; i < magazin.nrProduse; i++) {
		if (magazin.preturi[i] < pretMinim) {
			pretMinim = magazin.preturi[i];
		}
	}
	return pretMinim;
}
//Functie care modifica denumirea unui magazin
void modificaDenumire(struct Magazin* magazin, char* nouaDenumire) {
	free(magazin->denumire);
	magazin->denumire = (char*)malloc(strlen(nouaDenumire) + 1);
	strcpy(magazin->denumire, nouaDenumire);
}
//Functia pentru afisarea unui magazin
void afiseazaMagazin(struct Magazin magazin) {
	printf("Cod: %d\n", magazin.cod);
	printf("Denumire: %s\n", magazin.denumire);
	printf("Numar de produse: %d\n", magazin.nrProduse);
	printf("Preturi produse:\n");
	for (int i = 0; i < magazin.nrProduse; i++) {
		printf("Produsul %d are pretul: %.2f\n", i + 1, magazin.preturi[i]);
	}

}
void main() {
	//Citirea unui magazin de la tastatura
	struct Magazin magazin = citesteMagazin();
	//Calculeaza pretul minim
	float pretMinim = calculeazaPretMinim(magazin);
	printf("Pretul minim din magazin: %.2f\n", pretMinim);
	//Modifica denumirea magazinului
	modificaDenumire(&magazin, "Mega Image");
	//Afisare magazin
	printf("Magazin modificat:\n");
	afiseazaMagazin(magazin);
	//Eliberare memorie alocata dinamic
	free(magazin.denumire);
	free(magazin.preturi);


}
