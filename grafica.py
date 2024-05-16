import matplotlib.pyplot as plt

# Función para graficar las coordenadas y unir los puntos según una ruta específica
def graficar_coordenadas(coordenadas, ruta):
    # Separar las coordenadas en x y y
    x = [coord[0] for coord in coordenadas]
    y = [coord[1] for coord in coordenadas]

    # Graficar puntos y añadir números
    for i, (xi, yi) in enumerate(zip(x, y)):
        plt.scatter(xi, yi)
        plt.text(xi, yi, str(i), fontsize=12, ha='center', va='bottom')  # Añadir número del nodo

    # Unir puntos según la ruta
    for i in range(len(ruta) - 1):
        plt.plot([coordenadas[ruta[i]][0], coordenadas[ruta[i+1]][0]],
                 [coordenadas[ruta[i]][1], coordenadas[ruta[i+1]][1]], color='b')

    # Configuración del gráfico
    plt.xlabel('Coordenada X')
    plt.ylabel('Coordenada Y')
    plt.title('Gráfico de Coordenadas con Ruta Específica')
    plt.show()

# Leer coordenadas desde el archivo de texto
with open('coordenadas.txt', 'r') as file:
    lines = file.readlines()

# Convertir las coordenadas a números flotantes
coordenadas = [tuple(map(float, line.strip().split())) for line in lines]

# Definir la ruta específica (por ejemplo, una lista de índices de coordenadas)
ruta_especifica = [7, 12, 4, 18, 14, 6, 5, 19, 3, 22, 10, 17, 23, 20, 11, 9, 16, 0 ,15 ,21 ,24, 13, 1, 8, 2 ]   # Ejemplo de ruta que conecta todos los puntos en orden

# Llamar a la función para graficar las coordenadas con la ruta específica
graficar_coordenadas(coordenadas, ruta_especifica)
