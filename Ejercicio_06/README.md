
Conclusiones sobre la cantidad de nodos visitados para los dos métodos
Crecimiento Exponencial de los Nodos Visitados:

Tanto el método de búsqueda exhaustiva como el método de Branch and Bound visitan un número de nodos que crece exponencialmente con 
𝑛
n, el tamaño del conjunto. Esto se debe a que cada elemento puede estar en uno de los dos subconjuntos, lo que genera 
2
𝑛
2 
n
  combinaciones posibles.


En este caso, los dos métodos están visitando exactamente la misma cantidad de nodos porque no se están aplicando estrategias de poda efectivas en el método Branch and Bound. Esto indica que el método Branch and Bound, tal como está implementado, no está eliminando ramas del árbol de búsqueda.
Esto se puede mejorar introduciendo heurísticas que permitan podar ramas donde sea evidente que no se puede mejorar la solución actual.
Escalabilidad:

La búsqueda exhaustiva es ineficiente para valores grandes de 𝑛 n debido a su crecimiento exponencial. El mismo problema afecta al método Branch and Bound si no se optimiza adecuadamente con heurísticas. Sin optimizaciones, ambos métodos son prácticamente equivalentes en términos de eficiencia.
Uso de Branch and Bound:

En su forma actual, el método Branch and Bound no presenta ninguna ventaja sobre la búsqueda exhaustiva, ya que no reduce el número de nodos explorados. Esto puede deberse a la falta de criterios de poda basados en heurísticas específicas. Con una poda efectiva, Branch and Bound debería visitar significativamente menos nodos al evitar explorar ramas innecesarias.