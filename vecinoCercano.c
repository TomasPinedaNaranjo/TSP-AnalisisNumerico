#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define N 25 // Número de ciudades

// Función para encontrar el siguiente nodo más cercano
int encontrarSiguienteNodo(int ciudadActual, int visitado[N], int distancias[N][N]) {
    int minDistancia = INT_MAX;
    int siguienteNodo = -1;

    for (int i = 0; i < N; i++) {
        if (!visitado[i] && distancias[ciudadActual][i] < minDistancia) {
            minDistancia = distancias[ciudadActual][i];
            siguienteNodo = i;
        }
    }

    return siguienteNodo;
}

// Función para encontrar la solución aproximada al TSP usando la heurística del vecino más cercano
void tspVecinoMasCercano(int distancias[N][N]) {
    int visitado[N] = {0}; // Array para marcar los nodos visitados
    int ruta[N]; // Array para almacenar la ruta
    int ciudadActual = 0; // Comenzamos desde la ciudad 0
    int distanciaTotal = 0; // Variable para almacenar la distancia total

    visitado[ciudadActual] = 1; // Marcamos la ciudad actual como visitada
    ruta[0] = ciudadActual; // Añadimos la ciudad actual a la ruta

    for (int i = 1; i < N; i++) {
        int siguienteNodo = encontrarSiguienteNodo(ciudadActual, visitado, distancias);
        distanciaTotal += distancias[ciudadActual][siguienteNodo]; // Sumamos la distancia al siguiente nodo
        ruta[i] = siguienteNodo; // Añadimos el siguiente nodo a la ruta
        visitado[siguienteNodo] = 1; // Marcamos el siguiente nodo como visitado
        ciudadActual = siguienteNodo; // Actualizamos la ciudad actual
    }

    // Calcular la distancia de regreso a la ciudad inicial
    distanciaTotal += distancias[ciudadActual][0];

    // Imprimimos la ruta y la distancia total
    printf("Ruta aproximada: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", ruta[i]);
    }
    printf("\nDistancia total: %d\n", distanciaTotal);
}

int main() {
    // Leer la matriz de distancias desde un archivo de texto
    FILE *archivo;
    archivo = fopen("distancias2.txt", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    int distancias[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(archivo, "%d", &distancias[i][j]);
        }
    }
    fclose(archivo);

    // Medir el tiempo de ejecución
    clock_t inicio = clock();

    // Calcular la ruta usando la heurística del vecino más cercano
    tspVecinoMasCercano(distancias);

    clock_t fin = clock();
    double tiempo_total = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución: %.6f segundos\n", tiempo_total);

    return 0;
}
