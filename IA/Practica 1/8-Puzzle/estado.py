from dataclasses import dataclass
from typing import List


def representacion_estado(cadena: str) -> List[int]:
    """
    Convierte una cadena de 9 dígitos, por ejemplo '123456780',
    en la representación interna de un estado del 8-puzzle:
    una lista de 9 enteros.

    Ejemplo:
        '123456780' -> [1, 2, 3, 4, 5, 6, 7, 8, 0]
    """
    return [int(c) for c in cadena]


def mostrar_estado(estado: List[int]) -> None:
    """
    Muestra por pantalla un estado del 8-puzzle en formato 3x3.
    La casilla vacía (0) se representa como un espacio en blanco.
    """
    for i in range(0, 9, 3):
        fila = estado[i:i + 3]
        print(" ".join(str(x) if x != 0 else " " for x in fila))


def estado_a_cadena(estado: List[int]) -> str:
    """
    Convierte un estado en lista a su representación en cadena.
    Ejemplo:
        [1,2,3,4,5,6,7,8,0] -> '123456780'
    """
    return "".join(str(x) for x in estado)


@dataclass
class Problema:
    """
    Representa un problema del 8-puzzle mediante:
    - estado_inicial
    - estado_objetivo

    Ambos se almacenan como listas de 9 enteros.
    """
    estado_inicial: List[int]
    estado_objetivo: List[int]

    @classmethod
    def representacion_problema(cls, inicial: str, objetivo: str) -> "Problema":
        """
        Crea un problema a partir de dos cadenas de 9 dígitos.

        Entrada:
            inicial: cadena con 9 números entre 0 y 8 sin repetir
            objetivo: cadena con 9 números entre 0 y 8 sin repetir

        Ejemplo:
            inicial = '123485706'
            objetivo = '123456780'

        Devuelve:
            un objeto Problema con ambos estados convertidos a listas.
        """
        estado_inicial = representacion_estado(inicial)
        estado_objetivo = representacion_estado(objetivo)
        return cls(estado_inicial, estado_objetivo)

    def es_estado_objetivo(self, estado: List[int]) -> bool:
        """
        Devuelve True si el estado recibido coincide con el estado objetivo
        del problema y False en caso contrario.
        """
        return estado == self.estado_objetivo

    def mostrar_problema(self) -> None:
        """
        Muestra por pantalla el estado inicial y el estado objetivo
        del problema en formato visual.
        """
        print("Estado inicial:")
        mostrar_estado(self.estado_inicial)
        print()
        print("Estado objetivo:")
        mostrar_estado(self.estado_objetivo)


if __name__ == "__main__":
    # Ejemplo de prueba básica
    estado = representacion_estado("123485706")
    print("Estado individual:")
    mostrar_estado(estado)
    print()

    problema = Problema.representacion_problema("123485706", "123456780")
    problema.mostrar_problema()
    print()

    print("¿El estado inicial es objetivo?:", problema.es_estado_objetivo(problema.estado_inicial))
    print("¿El estado objetivo es objetivo?:", problema.es_estado_objetivo(problema.estado_objetivo))