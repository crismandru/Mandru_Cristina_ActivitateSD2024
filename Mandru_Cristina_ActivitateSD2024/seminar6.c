//OCUPA MAI MULT SPATIU PT CA AVEM Pointer SUPLIMENTAR
//fiecare nod retine adresa urm nod si a celui precedent 
//ultimul nod va pointa catre null
//iar nodul prim va pointa anterior tot catre null
//cream o alta structura in care avem adresa nodului inceput si final  unde in aceasta structura avem 
//2 pointeri cu care pot sa merg la inceput sau final

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include<string.h>

typedef struct Biblioteca Biblioteca;

struct Biblioteca {
	char* nume;
	int nrCarti;
	int nrCititori;
};

typedef struct Nod Nod;
struct Nod {
	Biblioteca info;
	Nod* next;
	Nod* prev; //previous
};

//struct ListaDubla va retine cei doi ptr
typedef struct ListaDubla ListaDubla; //am fc un alias
struct ListaDubla {
	Nod* head;
	Nod* tail;

};

Biblioteca initializare(const char* nume, int nrCarti, int nrCititori) {
	Biblioteca b; //cream ob
	b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.nrCarti = nrCarti;
	b.nrCititori = nrCititori;
	return b;
}

void inserareInceput(ListaDubla* listaDubla, Biblioteca b) {
	//fie obiectul il returnam fie il transmitem prin ptr 
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	//setam atributele
	//facem shallowcopy pt ca data trecuta am fc cu deep
	nod->info = b; //am pus informatii in nod (este cel nou creat) care va pointa catre cap
	nod->next = listaDubla->head;
	//cei doi pointeri trb sa ii setez mereu sa vina pe noul cap
	nod->prev = NULL;
	if (listaDubla->head) {
		listaDubla->head->prev = nod;
	}
	else {
		listaDubla->tail = nod;
	}
	listaDubla->head = nod;
	//vechiul cap inca pointeaza catre null si trb sa l schimb sa pointeze catre noul cap 
}

void afisareListaInceput(ListaDubla listaDubla)
{
	//nu modificam lista deci o transmitem prin valoare
	while (listaDubla.head) {
		//parcurgem pana devine null
		printf("Biblioteca: %s,;Numar cititori: %d; Numar carti:%d; \n", listaDubla.head->info.nume, listaDubla.head->info.nrCititori, listaDubla.head->info.nrCarti);
		listaDubla.head = listaDubla.head->next;
	}
	printf("\n");
}
void stergereNodNume(ListaDubla* listaDubla, const char* nume) {
	Nod* aux = listaDubla->head;
	while (aux && strcmp(nume, aux->info.nume) != 0) {
		aux = aux->next;
	}
	if (aux) {
		if (aux == listaDubla->head) {
			if (aux == listaDubla->tail) {
				listaDubla->head = NULL;
				listaDubla->tail = NULL;
			}
			else {
				listaDubla->head = listaDubla->head->next;
				listaDubla->head->prev = NULL;
			}
		}
		else
		{
			if (aux == listaDubla->tail) {
				aux->prev->next = NULL;
				listaDubla->tail = aux->prev;
			}
			else {
				aux->next->prev = aux->prev;
				aux->prev->next = aux->next;
			}
			free(aux->info.nume);
			free(aux);
		}
	}
}


void stergereLista(ListaDubla* listaDubla) {
	while (listaDubla->head) {
		free(listaDubla->head->info.nume);
		Nod* aux = listaDubla->head;
		listaDubla->head = listaDubla->head->next;
		free(aux);
	}
	listaDubla->head = NULL;
	listaDubla->tail = NULL;
}

//parcurgere de la sf spre inceput:nr total de carti din bibliotecile noastre 
int nrCartiTotal(ListaDubla listaDubla)
{
	int rezultat = 0;
	while (listaDubla.tail) {
		rezultat += listaDubla.tail->info.nrCarti;
		listaDubla.tail = listaDubla.tail->prev;
	}
	return rezultat;
}

void main() {
	Biblioteca b1 = initializare("Mihai Eminescu", 150, 20);
	Biblioteca b2 = initializare("Ioan Slavici", 200, 30);
	Biblioteca b3 = initializare("Tudor Arghezi", 100, 15);
	ListaDubla listaDubla; //este un obiect
	listaDubla.head = NULL;
	listaDubla.tail = NULL;
	inserareInceput(&listaDubla, b1);
	inserareInceput(&listaDubla, b2);
	inserareInceput(&listaDubla, b3);
	afisareListaInceput(listaDubla);
	int rezultat = nrCartiTotal(listaDubla);
	printf("nr total de carti ->%d", rezultat);
	//stergereNodNume(&listaDubla, "Ioan Slavici"); //stergere din mijloc
	//afisareListaInceput(listaDubla);
	//stergereNodNume(&listaDubla, "Mihai Eminescu");
	//afisareListaInceput(listaDubla);
	//stergereNodNume(&listaDubla, "Tudor Arghezi");
	//afisareListaInceput(listaDubla);
	stergereLista(&listaDubla);
	afisareListaInceput(listaDubla);
}