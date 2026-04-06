from typing import List, Tuple
from estado import mostrar_estado
from acciones import OPERADORES, AplicaOperador, EsAplicableU, EsAplicableD, EsAplicableL, EsAplicableR


def EstadosSucesores(estado: List[int]) -> List[Tuple[str, List[int]]]:
    """
    Genera la lista de estados sucesores de un estado dado del 8-puzzle.

    Entrada:
        - estado: lista de 9 enteros que representa un estado del 8-puzzle

    Salida:
        - lista de tuplas (operador, nuevo_estado), donde:
            operador es 'U', 'D', 'L' o 'R'
            nuevo_estado es el estado resultante de aplicar ese operador

    La función solo incluye los operadores aplicables en el estado recibido.
    """
    sucesores = []

    if EsAplicableU(estado):
        sucesores.append(("U", AplicaOperador(estado, "U")))

    if EsAplicableD(estado):
        sucesores.append(("D", AplicaOperador(estado, "D")))

    if EsAplicableL(estado):
        sucesores.append(("L", AplicaOperador(estado, "L")))

    if EsAplicableR(estado):
        sucesores.append(("R", AplicaOperador(estado, "R")))

    return sucesores


if __name__ == "__main__":
    # Estado de prueba
    estado = [1, 2, 3,
              4, 8, 5,
              7, 0, 6]

    print("Estado original:")
    mostrar_estado(estado)
    print()

    sucesores = EstadosSucesores(estado)

    print("Estados sucesores:")
    for operador, nuevo_estado in sucesores:
        print(f"Operador aplicado: {operador}")
        mostrar_estado(nuevo_estado)
        print()