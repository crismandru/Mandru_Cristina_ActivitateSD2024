#include<stdio.h>
#include <malloc.h>
struct Masina {
	char* marca;
	float capacitateCilindrica;
	int an;
};
////functie care sa afiseze

void afisareMasina(const struct Masina* m)
{
	if (m->marca != NULL) {

		printf("Marca:%s\n", m->marca);
	}
	printf("capacitate cilindrica:%5.2f\n", m->capacitateCilindrica);
	printf("An:%d\n\n", m->an);


}

//functie care va initializa o masina
struct Masina initializareMasina(const char* marca, int an, float capacitateCilindrica)
{
	struct Masina m; //am creat o masina
	m.an = an;
	m.capacitateCilindrica = capacitateCilindrica;
	if (marca != NULL)
	{
		m.marca = malloc(strlen(marca) + 1);//sizeof char este 1 si n am mai pus*1
		strcpy(m.marca, marca);
	}
	else {
		m.marca = (char*)malloc(strlen("N/A") + 1);
		strcpy(m.marca, "N/A");
	}
	return m;
}

void dezalocareMasina(struct Masina* masina) {
	free(masina->marca);
	masina->marca = NULL;
}
int main() {
	struct Masina masina1;
	//Dacia
	masina1.marca = (char*)malloc(sizeof(char) * (strlen("Dacia") + 1));//alocam spatiu pt marca
	strcpy(masina1.marca, "Dacia");

	masina1.capacitateCilindrica = 1.9;
	masina1.an = 2023;

	afisareMasina(&masina1);

	//eliberam memoria
	/*free(masina1.marca);
	masina1.marca = NULL;*/
	dezalocareMasina(&masina1);

	//initializam alta masina
	struct Masina masina2 = initializareMasina("Masina", 2022, 2.49);
	afisareMasina(&masina2);

	/*free(masina2.marca);
	masina2.marca = NULL;*/
	dezalocareMasina(&masina2);
	afisareMasina(&masina2); //dankly ptr e o adresa unde nu e nimic
	return 0;
}