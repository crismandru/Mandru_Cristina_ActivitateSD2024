#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Mesaj Mesaj;
typedef struct Heap Heap;

struct Mesaj {
	char* text;
	int prioritate;
};

struct Heap {
	Mesaj* vector;
	int dimensiune;
	int dimensiuneTotala;
};

Mesaj init(const char* text, int prioritate) {
	Mesaj m;
	m.text = malloc(sizeof(char) * (1 + strlen(text)));
	strcpy(m.text, text);
	m.prioritate = prioritate;
	return m;
}

Heap initHeap(int dimensiune) {
	Heap h;
	h.vector = malloc(sizeof(char) * dimensiune);
	h.dimensiune = 0;
	h.dimensiuneTotala = dimensiune;
	return h;
}

void afisareMesaj(Mesaj m) {
	printf("Mesajul cu textul %s si prioritatea %d\n",
		m.text, m.prioritate);
}

void afisareHeap(Heap h) {
	for (int i = 0; i < h.dimensiune; i++)
	{
		afisareMesaj(h.vector[i]);
	}
}

void filtrareHeap(Heap h, int poz) {
	int poz_stanga = poz * 2 + 1;
	int poz_dreapta = poz * 2 + 2;
	int poz_max = poz;
	if (poz_stanga<h.dimensiune && h.vector[poz_stanga].prioritate
	>h.vector[poz_max].prioritate) {
		poz_max = poz_stanga;
	}
	if (poz_dreapta<h.dimensiune && h.vector[poz_dreapta].prioritate
	>h.vector[poz_max].prioritate) {
		poz_max = poz_dreapta;
	}
	if (poz_max != poz) {
		Mesaj aux = h.vector[poz];
		h.vector[poz] = h.vector[poz_max];
		h.vector[poz_max] = aux;
		if (poz_max * 2 + 1 < h.dimensiune) {
			filtrareHeap(h, poz_max);
		}
	}
}

Mesaj extragereHeap(Heap* h) {
	if (h->dimensiune > 0) {
		Mesaj aux = h->vector[0];
		h->vector[0] = h->vector[h->dimensiune-1];
		h->vector[h->dimensiune - 1] = aux;
		h->dimensiune--;
		for (int i = h->dimensiune / 2; i >= 0; i--)
		{
			filtrareHeap(*h, i);
		}
		return aux;
	}
}

void afisareHeapTotala(Heap h) {
	for (int i = 0; i < h.dimensiuneTotala; i++)
	{
		afisareMesaj(h.vector[i]);
	}
}

void dezalocareHeap(Heap* h) {
	if (h->vector != NULL)
	{
		while (h->dimensiuneTotala > 0) {
			free(h->vector[h->dimensiuneTotala-1].text);
			h->dimensiuneTotala--;
		}
		free(h->vector);
		h->vector = NULL;
		h->dimensiune = 0;
	}
}

void main() {
	Heap h;
	h = initHeap(6);
	h.vector[0] = init("Salut", 3);
	h.vector[1] = init("Salut ce faci", 8);
	h.vector[2] = init("Buna", 6);
	h.vector[3] = init("Noroc", 2);
	h.vector[4] = init("Ce mai faci", 9);
	h.vector[5] = init("Pa pa", 4);
	h.dimensiune = 6;
	afisareHeap(h);

	printf("\nDupa filtrare:\n\n");
	for (int i = h.dimensiune/2-1; i >= 0; i--)
	{
		filtrareHeap(h, i);
	}
	afisareHeap(h);

	printf("\nExtragere:\n\n");
	afisareMesaj(extragereHeap(&h));
	afisareMesaj(extragereHeap(&h));
	afisareMesaj(extragereHeap(&h));
	afisareMesaj(extragereHeap(&h));
	afisareMesaj(extragereHeap(&h));
	afisareMesaj(extragereHeap(&h));

	printf("\n***********************************\n\n");
	afisareHeapTotala(h);

	dezalocareHeap(&h);
}
