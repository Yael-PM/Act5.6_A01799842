# Uso del ejercicio
- ejecutar el programa `main6.cpp`
- al ejecutar el programa se creara un archivo `.csv`
- posteriormente se deberá ejecutar el programa `graficar.py` para mostra el logaritmo del número de nodos visitados


---

# Conclusiones sobre la cantidad de nodos visitados para los dos métodos

- Los dos métodos están visitando exactamente la misma cantidad de nodos debido al método Branch and Bound. Esto se puede mejorar introduciendo heurísticas que permitan podar ramas donde sea evidente que no se puede mejorar la solución actual.

- La búsqueda exhaustiva es ineficiente para valores grandes de 𝑛 del mismo modo afecta al método Branch and Bound si no se optimiza adecuadamente con heurísticas. Sin optimizaciones, ambos métodos son prácticamente equivalentes en términos de eficiencia.

- Branch and Bound debería visitar significativamente menos nodos al evitar explorar ramas innecesarias.