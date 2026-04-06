from collections import deque
from typing import List, Optional, Tuple

from estado import Problema, mostrar_estado
from espacio import EstadosSucesores


def estado_a_tupla(estado: List[int]) -> Tuple[int, ...]:
    """
    Convierte un estado en lista a una tupla, para poder guardarlo
    en conjuntos de visitados.
    """
    return tuple(estado)


def reconstruir_camino(nodo) -> List[str]:
    """
    Reconstruye la secuencia de operadores desde el nodo inicial
    hasta el nodo objetivo.
    Cada nodo tiene la forma:
        (estado, camino)
    donde camino es una lista de operadores.
    """
    estado, camino = nodo
    return camino


def Soluciona8Puzzle(problema: Problema) -> Optional[List[str]]:
    """
    Resuelve el 8-puzzle mediante búsqueda en anchura (BFS).

    Entrada:
        - problema: objeto de la clase Problema con estado inicial
          y estado objetivo

    Salida:
        - lista de operadores que llevan del estado inicial al objetivo
          por ejemplo ['U', 'L', 'R']
        - None si no encuentra solución
    """
    estado_inicial = problema.estado_inicial

    if problema.es_estado_objetivo(estado_inicial):
        return []

    frontera = deque()
    frontera.append((estado_inicial, []))

    visitados = set()
    visitados.add(estado_a_tupla(estado_inicial))

    while frontera:
        estado_actual, camino_actual = frontera.popleft()

        if problema.es_estado_objetivo(estado_actual):
            return camino_actual

        sucesores = EstadosSucesores(estado_actual)

        for operador, nuevo_estado in sucesores:
            nuevo_estado_tupla = estado_a_tupla(nuevo_estado)

            if nuevo_estado_tupla not in visitados:
                visitados.add(nuevo_estado_tupla)
                nuevo_camino = camino_actual + [operador]
                frontera.append((nuevo_estado, nuevo_camino))

    return None


def mostrar_solucion(solucion: Optional[List[str]]) -> None:
    """
    Muestra la solución por pantalla de forma amigable.
    """
    if solucion is None:
        print("No se ha encontrado solución.")
    else:
        print("Solución encontrada:", " ".join(solucion))
        print("Número de pasos:", len(solucion))


if __name__ == "__main__":
    inicial = "123456870"
    objetivo = "123456780"

    problema = Problema.representacion_problema(inicial, objetivo)

    print("Estado inicial:")
    mostrar_estado(problema.estado_inicial)
    print()

    print("Estado objetivo:")
    mostrar_estado(problema.estado_objetivo)
    print()

    solucion = Soluciona8Puzzle(problema)
    mostrar_solucion(solucion)