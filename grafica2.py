import matplotlib.pyplot as plt
import numpy as np

# Función para inicializar el gráfico
def init():
    for line, scatter, text in zip(lines, scatters, texts):
        line.set_data([], [])
        scatter.set_offsets(np.zeros((0, 2)))  # Usamos np.zeros para inicializar los offsets
        text.set_text('')
    return lines + scatters + texts

# Función de animación que se llama en cada cuadro
def animate(frame):
    for i, scatter in enumerate(scatters):
        if i <= frame:
            node_idx = ruta_especifica[i]
            scatter.set_offsets(np.array(coordenadas[:node_idx+1]))  # Actualizamos los offsets con las coordenadas correctas
            texts[node_idx].set_text(str(node_idx))
            texts[node_idx].set_position(coordenadas[node_idx])

    # Conectar los nodos hasta el nodo actual en la ruta específica
    for i in range(frame):
        node_idx = ruta_especifica[i]
        next_node_idx = ruta_especifica[i + 1]
        x = [coordenadas[node_idx][0], coordenadas[next_node_idx][0]]
        y = [coordenadas[node_idx][1], coordenadas[next_node_idx][1]]
        lines[i].set_data(x, y)

    return lines + scatters + texts

# Crear la figura y los ejes
fig, ax = plt.subplots()
ax.set_xlabel('Coordenada X')
ax.set_ylabel('Coordenada Y')
ax.set_title('Animación de Conexión de Nodos')

# Definir las coordenadas y la ruta específica
with open('coord300.txt', 'r') as file:
    lines = file.readlines()

coordenadas = [tuple(map(float, line.strip().split())) for line in lines]
ruta_especifica = [ 247, 92, 167, 293, 61, 296, 83, 294, 7, 22, 84, 53, 283, 186, 276, 12, 52, 18, 213, 90, 295, 150, 30, 26, 44, 4, 72, 299, 110, 212, 49, 71, 141, 143, 178, 122, 121, 120, 149, 14, 106, 165, 250, 133, 98, 216, 142, 5, 297, 128, 57, 243, 135, 184, 190, 240, 179, 173, 270, 63, 277, 210, 8, 94, 204, 268, 278, 265, 154, 103, 77, 31, 86, 16, 252, 0, 234, 161, 101, 286, 56, 58, 282, 51, 176, 257, 235, 81, 275, 182, 39, 15, 266, 192, 20, 228, 124, 285, 80, 25, 104, 117, 96, 229, 194, 70, 202, 189, 107, 85, 158, 199, 32, 217, 200, 298, 225, 102, 227, 13, 159, 281, 249, 209, 163, 255, 239, 287, 279, 115, 36, 180, 169, 290, 9, 201, 288, 207, 231, 148, 69, 259, 162, 254, 226, 126, 93, 245, 187, 263, 175, 260, 244, 139, 79, 193, 203, 23, 108, 88, 125, 238, 269, 137, 74, 35, 123, 160, 237, 242, 130, 172, 157, 205, 215, 33, 67, 188, 140, 65, 54, 45, 273, 221, 224, 3, 47, 28, 119, 111, 214, 183, 114, 246, 50, 38, 145, 191, 144, 64, 166, 222, 153, 156, 19, 181, 197, 95, 42, 48, 258, 233, 129, 284, 146, 164, 220, 177, 271, 170, 100, 267, 10, 230, 174, 152, 198, 105, 66, 248, 59, 82, 41, 147, 11, 62, 1, 118, 34, 289, 291, 155, 78, 113, 97, 292, 206, 272, 262, 116, 43, 223, 136, 37, 280, 112, 91, 76, 40, 195, 232, 127, 138, 73, 134, 185, 29, 264, 46, 241, 208, 274, 151, 21, 68, 251, 253, 87, 131, 109, 171, 211, 261, 24, 218, 99, 168, 89, 256, 132, 17, 60, 55, 27, 236, 2, 196, 219, 6, 75 ]

# Inicializar las líneas
lines = [ax.plot([], [], color='b')[0] for _ in range(len(ruta_especifica) - 1)]

# Inicializar los puntos y textos
scatters = [ax.scatter([], [], color='r') for _ in range(len(coordenadas))]
texts = [ax.text([], [], '', fontsize=12, ha='center', va='bottom') for _ in range(len(coordenadas))]

# Configurar el tamaño del gráfico para que se ajuste mejor a tus datos
plt.xlim(min(coordenadas, key=lambda x: x[0])[0] - 1, max(coordenadas, key=lambda x: x[0])[0] + 1)
plt.ylim(min(coordenadas, key=lambda x: x[1])[1] - 1, max(coordenadas, key=lambda x: x[1])[1] + 1)

# Crear la animación manualmente
num_frames = len(ruta_especifica)
for frame in range(num_frames):
    init()
    animate(frame)
    plt.pause(0.5)  # Pausa entre cada cuadro

plt.show()
