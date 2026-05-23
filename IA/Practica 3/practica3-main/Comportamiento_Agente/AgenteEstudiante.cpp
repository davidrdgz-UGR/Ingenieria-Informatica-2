#include "AgenteEstudiante.hpp"
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>

using namespace std;


AgenteEstudiante::AgenteEstudiante(int id, int profundidadMax, double tiempoMax, int numHeuristica, ModoJuego modo) 
    : id(id), profundidadMax(profundidadMax), tiempoMaxSegundos(tiempoMax), numHeuristica(numHeuristica), modo(modo), abortarBanda(false) {
    nodosVisitados = 0;
}

bool AgenteEstudiante::tieneLimiteDeTiempo() const {
    return modo != ModoJuego::STATUS;
}

pair<int, int> AgenteEstudiante::think(const Tablero& tablero) {
    pair<int, int> mejor;
    nodosVisitados = 0;
    abortarBanda = false;
    inicioBusqueda = chrono::steady_clock::now();

    switch (modo)
    {
    case ModoJuego::ALEATORIO:
        return JuegaAleatorio(tablero);
        break;
    
    case ModoJuego::STATUS:
        Status(tablero, mejor);
        return mejor;
        break;    

    case ModoJuego::MINIMAX:
        minimax(tablero, 0, profundidadMax, mejor);
        return mejor;
        break; 

    case ModoJuego::INTELIGENTE:
        return JuegaInteligente(tablero);   
        break;
    }
        
    return {-1, -1};
}


/**
 * @brief Compara dos tableros para identificar cuál ha sido el movimiento realizado.
 * @param padre Estado inicial del tablero.
 * @param hijo Estado resultante tras un movimiento.
 * @return Un par (fila, columna) con la posición de la nueva pieza.
 */
pair<int, int> SacarMovimiento(const Tablero& padre, const Tablero &hijo){
    for(int f=0; f<padre.getFilas(); ++f)
        for(int c=0; c<padre.getColumnas(); ++c)
            if (padre.getCelda(f,c) == 0 && hijo.getCelda(f,c) != 0) 
                return {f, c};
    return {-1, -1};
}

/**
 * @brief Implementa un agente que juega de forma totalmente aleatoria.
 * @param tablero Estado actual del juego.
 * @return La jugada elegida al azar.
 */
pair<int, int> AgenteEstudiante::JuegaAleatorio(const Tablero& tablero) {

    // Calculo los tableros descendientes de tablero
    auto sucesores = tablero.getSucesores();

    // Si no tiene descendientes, paso el turno
    if (sucesores.empty()) return {-1, -1};

    // Elijo aleatoriamente uno de los descendientes
    int elegido = rand() % sucesores.size();

    // Saco el movimiento realizado comparando el tablero original con el elegido.
    pair<int,int> Mov = SacarMovimiento(tablero, sucesores[elegido]);

    return Mov;
}


/**
 * @brief Algoritmo de resolución completa para estados de final de juego.
 * Determina si una posición está matemáticamente ganada, perdida o empatada.
 * @param tablero Estado a evaluar.
 * @param Mov [Salida] La jugada óptima encontrada.
 * @return Resultado del análisis (VICTORIA, DERROTA o EMPATE).
 */
AgenteEstudiante::Resultado AgenteEstudiante::Status(const Tablero &tablero, pair<int,int> &Mov) {
    /* ============== Este trozo de código se tiene que quedar aquí  =============== */
    nodosVisitados++;
    /* ============== Empieza a partir de aquí tu implementación  =============== */

    Mov = {-1, -1};

    int oponente = (id == 1) ? 2 : 1;

    // Comprobamos si el tablero actual ya es terminal.
    int ganador = tablero.comprobarGanador();

    if (ganador == id) {
        return Resultado::VICTORIA;
    }

    if (ganador == oponente) {
        return Resultado::DERROTA;
    }

    if (ganador == -1) {
        return Resultado::EMPATE;
    }

    // Generamos sucesores con sus movimientos asociados.
    auto sucesores = tablero.getSucesoresConMovimientos();

    // Si no hay sucesores, tratamos la posición como empate.
    if (sucesores.empty()) {
        return Resultado::EMPATE;
    }

    bool mueveNuestroJugador = (tablero.getJugadorTurno() == id);

    if (mueveNuestroJugador) {
        // Nuestro jugador intenta maximizar:
        // VICTORIA > EMPATE > DERROTA

        Resultado mejorResultado = Resultado::DERROTA;
        pair<int,int> mejorMov = sucesores[0].second;

        for (const auto& sucesor : sucesores) {

            pair<int,int> movHijo;
            Resultado r = Status(sucesor.first, movHijo);

            if (r == Resultado::VICTORIA) {
                Mov = sucesor.second;
                return Resultado::VICTORIA;
            }

            if (r == Resultado::EMPATE && mejorResultado == Resultado::DERROTA) {
                mejorResultado = Resultado::EMPATE;
                mejorMov = sucesor.second;
            }

        }

        Mov = mejorMov;
        return mejorResultado;

    }else {
        // El rival intenta minimizar nuestro resultado:
        // para nosotros: DERROTA < EMPATE < VICTORIA

        Resultado peorResultado = Resultado::VICTORIA;
        pair<int,int> peorMov = sucesores[0].second;

        for (const auto& sucesor : sucesores) {
            pair<int,int> movHijo;
            Resultado r = Status(sucesor.first, movHijo);

            if (r == Resultado::DERROTA) {
                Mov = sucesor.second;
                return Resultado::DERROTA;
            }

            if (r == Resultado::EMPATE && peorResultado == Resultado::VICTORIA) {
                peorResultado = Resultado::EMPATE;
                peorMov = sucesor.second;
            }
        }

        Mov = peorMov;
        return peorResultado;
    }
}



/**
 * @brief Implementación del algoritmo Minimax clásico.
 * @param tablero Estado actual.
 * @param profundidad Nivel actual en el árbol de búsqueda.
 * @param prof_Max Límite de profundidad de la búsqueda.
 * @param Mov [Salida] La mejor jugada encontrada en la raíz.
 * @return Valor heurístico del estado.
 */
double AgenteEstudiante::minimax(const Tablero &tablero, int profundidad, int prof_Max, std::pair<int,int> &Mov) {
    /* ============== Este trozo de código se tiene que quedar aquí  =============== */
    nodosVisitados++;
    if (abortarBanda) return 0;
    
    if (std::chrono::duration<double>(std::chrono::steady_clock::now() - inicioBusqueda).count() > tiempoMaxSegundos) {
        abortarBanda = true;
        return 0;
    }
    /* ============== Empieza a partir de aquí tu implementación  =============== */

    Mov = {-1, -1};

    int oponente = (id == 1) ? 2 : 1;

    // 1. Comprobar si el tablero actual ya es terminal.
    Tablero copia = tablero;
    int ganador = copia.comprobarGanador();

    if (ganador == id) {
        return GANAR - profundidad;
    }

    if (ganador == oponente) {
        return PERDER + profundidad;
    }

    if (ganador == -1) {
        return 0;
    }

    // 2. Si hemos llegado a la profundidad máxima, usamos la heurística.
    if (profundidad >= prof_Max) {
        return heuristica(tablero);
    }

    // 3. Generar sucesores.
    auto sucesores = tablero.getSucesoresConMovimientos();

    if (sucesores.empty()) {
        return heuristica(tablero);
    }

    bool mueveNuestroJugador = (tablero.getJugadorTurno() == id);

    if (mueveNuestroJugador) {
        // Nodo MAX: nuestro agente quiere maximizar la puntuación.
        double mejorValor = MenosInfinito;
        std::pair<int,int> mejorMov = sucesores[0].second;

        for (const auto& sucesor : sucesores) {
            std::pair<int,int> movHijo;

            double valor = minimax(sucesor.first, profundidad + 1, prof_Max, movHijo);

            if (valor > mejorValor) {
                mejorValor = valor;
                mejorMov = sucesor.second;
            }
        }

        Mov = mejorMov;
        return mejorValor;
    }
    else {
        // Nodo MIN: el rival intenta minimizar nuestra puntuación.
        double mejorValor = MasInfinito;
        std::pair<int,int> mejorMov = sucesores[0].second;

        for (const auto& sucesor : sucesores) {
            std::pair<int,int> movHijo;

            double valor = minimax(sucesor.first, profundidad + 1, prof_Max, movHijo);

            if (valor < mejorValor) {
                mejorValor = valor;
                mejorMov = sucesor.second;
            }
        }

        Mov = mejorMov;
        return mejorValor;
    }
}


/**
 * @brief Punto de entrada para el juego inteligente.
 * @param tablero Estado actual del juego.
 * @return La jugada elegida por el algoritmo de búsqueda.
 */
pair<int, int> AgenteEstudiante::JuegaInteligente(const Tablero& tablero) {
    pair<int,int> Mov;

    double valor = alfaBeta(tablero, 0, profundidadMax, MenosInfinito, MasInfinito, Mov);
    cout << "Valor Minimax: " << valor << "\tJugada: (" << Mov.first << ", " << Mov.second << ")\n";
    return Mov;
}




/**
 * @brief Implementación del algoritmo Minimax con Poda Alfa-Beta.
 * @param tablero Estado actual.
 * @param profundidad Nivel actual en el árbol de búsqueda.
 * @param prof_Max Límite de profundidad de la búsqueda.
 * @param alfa Valor mínimo garantizado para el jugador MAX.
 * @param beta Valor máximo garantizado para el jugador MIN.
 * @param Mov [Salida] La mejor jugada encontrada en la raíz.
 * @return Valor heurístico del estado tras la poda.
 */
double AgenteEstudiante::alfaBeta(const Tablero &tablero, int profundidad, int prof_Max, double alfa, double beta, std::pair<int,int> &Mov) {
    /* ============== Este trozo de código se tiene que quedar aquí  =============== */
    nodosVisitados++;
    if (abortarBanda) return 0;
    
    if (std::chrono::duration<double>(std::chrono::steady_clock::now() - inicioBusqueda).count() > tiempoMaxSegundos) {
        abortarBanda = true;
        return 0;
    }
    /* ============== Empieza a partir de aquí tu implementación  =============== */

    Mov = {-1, -1};

    int oponente = (id == 1) ? 2 : 1;

    // 1. Comprobar si el tablero actual ya es terminal.
    Tablero copia = tablero;
    int ganador = copia.comprobarGanador();

    if (ganador == id) {
        return GANAR - profundidad;
    }

    if (ganador == oponente) {
        return PERDER + profundidad;
    }

    if (ganador == -1) {
        return 0;
    }

    // 2. Si llegamos a la profundidad máxima, usamos la heurística.
    if (profundidad >= prof_Max) {
        return heuristica(tablero);
    }

    // 3. Generar sucesores.
    auto sucesores = tablero.getSucesoresConMovimientos();

    if (sucesores.empty()) {
        return heuristica(tablero);
    }

    bool mueveNuestroJugador = (tablero.getJugadorTurno() == id);

    // Ordenación de sucesores para mejorar la poda Alfa-Beta.
    // Si mueve nuestro jugador, interesan primero los tableros con mayor heurística.
    // Si mueve el rival, interesan primero los tableros con menor heurística.
    std::sort(sucesores.begin(), sucesores.end(),
        [&](const auto& a, const auto& b) {
            double valorA = heuristica(a.first);
            double valorB = heuristica(b.first);

            if (mueveNuestroJugador) {
                return valorA > valorB;
            }
            else {
                return valorA < valorB;
            }
        }
    );

    if (mueveNuestroJugador) {
        // Nodo MAX: nuestro agente intenta maximizar.
        double mejorValor = MenosInfinito;
        std::pair<int,int> mejorMov = sucesores[0].second;

        for (const auto& sucesor : sucesores) {
            std::pair<int,int> movHijo;

            double valor = alfaBeta(
                sucesor.first,
                profundidad + 1,
                prof_Max,
                alfa,
                beta,
                movHijo
            );

            if (valor > mejorValor) {
                mejorValor = valor;
                mejorMov = sucesor.second;
            }

            alfa = std::max(alfa, mejorValor);

            if (alfa >= beta) {
                break;
            }
        }

        Mov = mejorMov;
        return mejorValor;
    }
    else {
        // Nodo MIN: el rival intenta minimizar nuestra puntuación.
        double mejorValor = MasInfinito;
        std::pair<int,int> mejorMov = sucesores[0].second;

        for (const auto& sucesor : sucesores) {
            std::pair<int,int> movHijo;

            double valor = alfaBeta(
                sucesor.first,
                profundidad + 1,
                prof_Max,
                alfa,
                beta,
                movHijo
            );

            if (valor < mejorValor) {
                mejorValor = valor;
                mejorMov = sucesor.second;
            }

            beta = std::min(beta, mejorValor);

            if (alfa >= beta) {
                break;
            }
        }

        Mov = mejorMov;
        return mejorValor;
    }
}

/**
 * @brief Función heurística para evaluar la calidad de un tablero.
 * @param tablero Estado a evaluar.
 * @return Puntuación numérica (positiva para ventaja de J1, negativa para J2).
 */
double AgenteEstudiante::heuristica(const Tablero& tablero) {
    switch(numHeuristica) {
        case 0: return heuristicaPrueba(tablero);
                break;
        case 1: return heuristica1(tablero);
                break;
        case 2: return heuristica2(tablero);
                break;
        default: return heuristica1(tablero);
    }
}

double AgenteEstudiante::heuristicaPrueba(const Tablero& tablero) {
    // n es el número de fichas en línea para ganar.
    int n = tablero.getNParaGanar();
    int oponente = (id == 1) ? 2 : 1;
    double score_positivo = 0;

    double score_negativo = 0;

    for (int f=0; f< tablero.getFilas(); f++ ){
        for (int c = 0; c< tablero.getColumnas(); c++){
            if (tablero.getCelda(f,c) != 0 ){
                int valor = tablero.getFilas()-abs(f-(tablero.getFilas()/2)) + tablero.getColumnas()-abs(c-(tablero.getColumnas()/2)); 
                if (tablero.getCelda(f,c) == id){
                  score_positivo += valor;
                 }
                else {
                  score_negativo += valor;
                }
            }
        }
    }

   
    return score_positivo - score_negativo;
}


double AgenteEstudiante::heuristica1(const Tablero& tablero) {
    int filas = tablero.getFilas();
    int columnas = tablero.getColumnas();
    int n = tablero.getNParaGanar();
    int oponente = (id == 1) ? 2 : 1;

    // 1. Comprobación de estados terminales.
    Tablero copia = tablero;
    int ganador = copia.comprobarGanador();

    if (ganador == id) {
        return GANAR;
    }

    if (ganador == oponente) {
        return PERDER;
    }

    if (ganador == -1) {
        return 0;
    }

    double score = 0.0;

    // 2. Pequeño bonus por ocupar zonas centrales.
    // En juegos de alineación, el centro suele ser más valioso porque participa
    // en más líneas horizontales, verticales y diagonales.
    int centroF = filas / 2;
    int centroC = columnas / 2;

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            int celda = tablero.getCelda(f, c);

            if (celda != 0) {
                int valorCentro = (filas - std::abs(f - centroF)) + 
                                  (columnas - std::abs(c - centroC));

                if (celda == id) {
                    score += 3.0 * valorCentro;
                }
                else if (celda == oponente) {
                    score -= 3.0 * valorCentro;
                }
            }
        }
    }

    // 3. Función auxiliar para puntuar una ventana de n casillas.
    auto evaluarVentana = [&](int propias, int rivales) -> double {
        // Si hay fichas de ambos jugadores, esa línea está bloqueada.
        if (propias > 0 && rivales > 0) {
            return 0.0;
        }

        // Línea vacía: no aporta información.
        if (propias == 0 && rivales == 0) {
            return 0.0;
        }

        // Línea favorable a nuestro jugador.
        if (propias > 0) {
            if (propias >= n) {
                return GANAR / 10.0;
            }

            if (propias == n - 1) {
                return 200000.0;
            }

            if (propias == n - 2) {
                return 10000.0;
            }

            if (propias == n - 3) {
                return 500.0;
            }

            return 20.0 * propias;
        }

        // Línea favorable al rival.
        if (rivales > 0) {
            if (rivales >= n) {
                return PERDER / 10.0;
            }

            if (rivales == n - 1) {
                return -250000.0;
            }

            if (rivales == n - 2) {
                return -15000.0;
            }

            if (rivales == n - 3) {
                return -700.0;
            }

            return -25.0 * rivales;
        }

        return 0.0;
    };

    // 4. Direcciones que vamos a analizar:
    // horizontal, vertical, diagonal descendente y diagonal ascendente.
    const int df[4] = {0, 1, 1, -1};
    const int dc[4] = {1, 0, 1, 1};

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            for (int dir = 0; dir < 4; dir++) {
                int finF = f + (n - 1) * df[dir];
                int finC = c + (n - 1) * dc[dir];

                // Comprobamos que la ventana cabe dentro del tablero.
                if (finF < 0 || finF >= filas || finC < 0 || finC >= columnas) {
                    continue;
                }

                int propias = 0;
                int rivales = 0;

                for (int k = 0; k < n; k++) {
                    int nf = f + k * df[dir];
                    int nc = c + k * dc[dir];

                    int celda = tablero.getCelda(nf, nc);

                    if (celda == id) {
                        propias++;
                    }
                    else if (celda == oponente) {
                        rivales++;
                    }
                }

                score += evaluarVentana(propias, rivales);
            }
        }
    }

    return score;
}

double AgenteEstudiante::heuristica2(const Tablero& tablero) {
    int n = tablero.getNParaGanar();
    int oponente = (id == 1) ? 2 : 1;

    // Comprobación de estados terminales.
    Tablero copia = tablero;
    int ganador = copia.comprobarGanador();

    if (ganador == id) {
        return GANAR;
    }

    if (ganador == oponente) {
        return PERDER;
    }

    if (ganador == -1) {
        return 0;
    }

    double score = 0.0;

    // Valoramos combinaciones propias y del rival.
    // Cuanto más largas sean las líneas, más peso tienen.
    for (int longitud = 1; longitud <= n; longitud++) {
        int propias = tablero.contarCombinaciones(longitud, id);
        int rivales = tablero.contarCombinaciones(longitud, oponente);

        double peso = std::pow(10.0, longitud);

        score += peso * propias;
        score -= peso * 1.25 * rivales;
    }

    // Pequeño bonus por control del centro.
    int filas = tablero.getFilas();
    int columnas = tablero.getColumnas();
    int centroF = filas / 2;
    int centroC = columnas / 2;

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            int celda = tablero.getCelda(f, c);

            if (celda != 0) {
                int distancia = std::abs(f - centroF) + std::abs(c - centroC);
                double valorCentro = 10.0 - distancia;

                if (celda == id) {
                    score += valorCentro;
                }
                else if (celda == oponente) {
                    score -= valorCentro;
                }
            }
        }
    }

    return score;
}

