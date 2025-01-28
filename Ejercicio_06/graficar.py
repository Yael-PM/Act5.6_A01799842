import matplotlib.pyplot as plt
import csv

# Leer datos del archivo CSV
tamanos = []
nodos_exh = []
nodos_bb = []

with open('Ejercicio_06/resultados.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader)  # Saltar la cabecera
    for row in reader:
        tamanos.append(int(row[0]))
        nodos_exh.append(int(row[1]))
        nodos_bb.append(int(row[2]))

# Graficar nodos visitados
plt.figure()
plt.plot(tamanos, nodos_exh, label="Exhaustivo", color="red")
plt.plot(tamanos, nodos_bb, label="Branch & Bound", color="blue")
plt.xlabel("Tamaño del conjunto (n)")
plt.ylabel("Nodos visitados")
plt.title("Nodos visitados vs Tamaño del conjunto")
plt.legend()
plt.grid()
plt.show()

# Graficar logaritmo de nodos visitados
plt.figure()
plt.plot(tamanos, [np.log10(x) for x in nodos_exh], label="Log(Exhaustivo)", color="red")
plt.plot(tamanos, [np.log10(x) for x in nodos_bb], label="Log(Branch & Bound)", color="blue")
plt.xlabel("Tamaño del conjunto (n)")
plt.ylabel("Log(Nodos visitados)")
plt.title("Log(Nodos visitados) vs Tamaño del conjunto")
plt.legend()
plt.grid()
plt.show()
