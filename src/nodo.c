#include "nodo.h"
#include <stdio.h>
#include <stdlib.h>

static tNodo *sucesoresNodo(tNodo *n, unsigned op) {
  tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));
  nuevo->estado = aplicaOperador(n->estado, op);
  nuevo->padre = n;
  nuevo->operador = op;
  nuevo->costeCamino = n->costeCamino + coste(n->estado, op);
  nuevo->profundidad = n->profundidad + 1;
  nuevo->valHeuristica = heuristica(nuevo->estado);
  return nuevo;
}

GQueue *Expandir(tNodo *n) {
  GQueue *sucesores = g_queue_new();
  for (unsigned op = 1; op <= NUM_OPERADORES; ++op) {
    if (esValido(n->estado, op) == 1) {
      g_queue_push_tail(sucesores, (void *)sucesoresNodo(n, op));
    }
  }
  return sucesores;
}

tNodo *nodoInicial() {
  tNodo *inicial = (tNodo *)malloc(sizeof(tNodo));
  inicial->estado = estadoInicial();
  inicial->padre = NULL;
  inicial->operador = 0;
  inicial->costeCamino = 0;
  inicial->profundidad = 0;
  inicial->valHeuristica = heuristica(inicial->estado);
  return inicial;
}

void dispCamino(tNodo *n) {
  if (n->padre == NULL) {
    printf("INICIO\n\n");
    dispEstado(n->estado);
    printf("\n");
  } else {
    dispCamino(n->padre);
    dispOperador(n->operador);
    dispEstado(n->estado);
    printf("\n");
  }
}

void dispSolucion(tNodo *n) {
  dispCamino(n);
  printf("Profundidad = %d\n", n->profundidad);
  printf("Coste = %d\n", n->costeCamino);
}

gint estadoNodoIguales(gconstpointer e1, gconstpointer e2) {
  tNodo *el1 = (tNodo *)e1;
  tNodo *el2 = (tNodo *)e2;
  return (gint)!iguales(el1->estado, el2->estado);
}

GQueue *g_queue_merge_sorted(GQueue *a, GQueue *s, GCompareDataFunc cmp) {
  while (!g_queue_is_empty(s)) {
    g_queue_insert_sorted(a, g_queue_pop_head(s), cmp, NULL);
  }
  return a;
}