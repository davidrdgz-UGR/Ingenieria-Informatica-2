from typing import List
from estado import mostrar_estado


# Operadores posibles del 8-puzzle
OPERADORES = ["U", "D", "L", "R"]


def posicion_vacia(estado: List[int]) -> int:
    """
    Devuelve la posición de la casilla vacía (0) en la lista.
    """
    return estado.index(0)


def EsAplicableU(estado: List[int]) -> bool:
    """
    El operador U es aplicable si la casilla vacía no está en la primera fila.
    """
    pos = posicion_vacia(estado)
    return pos not in [0, 1, 2]


def EsAplicableD(estado: List[int]) -> bool:
    """
    El operador D es aplicable si la casilla vacía no está en la última fila.
    """
    pos = posicion_vacia(estado)
    return pos not in [6, 7, 8]


def EsAplicableL(estado: List[int]) -> bool:
    """
    El operador L es aplicable si la casilla vacía no está en la primera columna.
    """
    pos = posicion_vacia(estado)
    return pos not in [0, 3, 6]


def EsAplicableR(estado: List[int]) -> bool:
    """
    El operador R es aplicable si la casilla vacía no está en la última columna.
    """
    pos = posicion_vacia(estado)
    return pos not in [2, 5, 8]


def aplicar_U(estado: List[int]) -> List[int]:
    """
    Devuelve un nuevo estado resultante de mover la casilla vacía hacia arriba.
    """
    nuevo_estado = estado.copy()
    pos = posicion_vacia(nuevo_estado)
    nueva_pos = pos - 3
    nuevo_estado[pos], nuevo_estado[nueva_pos] = nuevo_estado[nueva_pos], nuevo_estado[pos]
    return nuevo_estado


def aplicar_D(estado: List[int]) -> List[int]:
    """
    Devuelve un nuevo estado resultante de mover la casilla vacía hacia abajo.
    """
    nuevo_estado = estado.copy()
    pos = posicion_vacia(nuevo_estado)
    nueva_pos = pos + 3
    nuevo_estado[pos], nuevo_estado[nueva_pos] = nuevo_estado[nueva_pos], nuevo_estado[pos]
    return nuevo_estado


def aplicar_L(estado: List[int]) -> List[int]:
    """
    Devuelve un nuevo estado resultante de mover la casilla vacía hacia la izquierda.
    """
    nuevo_estado = estado.copy()
    pos = posicion_vacia(nuevo_estado)
    nueva_pos = pos - 1
    nuevo_estado[pos], nuevo_estado[nueva_pos] = nuevo_estado[nueva_pos], nuevo_estado[pos]
    return nuevo_estado


def aplicar_R(estado: List[int]) -> List[int]:
    """
    Devuelve un nuevo estado resultante de mover la casilla vacía hacia la derecha.
    """
    nuevo_estado = estado.copy()
    pos = posicion_vacia(nuevo_estado)
    nueva_pos = pos + 1
    nuevo_estado[pos], nuevo_estado[nueva_pos] = nuevo_estado[nueva_pos], nuevo_estado[pos]
    return nuevo_estado


def AplicaOperador(estado: List[int], operador: str) -> List[int]:
    """
    Aplica un operador ('U', 'D', 'L', 'R') a un estado si es válido
    y devuelve el nuevo estado.

    Entrada:
        - estado: lista de 9 enteros que representa un estado del 8-puzzle
        - operador: cadena 'U', 'D', 'L' o 'R'

    Salida:
        - nuevo estado resultante de aplicar el operador

    Si el operador no es aplicable, lanza una excepción.
    """
    if operador == "U":
        if EsAplicableU(estado):
            return aplicar_U(estado)
        raise ValueError("El operador U no es aplicable en este estado.")

    elif operador == "D":
        if EsAplicableD(estado):
            return aplicar_D(estado)
        raise ValueError("El operador D no es aplicable en este estado.")

    elif operador == "L":
        if EsAplicableL(estado):
            return aplicar_L(estado)
        raise ValueError("El operador L no es aplicable en este estado.")

    elif operador == "R":
        if EsAplicableR(estado):
            return aplicar_R(estado)
        raise ValueError("El operador R no es aplicable en este estado.")

    else:
        raise ValueError(f"Operador desconocido: {operador}")


if __name__ == "__main__":
    # Estado de prueba
    estado = [1, 2, 3,
              4, 8, 5,
              7, 0, 6]

    print("Estado original:")
    mostrar_estado(estado)
    print()

    print("¿U aplicable?:", EsAplicableU(estado))
    print("¿D aplicable?:", EsAplicableD(estado))
    print("¿L aplicable?:", EsAplicableL(estado))
    print("¿R aplicable?:", EsAplicableR(estado))
    print()

    for op in OPERADORES:
        try:
            nuevo = AplicaOperador(estado, op)
            print(f"Estado tras aplicar {op}:")
            mostrar_estado(nuevo)
            print()
        except ValueError as e:
            print(f"No se puede aplicar {op}: {e}")
            print()