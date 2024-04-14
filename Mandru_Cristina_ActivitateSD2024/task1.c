#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MAX_STRING_LENGTH 20

//Cristina Mandru -> C și M. Articolul Camara:
struct Camara {
	int cod;
	char* denumireGem;
	int nrBorcane;
	int pret;
};

void citireCamara(struct Camara* c) {
	printf("Introduceti codul: ");
	scanf("%d", &(c->cod));

	printf("Introduceti denumirea gemului: ");
	c->denumireGem = (char*)malloc(sizeof(char) * (MAX_STRING_LENGTH + 1));
	scanf("%20s", c->denumireGem);

	printf("Introduceti numarul de borcane: ");
	scanf("%d", &(c->nrBorcane));

	printf("Introduceti pretul unui borcan: ");
	scanf("%d", &(c->pret));
	printf("\n");
}

void dezalocareCamara(struct Camara* c){
	free(c->denumireGem);
	c->denumireGem = NULL;
}

//Funcție care calculează suma prețurilor pentru toate tipurile de gemuri

int sumaPreturilor(struct Camara* tipuriDeGemuri, int numarTipuriDeGemuri) {
	int suma = 0;
	for (int i = 0; i < numarTipuriDeGemuri; i++)
	{
		suma += tipuriDeGemuri[i].nrBorcane * tipuriDeGemuri[i].pret;
	}
	return suma;
}

int main()
{
	int numarTipuriDeGemuri;
	printf("Introduceti numarul de tipuri de gemuri: ");
	scanf("%d", &numarTipuriDeGemuri);
	printf("\n");
	
	struct Camara* tipuriDeGemuri = (struct Camara*)malloc(sizeof(struct Camara) * numarTipuriDeGemuri);
	for (int i = 0; i < numarTipuriDeGemuri; i++)
	{
		printf("Detalii despre gemul %d", i + 1);
		printf("\n");
		citireCamara(&tipuriDeGemuri[i]);
	}
	
	printf("\nTipurile de gemuri\n\n");
	for (int i = 0; i < numarTipuriDeGemuri; i++)
	{
		printf("Cod: %d\n", tipuriDeGemuri[i].cod);
		printf("Denumirea gemului: %s\n", tipuriDeGemuri[i].denumireGem);
		printf("Numarul de borcane: %d\n", tipuriDeGemuri[i].nrBorcane);
		printf("Pretul unui borcan: %d\n", tipuriDeGemuri[i].pret);
		printf("\n");
		dezalocareCamara(&tipuriDeGemuri[i]);
	}
	int suma = sumaPreturilor(tipuriDeGemuri, numarTipuriDeGemuri);
	printf("Suma preturilor pentru toate tipurile de gemuri: %d\n", suma);
	free(tipuriDeGemuri);
	return 0;
}
