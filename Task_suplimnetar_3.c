#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structura pentru un magazin
struct Magazin {
    int cod;
    char* denumire;
    int nrProduse;
    float* preturi;
};

// Functie pentru eliberarea memoriei alocate pentru un magazin
void elibereazaMagazin(struct Magazin* magazin) {
    free(magazin->denumire);
    free(magazin->preturi);
}

// Functie care citește un obiect de tip Magazin dintr-un fișier și îl returnează
struct Magazin* citesteMagazin(FILE* fisier) {
    struct Magazin* magazin = (struct Magazin*)malloc(sizeof(struct Magazin));
    if (!magazin) {
       printf("Eroare la alocarea memoriei pentru magazin");
        
    }

    char denumire[100]; // Buffer pentru citirea denumirii
    if (fscanf(fisier, "%d,%99[^,],%d", &magazin->cod, denumire, &magazin->nrProduse) != 3) {
        
        free(magazin);
        return NULL;
    }

    magazin->denumire = strdup(denumire);
    if (!magazin->denumire) {
        printf("Eroare la alocarea memoriei pentru denumirea magazinului");
       
    }

    magazin->preturi = (float*)malloc(magazin->nrProduse * sizeof(float));
    if (!magazin->preturi) {
       printf("Eroare la alocarea memoriei pentru preturi");
        
    }

    for (int i = 0; i < magazin->nrProduse; i++) {
        if (fscanf(fisier, ",%f", &magazin->preturi[i]) != 1) {
            elibereazaMagazin(magazin);
            return NULL;
        }
    }

    return magazin;
}

// Functie care salvează un obiect de tip Magazin într-un fișier
void salveazaMagazin(FILE* fisier, const struct Magazin* magazin) {
    fprintf(fisier, "%d,%s,%d", magazin->cod, magazin->denumire, magazin->nrProduse);
    for (int i = 0; i < magazin->nrProduse; i++) {
        fprintf(fisier, ",%.2f", magazin->preturi[i]);
    }
    fprintf(fisier, "\n");
}

// Functie care citește un vector de obiecte de tip Magazin dintr-un fișier și îl returnează
struct Magazin** citesteVectorMagazine(const char* numeFisier, int* dimensiune) {
    FILE* fisier = fopen(numeFisier, "r");
    if (!fisier) {
        printf("Eroare la deschiderea fisierului");
        
    }

    int capacitate = 10; // Dimensiunea initiala a vectorului
    *dimensiune = 0;
    struct Magazin** vectorMagazine = (struct Magazin**)malloc(capacitate * sizeof(struct Magazin*));
    if (!vectorMagazine) {
        printf("Eroare la alocarea memoriei pentru vectorul de magazine");
        
    }

    struct Magazin* magazin;
    while ((magazin = citesteMagazin(fisier)) != NULL) {
        if (*dimensiune >= capacitate) {
            capacitate *= 2; // Dublare dimensiune
            vectorMagazine = (struct Magazin**)realloc(vectorMagazine, capacitate * sizeof(struct Magazin*));
            if (!vectorMagazine) {
                printf("Eroare la realocarea memoriei pentru vectorul de magazine");
                
            }
        }
        vectorMagazine[*dimensiune] = magazin;
        (*dimensiune)++;
    }

    fclose(fisier);
    return vectorMagazine;
}

// Functie care salvează un vector de obiecte de tip Magazin într-un fișier
void salveazaVectorMagazine(const char* numeFisier, struct Magazin** vectorMagazine, int dimensiune) {
    FILE* fisier = fopen(numeFisier, "w");
    if (!fisier) {
        printf("Eroare la deschiderea fisierului");
       
    }

    for (int i = 0; i < dimensiune; i++) {
        salveazaMagazin(fisier, vectorMagazine[i]);
    }

    fclose(fisier);
}

int main() {
    int dimensiune;
    struct Magazin** vectorMagazine = citesteVectorMagazine("magazine.txt", &dimensiune);

    printf("Obiecte citite din fisier:\n");
    for (int i = 0; i < dimensiune; i++) {
        printf("Cod: %d, Denumire: %s, Nr. produse: %d, Preturi: ", vectorMagazine[i]->cod, vectorMagazine[i]->denumire, vectorMagazine[i]->nrProduse);
        for (int j = 0; j < vectorMagazine[i]->nrProduse; j++) {
            printf("%.2f ", vectorMagazine[i]->preturi[j]);
        }
        printf("\n");
    }

    salveazaVectorMagazine("magazine_salvate.txt", vectorMagazine, dimensiune);

    // Eliberarea memoriei alocate
    for (int i = 0; i < dimensiune; i++) {
        elibereazaMagazin(vectorMagazine[i]);
    }
    free(vectorMagazine);

    return 0;
}


