#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "puzle.h"

tEstado* crearEstado(int puzle[N][N]) {
    tEstado *estado = (tEstado*) malloc(sizeof(tEstado));
    int ficha = 0;
    for (int i = 0 ; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            ficha = puzle[i][j];
            estado->celdas[i][j] = ficha;
            estado->fila[ficha] = i;
            estado->col[ficha] = j;
        }
    }
    return estado;
}


tEstado* estadoInicial() {
   return crearEstado(puzle_inicial);
}


tEstado* estadoObjetivo() {
   return crearEstado(puzle_final);
}

int coste(unsigned op, tEstado* estado) {
   return 1;
}

int hManhattan(tEstado* act) {
    tEstado obj = *estadoObjetivo();
    int sum = 0;
    for (int i = 0; i < N*N; ++i) {
        sum += (abs(act->fila[i] - obj.fila[i]) + abs(act->col[i] - obj.col[i]));
    }
    return sum;
}

int hPiezasMalColocadas(tEstado* act) {
    tEstado obj = *estadoObjetivo();
    int sum = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (act->celdas[i][j] != obj.celdas[i][j])
                ++sum;
    return sum;
}
/* VISUALIZACION DE ESTADOS Y OPERADORES*/


void dispEstado(tEstado* estado) {
    for (int i = 0; i < N; ++i) {
        printf("[");
        for (int j = 0; j < N; ++j) {
            printf("%d", estado->celdas[i][j]);
        }
            printf("]\n");
    }
}


void dispOperador(unsigned op) {
    switch (op) {
        case ARRIBA:    printf("ARRIBA:\n\n");    break;
        case ABAJO:     printf("ABAJO:\n\n");     break;
        case IZQUIERDA: printf("IZQUIERDA:\n\n"); break;
        case DERECHA:   printf("DERECHA:\n\n");   break;
    }
}

int iguales(tEstado* m, tEstado* n) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (m->celdas[i][j] != n->celdas[i][j])
                return 0;
    return 1;
}

int testObjetivo(tEstado* estado) {
    return iguales(estado, estadoObjetivo());
}

int esValido(unsigned op, tEstado* estado) {
    int valido = 0;
    switch (op) {
        case ARRIBA:
            valido = (estado->fila[0] > 0);
        break;
        case ABAJO:
            valido = (estado->fila[0] < N - 1);
        break;
        case IZQUIERDA: 
            valido = (estado->col[0] > 0);
        break;
        case DERECHA:
            valido = (estado->col[0] < N - 1);
        break;
    }
    return valido;
}

static void intercambioEstado(tEstado* e, int fnew, int cnew,int fold, int cold) {
    int ficha = e->celdas[fnew][cnew];
    // intercambio
    e->celdas[fold][cold] = ficha;
    e->celdas[fnew][cnew] = 0;
    // intercambio indices vector filas y columnas.
    e->col[ficha] = cold;
    e->fila[ficha] = fold;
}

tEstado* aplicaOperador(unsigned op, tEstado* estado) {
    tEstado* nuevo = (tEstado*) malloc(sizeof(tEstado));
    memcpy(nuevo, estado, sizeof(tEstado));
    switch (op) {
        case ARRIBA:    
            --nuevo->fila[0];
        break;
        case ABAJO:
            ++nuevo->fila[0];
        break;
        case IZQUIERDA:
            --nuevo->col[0];
        break;
        case DERECHA:
            ++nuevo->col[0];
        break;
    }
    intercambioEstado(
        nuevo,
        nuevo->fila[0],
        nuevo->col[0],
        estado->fila[0],
        estado->col[0]);
    return nuevo;
}
