#include <stdio.h>
#include <malloc.h>

struct Calculator {
	char* serie;
	float pret;
	int nrPorturi;
};

struct Calculator initializare(const char* serie, float pret, int NrPorturi)
{
	struct Calculator c;
	//alocm spatiu pt serie
	c.serie = (char*)malloc(sizeof(char) * (strlen(serie) + 1));
	strcpy(c.serie, serie);
	c.nrPorturi = NrPorturi;
	c.pret = pret;
	return c;
}

void afisareCalculator(struct Calculator c) {
	printf("Calculatorul cu seria %s costa %5.2f si are %d porturi \n", c.serie, c.pret, c.nrPorturi);
}

//functie care afiseaza vectorul nostru
void afisareVectorCalculatoare(struct Calculator* vector, int nrCalculatoare) {

	if (nrCalculatoare > 0 && vector != NULL) {
		for (int i = 0; i < nrCalculatoare; i++) {
			afisareCalculator(vector[i]);
		}
		//verificam daca exista calculator:

	}
}

//functie care copiaza primele n elemente dintr-un vector

struct Calculator* copiazaNCalculatoare(struct Calculator* calculatoare, int nrCalculatoare, int nrCalculatoareCopiate) {
	struct Calculator* calculatoareCopiate = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalculatoareCopiate);
	for (int i = 0; i < nrCalculatoareCopiate; i++) {
		calculatoareCopiate[i] = calculatoare[i];
		calculatoareCopiate[i].serie = (char*)malloc(sizeof(char) * (1 + strlen(calculatoare[i].serie)));
		strcpy(calculatoareCopiate[i].serie, calculatoare[i].serie);
	}

	return calculatoareCopiate;
}

//alta functie
struct Calculator* copiazaCalculatoareCuMultePorturi(struct Calculator* calculatoare, int nrCalculatoare, int pragNrPorturi, int* nrCalculatoarePorturi)
{
	*nrCalculatoarePorturi = 0; //ca sa pornim cu el de la 0
	for (int i = 0; i < nrCalculatoare; i++)
	{
		if (calculatoare[i].nrPorturi > pragNrPorturi)
		{
			(*nrCalculatoarePorturi)++;
		}
	}
	struct Calculator* v = (struct Calculator*)malloc(sizeof(struct Calculator) * (*nrCalculatoarePorturi)); //prin *nrCalculatoarePorturi il deferentiem
	int k = 0;
	for (int i = 0; i < nrCalculatoare; i++)
	{
		if (calculatoare[i].nrPorturi > pragNrPorturi) {
			v[k++] = initializare(calculatoare[i].serie, calculatoare[i].pret, calculatoare[i].nrPorturi);
		}
	}
}

//returnam primul calculator care are un pret dat si primul din vector

void dezalocare(struct Calculator** vector, int* dim) {
	//stergem seria de la fiecare
	for (int i = 0; i < (*dim); i++)
	{
		free((*vector)[i].serie);
	}
	free(*vector);//il deferentiem
	*vector = NULL;
	*dim = 0;
}
void main()
{
	//int v[10]; //alocarea statica pe stack a vectorului ocupa 40 de octeti
	//int* v1; //ocupa 8/64 biti
	//facem o vb
	int nrCalculatoare = 5;
	//declaram un vector de calculatoare din sala de seminar:
	struct Calculator* calculatoare = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalculatoare);
	//initializam calculatoarele
	for (int i = 0; i < nrCalculatoare; i++)
	{
		calculatoare[i] = initializare("1234567890", i * 20 + 10, i + 1);
	}

	afisareVectorCalculatoare(calculatoare, nrCalculatoare);

	int nrCalculatoareCopiate = 3;
	struct Calculator* calculatoareCopiate = copiazaNCalculatoare(calculatoare, nrCalculatoare, nrCalculatoareCopiate);

	printf("\n\n");

	afisareVectorCalculatoare(calculatoareCopiate, nrCalculatoareCopiate);

	//ne cream un nou vector
	int nrCalculatoarePorturi = 0;
	struct Calculator* calculatoarePorturi = copiazaCalculatoareCuMultePorturi(calculatoare, nrCalculatoare, 3, &nrCalculatoarePorturi);

	printf("\n\n");
	afisareVectorCalculatoare(calculatoarePorturi, nrCalculatoarePorturi);

	dezalocare(&calculatoare, &nrCalculatoare);
}