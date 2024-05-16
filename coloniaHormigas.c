#include <stdlio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 25 // Número de ciudades
#define MAX_ITERATIONS 1000 // Número máximo de iteraciones
#define ALPHA 1.0 // Importancia de la feromonag
#define BETA 2.0 // Importancia de la visibilidad
#define RHO 0.5 // Tasa de evaporación de la feromona
#define Q 100 // Cantidad de feromona depositada

double distancia[N][N]; // Matriz de distancias entre ciudades
double feromona[N][N]; // Matriz de feromonas entre ciudades

// Función para calcular la distancia euclidiana entre dos ciudades
double calcularDistancia(int ciudad1, int ciudad2) {
    return distancia[ciudad1][ciudad2];
}

// Función para inicializar las matrices de distancia y feromona
void inicializarMatrices() {
    FILE *archivo = fopen("distancias.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(archivo, "%lf", &distancia[i][j]);
            feromona[i][j] = 0.1; // Inicialización de feromonas
        }
    }

    fclose(archivo);
}

// Función para encontrar la siguiente ciudad basada en la regla de transición de probabilidad
int siguienteCiudad(int ciudadActual, int *visitado) {
    double suma = 0.0;
    double probabilidad[N];
    int siguiente = -1;

    // Calcular la suma de la probabilidad
    for (int i = 0; i < N; i++) {
        if (!visitado[i]) {
            probabilidad[i] = pow(feromona[ciudadActual][i], ALPHA) * pow(1.0 / distancia[ciudadActual][i], BETA);
            suma += probabilidad[i];
        } else {
            probabilidad[i] = 0.0;
        }
    }

    // Seleccionar la siguiente ciudad basada en la probabilidad
    double random = ((double)rand() / RAND_MAX);
    double acumulada = 0.0;
    for (int i = 0; i < N; i++) {
        if (!visitado[i]) {
            acumulada += probabilidad[i] / suma;
            if (random <= acumulada) {
                siguiente = i;
                break;
            }
        }
    }

    return siguiente;
}

// Función para actualizar las feromonas después de cada iteración
void actualizarFeromona(int *recorrido) {
    for (int i = 0; i < N - 1; i++) {
        feromona[recorrido[i]][recorrido[i + 1]] += Q / distancia[recorrido[i]][recorrido[i + 1]];
        feromona[recorrido[i + 1]][recorrido[i]] += Q / distancia[recorrido[i]][recorrido[i + 1]];
    }
}

// Función principal para resolver el TSP utilizando el algoritmo de colonia de hormigas
void resolverTSP() {
    int recorrido[N]; // Arreglo para almacenar el recorrido óptimo
    double mejorDistancia = -1;

    for (int iteracion = 0; iteracion < MAX_ITERATIONS; iteracion++) {
        int visitado[N] = {0}; // Arreglo para verificar si una ciudad ha sido visitada
        recorrido[0] = rand() % N; // Ciudad inicial aleatoria

        for (int i = 1; i < N; i++) {
            visitado[recorrido[i - 1]] = 1;
            recorrido[i] = siguienteCiudad(recorrido[i - 1], visitado);
        }

        // Calcular la distancia total del recorrido
        double distanciaTotal = 0.0;
        for (int i = 0; i < N - 1; i++) {
            distanciaTotal += distancia[recorrido[i]][recorrido[i + 1]];
        }
        distanciaTotal += distancia[recorrido[N - 1]][recorrido[0]]; // Regresar a la ciudad inicial

        // Actualizar la mejor distancia y recorrido
        if (mejorDistancia == -1 || distanciaTotal < mejorDistancia) {
            mejorDistancia = distanciaTotal;
            for (int i = 0; i < N; i++) {
                recorrido[i] = recorrido[i];
            }
        }

        // Actualizar las feromonas
        actualizarFeromona(recorrido);
    }

    // Imprimir el recorrido óptimo y la mejor distancia
    printf("Recorrido óptimo: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", recorrido[i]);
    }
    printf("\nMejor distancia: %.2f\n", mejorDistancia);
}

int main() {
    srand(time(NULL));
    inicializarMatrices();
    resolverTSP();
    return 0;
}
