#include "tecnico.hpp"
#include "motorlib/util.h"
#include <iostream>
#include <queue>
#include <set>

#include <map>
#include <list>
#include <cmath>

using namespace std;

// =========================================================================
// ÁREA DE IMPLEMENTACIÓN DEL ESTUDIANTE
// =========================================================================

Action ComportamientoTecnico::think(Sensores sensores) {
  Action accion = IDLE;


  // Decisión del agente según el nivel
  switch (sensores.nivel) {
    case 0: accion = ComportamientoTecnicoNivel_0(sensores); break;
    case 1: accion = ComportamientoTecnicoNivel_1(sensores); break;
    case 2: accion = ComportamientoTecnicoNivel_2(sensores); break;
    case 3: accion = ComportamientoTecnicoNivel_3(sensores); break;
    case 4: accion = ComportamientoTecnicoNivel_4(sensores); break;
    case 5: accion = ComportamientoTecnicoNivel_5(sensores); break;
    case 6: accion = ComportamientoTecnicoNivel_6(sensores); break;
  }

  return accion;
}


/**
 * @brief Determina la mejor casilla interesante para el Técnico.
 * Devuelve:
 * 2 -> avanzar
 * 1 -> girar izquierda
 * 3 -> girar derecha
 * 0 -> no hay opción interesante
 */
int VeoCasillaInteresanteT(char i, char c, char d)
{
  // Primero, prioridad absoluta: llegar a U
  if (c == 'U') return 2;
  else if (i == 'U') return 1;
  else if (d == 'U') return 3;

  // Después puede coger zapatillas, aunque en nivel 0 no le mejoran la altura
  if (c == 'D') return 2;
  else if (i == 'D') return 1;
  else if (d == 'D') return 3;

  // Después seguir camino
  if (c == 'C') return 2;
  else if (i == 'C') return 1;
  else if (d == 'C') return 3;

  return 0;
}

/**
 * @brief Filtra una casilla según si es viable por altura para el Técnico.
 * El Técnico solo permite desnivel máximo 1.
 */
char ViablePorAlturaT(char casilla, int dif)
{
  if (abs(dif) <= 1)
    return casilla;
  else
    return 'P';
}

// Niveles del técnico
Action ComportamientoTecnico::ComportamientoTecnicoNivel_0(Sensores sensores)
{
  Action accion = IDLE;

  // 1. Actualización del mapa conocido
  ActualizarMapa(sensores);

  if (giros_pendientes > 0)
  {
    giros_pendientes--;
    last_action = TURN_SL;
    return TURN_SL;
  }

  // 2. Actualización de variables de estado
  if (sensores.superficie[0] == 'D')
  {
    tiene_zapatillas = true;
  }

  // 3. Si ya ha llegado a una planta de tratamiento, se queda quieto
  if (sensores.superficie[0] == 'U')
  {
    accion = IDLE;
  }
  else
  {
    // 4. Filtramos las tres casillas cercanas por altura
    char i = ViablePorAlturaT(
        sensores.superficie[1],
        sensores.cota[1] - sensores.cota[0]);

    char c = ViablePorAlturaT(
        sensores.superficie[2],
        sensores.cota[2] - sensores.cota[0]);

    char d = ViablePorAlturaT(
        sensores.superficie[3],
        sensores.cota[3] - sensores.cota[0]);

    // 5. Evitamos avanzar si hay otro agente justo delante
    
    // Si tengo otro agente delante, espero.
    // El Ingeniero se encargará de darse la vuelta y liberar el paso.
    if (sensores.agentes[2] != '_')
    {
      accion = IDLE;
      last_action = accion;
      return accion;
    }

    // 6. Elegimos la mejor casilla interesante
    int pos = VeoCasillaInteresanteT(i, c, d);

    switch (pos)
    {
    case 2:
      accion = WALK;
      break;
    case 1:
      accion = TURN_SL;
      break;
    case 3:
      accion = TURN_SR;
      break;
    default:
      accion = TURN_SR;
      break;
    }
  }

  last_action = accion;
  return accion;
}

/**
 * @brief Comprueba si una celda es de tipo camino transitable.
 * @param c Carácter que representa el tipo de superficie.
 * @return true si es camino ('C'), zapatillas ('D') o meta ('U').
 */
bool ComportamientoTecnico::es_camino(unsigned char c) const {
  return (c == 'C' || c == 'D' || c == 'U');
}



bool EsTransitableNivel1T(char casilla)
{
  return casilla == 'C' || casilla == 'S' || casilla == 'D' || casilla == 'U';
}

int VeoCasillaInteresanteNivel1T(char i, char c, char d)
{
  // Prioridad: avanzar si se puede
  if (c == 'C' || c == 'S' || c == 'D' || c == 'U')
    return 2;

  // Técnico prioriza derecha para separarse del Ingeniero
  if (d == 'C' || d == 'S' || d == 'D' || d == 'U')
    return 3;

  if (i == 'C' || i == 'S' || i == 'D' || i == 'U')
    return 1;

  return 0;
}

/**
 * @brief Comportamiento reactivo del técnico para el Nivel 1.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */Action ComportamientoTecnico::ComportamientoTecnicoNivel_1(Sensores sensores)
{
  Action accion = IDLE;

  ActualizarMapa(sensores);

  if (sensores.superficie[0] == 'D')
  {
    tiene_zapatillas = true;
  }

  if (visitadas_n1.empty())
  {
    visitadas_n1 = vector<vector<int>>(
        mapaResultado.size(),
        vector<int>(mapaResultado[0].size(), 0));
  }

  visitadas_n1[sensores.posF][sensores.posC]++;

  auto esValidaN1 = [](char casilla) -> bool
  {
    return casilla == 'C' || casilla == 'S' || casilla == 'D' || casilla == 'U';
  };

  char i = ViablePorAlturaT(
      sensores.superficie[1],
      sensores.cota[1] - sensores.cota[0]);

  char c = ViablePorAlturaT(
      sensores.superficie[2],
      sensores.cota[2] - sensores.cota[0]);

  char d = ViablePorAlturaT(
      sensores.superficie[3],
      sensores.cota[3] - sensores.cota[0]);

  if (sensores.agentes[1] != '_') i = 'P';
  if (sensores.agentes[2] != '_') c = 'P';
  if (sensores.agentes[3] != '_') d = 'P';

  ubicacion actual;
  actual.f = sensores.posF;
  actual.c = sensores.posC;
  actual.brujula = sensores.rumbo;

  auto posicionTrasGiro = [&](int giro) -> ubicacion
  {
    ubicacion aux = actual;
    aux.brujula = static_cast<Orientacion>(((int)sensores.rumbo + giro + 8) % 8);
    return Delante(aux);
  };

  auto dentroMapa = [&](const ubicacion &u) -> bool
  {
    return u.f >= 0 && u.f < mapaResultado.size() &&
           u.c >= 0 && u.c < mapaResultado[0].size();
  };

  auto cuentaDesconocidas = [&](const ubicacion &u) -> int
  {
    int total = 0;

    for (int df = -3; df <= 3; df++)
    {
      for (int dc = -3; dc <= 3; dc++)
      {
        int nf = u.f + df;
        int nc = u.c + dc;

        if (nf >= 0 && nf < mapaResultado.size() &&
            nc >= 0 && nc < mapaResultado[0].size())
        {
          if (mapaResultado[nf][nc] == '?')
          {
            total++;
          }
        }
      }
    }

    return total;
  };

  ubicacion delante = posicionTrasGiro(0);
  ubicacion izquierda = posicionTrasGiro(-1);
  ubicacion derecha = posicionTrasGiro(1);

  bool centroValido = esValidaN1(c) && dentroMapa(delante);
  bool izquierdaValida = esValidaN1(i) && dentroMapa(izquierda);
  bool derechaValida = esValidaN1(d) && dentroMapa(derecha);

  // Si acaba de girar y ahora puede avanzar, avanza.
  if ((last_action == TURN_SL || last_action == TURN_SR) && centroValido)
  {
    accion = WALK;
    last_action = accion;
    return accion;
  }

  int mejorPuntuacion = -999999;
  Action mejorAccion = IDLE;

  if (centroValido)
  {
    int puntuacion = cuentaDesconocidas(delante) * 10
                     - visitadas_n1[delante.f][delante.c] * 3
                     + 2;

    if (puntuacion > mejorPuntuacion)
    {
      mejorPuntuacion = puntuacion;
      mejorAccion = WALK;
    }
  }

  // El Técnico revisa primero derecha para separarse más del Ingeniero
  if (derechaValida)
  {
    int puntuacion = cuentaDesconocidas(derecha) * 10
                     - visitadas_n1[derecha.f][derecha.c] * 3;

    if (puntuacion > mejorPuntuacion)
    {
      mejorPuntuacion = puntuacion;
      mejorAccion = TURN_SR;
    }
  }

  if (izquierdaValida)
  {
    int puntuacion = cuentaDesconocidas(izquierda) * 10
                     - visitadas_n1[izquierda.f][izquierda.c] * 3;

    if (puntuacion > mejorPuntuacion)
    {
      mejorPuntuacion = puntuacion;
      mejorAccion = TURN_SL;
    }
  }

  if (mejorAccion != IDLE)
  {
    accion = mejorAccion;
  }
  else
  {
    accion = TURN_SR;
  }

  last_action = accion;
  return accion;
}

/**
 * @brief Comportamiento del técnico para el Nivel 2.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_2(Sensores sensores)
{
  return IDLE;
}


struct EstadoN3
{
  int f;
  int c;
  int brujula;
  bool zapatillas;

  bool operator<(const EstadoN3 &otro) const
  {
    if (f != otro.f) return f < otro.f;
    if (c != otro.c) return c < otro.c;
    if (brujula != otro.brujula) return brujula < otro.brujula;
    return zapatillas < otro.zapatillas;
  }
};

struct NodoN3
{
  EstadoN3 estado;
  list<Action> plan;
  int coste;
  int prioridad;
};

struct ComparadorNodoN3
{
  bool operator()(const NodoN3 &a, const NodoN3 &b) const
  {
    return a.prioridad > b.prioridad;
  }
};

list<Action> BuscarPlanTecnicoHasta(
    int origenF,
    int origenC,
    int origenRumbo,
    bool tieneZapatillas,
    int destinoF,
    int destinoC,
    const vector<vector<unsigned char>> &mapaResultado,
    const vector<vector<unsigned char>> &mapaCotas)
{
  auto dentroMapa = [&](int f, int c) -> bool
  {
    return f >= 0 && f < mapaResultado.size() &&
           c >= 0 && c < mapaResultado[0].size();
  };

  auto transitableTecnico = [&](int f, int c, bool zap) -> bool
  {
    if (!dentroMapa(f, c)) return false;

    unsigned char casilla = mapaResultado[f][c];

    if (casilla == 'P' || casilla == 'M')
      return false;

    if (casilla == 'B' && !zap)
      return false;

    return true;
  };

  auto siguienteCasilla = [&](int f, int c, int brujula) -> pair<int, int>
  {
    switch (brujula)
    {
    case 0: return {f - 1, c};
    case 1: return {f - 1, c + 1};
    case 2: return {f, c + 1};
    case 3: return {f + 1, c + 1};
    case 4: return {f + 1, c};
    case 5: return {f + 1, c - 1};
    case 6: return {f, c - 1};
    case 7: return {f - 1, c - 1};
    default: return {f, c};
    }
  };

  auto alturaValidaTecnico = [&](int f1, int c1, int f2, int c2) -> bool
  {
    if (!dentroMapa(f1, c1) || !dentroMapa(f2, c2)) return false;

    int dif = abs((int)mapaCotas[f2][c2] - (int)mapaCotas[f1][c1]);

    return dif <= 1;
  };

  queue<NodoN3> abiertos;
  set<EstadoN3> cerrados;

  EstadoN3 inicial;
  inicial.f = origenF;
  inicial.c = origenC;
  inicial.brujula = origenRumbo;
  inicial.zapatillas = tieneZapatillas;

  NodoN3 nodoInicial;
  nodoInicial.estado = inicial;
  nodoInicial.plan.clear();
  nodoInicial.coste = 0;
  nodoInicial.prioridad = 0;

  abiertos.push(nodoInicial);
  cerrados.insert(inicial);

  while (!abiertos.empty())
  {
    NodoN3 actual = abiertos.front();
    abiertos.pop();

    EstadoN3 st = actual.estado;

    if (st.f == destinoF && st.c == destinoC)
    {
      return actual.plan;
    }

    // TURN_SL
    {
      EstadoN3 hijo = st;
      hijo.brujula = (hijo.brujula + 7) % 8;

      if (cerrados.find(hijo) == cerrados.end())
      {
        NodoN3 nuevo;
        nuevo.estado = hijo;
        nuevo.plan = actual.plan;
        nuevo.plan.push_back(TURN_SL);
        nuevo.coste = 0;
        nuevo.prioridad = 0;

        abiertos.push(nuevo);
        cerrados.insert(hijo);
      }
    }

    // TURN_SR
    {
      EstadoN3 hijo = st;
      hijo.brujula = (hijo.brujula + 1) % 8;

      if (cerrados.find(hijo) == cerrados.end())
      {
        NodoN3 nuevo;
        nuevo.estado = hijo;
        nuevo.plan = actual.plan;
        nuevo.plan.push_back(TURN_SR);
        nuevo.coste = 0;
        nuevo.prioridad = 0;

        abiertos.push(nuevo);
        cerrados.insert(hijo);
      }
    }

    // WALK
    {
      pair<int, int> sig = siguienteCasilla(st.f, st.c, st.brujula);
      int nf = sig.first;
      int nc = sig.second;

      if (transitableTecnico(nf, nc, st.zapatillas) &&
          alturaValidaTecnico(st.f, st.c, nf, nc))
      {
        EstadoN3 hijo = st;
        hijo.f = nf;
        hijo.c = nc;

        if (mapaResultado[nf][nc] == 'D')
          hijo.zapatillas = true;

        if (cerrados.find(hijo) == cerrados.end())
        {
          NodoN3 nuevo;
          nuevo.estado = hijo;
          nuevo.plan = actual.plan;
          nuevo.plan.push_back(WALK);
          nuevo.coste = 0;
          nuevo.prioridad = 0;

          abiertos.push(nuevo);
          cerrados.insert(hijo);
        }
      }
    }
  }

  return list<Action>();
}

/**
 * @brief Comportamiento del técnico para el Nivel 3.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_3(Sensores sensores)
{
  // Si ya estoy en la Belkanita, paro
  if (sensores.posF == sensores.BelPosF && sensores.posC == sensores.BelPosC)
  {
    return IDLE;
  }

  // Si ya tengo un plan, ejecuto la siguiente acción
  if (!plan_n3.empty())
  {
    Action sig = plan_n3.front();
    plan_n3.pop_front();
    last_action = sig;
    return sig;
  }

  // Si ya intenté calcular y no encontré plan, no recalculo todo el rato
  if (plan_n3_calculado)
  {
    return IDLE;
  }

  plan_n3_calculado = true;

  // ============================================================
  // Funciones auxiliares locales
  // ============================================================

  auto dentroMapa = [&](int f, int c) -> bool
  {
    return f >= 0 && f < mapaResultado.size() &&
           c >= 0 && c < mapaResultado[0].size();
  };

  auto transitableTecnico = [&](int f, int c, bool zap) -> bool
  {
    if (!dentroMapa(f, c)) return false;

    unsigned char casilla = mapaResultado[f][c];

    // Precipicio y muro nunca son transitables
    if (casilla == 'P' || casilla == 'M')
      return false;

    // El bosque solo es transitable para el Técnico con zapatillas
    if (casilla == 'B' && !zap)
      return false;

    return true;
  };

  auto siguienteCasilla = [&](int f, int c, int brujula) -> pair<int, int>
  {
    switch (brujula)
    {
    case 0: return {f - 1, c};     // norte
    case 1: return {f - 1, c + 1}; // noreste
    case 2: return {f, c + 1};     // este
    case 3: return {f + 1, c + 1}; // sureste
    case 4: return {f + 1, c};     // sur
    case 5: return {f + 1, c - 1}; // suroeste
    case 6: return {f, c - 1};     // oeste
    case 7: return {f - 1, c - 1}; // noroeste
    default: return {f, c};
    }
  };

  auto alturaValidaTecnico = [&](int f1, int c1, int f2, int c2) -> bool
  {
    if (!dentroMapa(f1, c1) || !dentroMapa(f2, c2)) return false;

    int dif = abs((int)mapaCotas[f2][c2] - (int)mapaCotas[f1][c1]);

    // El Técnico solo tolera desnivel máximo 1
    return dif <= 1;
  };

  auto costeGiroTecnico = [&](int f, int c) -> int
  {
    unsigned char casilla = mapaResultado[f][c];

    if (casilla == 'A') return 5;
    if (casilla == 'H') return 2;
    if (casilla == 'S') return 1;

    // Camino, U, D, X, bosque con zapatillas, etc.
    return 1;
  };

  auto costeWalkTecnico = [&](int f1, int c1, int f2, int c2) -> int
  {
    unsigned char casillaOrigen = mapaResultado[f1][c1];
    int base = 1;

    if (casillaOrigen == 'A')
      base = 60;
    else if (casillaOrigen == 'H')
      base = 6;
    else if (casillaOrigen == 'S')
      base = 3;
    else
      base = 1;

    int dif = (int)mapaCotas[f2][c2] - (int)mapaCotas[f1][c1];

    // Según tabla: A/H/S aplican +5 al subir y -2 al bajar.
    // Resto de casillas no tienen incremento/decremento.
    if (casillaOrigen == 'A' || casillaOrigen == 'H' || casillaOrigen == 'S')
    {
      if (dif > 0)
        base += 5;
      else if (dif < 0)
        base -= 2;
    }

    if (base < 1)
      base = 1;

    return base;
  };

  auto heuristica = [&](int f, int c) -> int
  {
    int df = abs(f - sensores.BelPosF);
    int dc = abs(c - sensores.BelPosC);

    // Como puede moverse en 8 direcciones, usamos distancia tipo tablero de ajedrez.
    // Es admisible si el coste mínimo por avance es 1.
    return max(df, dc);
  };

  // ============================================================
  // A*
  // ============================================================

  priority_queue<NodoN3, vector<NodoN3>, ComparadorNodoN3> abiertos;
  map<EstadoN3, int> mejorCoste;

  EstadoN3 inicial;
  inicial.f = sensores.posF;
  inicial.c = sensores.posC;
  inicial.brujula = (int)sensores.rumbo;
  inicial.zapatillas = tiene_zapatillas || sensores.superficie[0] == 'D';

  NodoN3 nodoInicial;
  nodoInicial.estado = inicial;
  nodoInicial.plan.clear();
  nodoInicial.coste = 0;
  nodoInicial.prioridad = heuristica(inicial.f, inicial.c);

  abiertos.push(nodoInicial);
  mejorCoste[inicial] = 0;

  bool encontrado = false;
  list<Action> mejorPlan;

  while (!abiertos.empty() && !encontrado)
  {
    NodoN3 actual = abiertos.top();
    abiertos.pop();

    EstadoN3 st = actual.estado;

    // Si este nodo ya está superado por otro más barato, lo ignoramos
    if (mejorCoste[st] < actual.coste)
      continue;

    // Objetivo
    if (st.f == sensores.BelPosF && st.c == sensores.BelPosC)
    {
      encontrado = true;
      mejorPlan = actual.plan;
      break;
    }

    // ------------------------------------------------------------
    // TURN_SL
    // ------------------------------------------------------------
    {
      EstadoN3 hijo = st;
      hijo.brujula = (hijo.brujula + 7) % 8;

      int nuevoCoste = actual.coste + costeGiroTecnico(st.f, st.c);

      if (mejorCoste.find(hijo) == mejorCoste.end() ||
          nuevoCoste < mejorCoste[hijo])
      {
        NodoN3 nuevo;
        nuevo.estado = hijo;
        nuevo.plan = actual.plan;
        nuevo.plan.push_back(TURN_SL);
        nuevo.coste = nuevoCoste;
        nuevo.prioridad = nuevoCoste + heuristica(hijo.f, hijo.c);

        abiertos.push(nuevo);
        mejorCoste[hijo] = nuevoCoste;
      }
    }

    // ------------------------------------------------------------
    // TURN_SR
    // ------------------------------------------------------------
    {
      EstadoN3 hijo = st;
      hijo.brujula = (hijo.brujula + 1) % 8;

      int nuevoCoste = actual.coste + costeGiroTecnico(st.f, st.c);

      if (mejorCoste.find(hijo) == mejorCoste.end() ||
          nuevoCoste < mejorCoste[hijo])
      {
        NodoN3 nuevo;
        nuevo.estado = hijo;
        nuevo.plan = actual.plan;
        nuevo.plan.push_back(TURN_SR);
        nuevo.coste = nuevoCoste;
        nuevo.prioridad = nuevoCoste + heuristica(hijo.f, hijo.c);

        abiertos.push(nuevo);
        mejorCoste[hijo] = nuevoCoste;
      }
    }

    // ------------------------------------------------------------
    // WALK
    // ------------------------------------------------------------
    {
      pair<int, int> sig = siguienteCasilla(st.f, st.c, st.brujula);
      int nf = sig.first;
      int nc = sig.second;

      if (transitableTecnico(nf, nc, st.zapatillas) &&
          alturaValidaTecnico(st.f, st.c, nf, nc))
      {
        EstadoN3 hijo = st;
        hijo.f = nf;
        hijo.c = nc;

        if (mapaResultado[nf][nc] == 'D')
          hijo.zapatillas = true;

        int nuevoCoste = actual.coste + costeWalkTecnico(st.f, st.c, nf, nc);

        if (mejorCoste.find(hijo) == mejorCoste.end() ||
            nuevoCoste < mejorCoste[hijo])
        {
          NodoN3 nuevo;
          nuevo.estado = hijo;
          nuevo.plan = actual.plan;
          nuevo.plan.push_back(WALK);
          nuevo.coste = nuevoCoste;
          nuevo.prioridad = nuevoCoste + heuristica(hijo.f, hijo.c);

          abiertos.push(nuevo);
          mejorCoste[hijo] = nuevoCoste;
        }
      }
    }
  }

  if (encontrado)
  {
    plan_n3 = mejorPlan;

    cout << "Plan Nivel 3 encontrado: ";
    PintaPlan(plan_n3);

    VisualizaPlan({sensores.posF, sensores.posC, sensores.rumbo}, plan_n3);

    if (!plan_n3.empty())
    {
      Action sig = plan_n3.front();
      plan_n3.pop_front();
      last_action = sig;
      return sig;
    }
  }

  return IDLE;
}

/**
 * @brief Comportamiento del técnico para el Nivel 4.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_4(Sensores sensores) {
  return IDLE;
}



struct NodoTubTech
{
  int f;
  int c;
  int alturaAjustada;
  int impacto;
  int longitud;
  list<Paso> plan;
};

struct ComparadorNodoTubTech
{
  bool operator()(const NodoTubTech &a, const NodoTubTech &b) const
  {
    if (a.longitud != b.longitud)
      return a.longitud > b.longitud;

    return a.impacto > b.impacto;
  }
};

struct ClaveTubTech
{
  int f;
  int c;
  int alturaAjustada;

  bool operator<(const ClaveTubTech &otra) const
  {
    if (f != otra.f) return f < otra.f;
    if (c != otra.c) return c < otra.c;
    return alturaAjustada < otra.alturaAjustada;
  }
};

bool DentroMapaTubTech(int f, int c, const vector<vector<unsigned char>> &mapa)
{
  return f >= 0 && f < mapa.size() && c >= 0 && c < mapa[0].size();
}

bool TransitableTuberiaTech(char casilla)
{
  return casilla != 'P' && casilla != 'M';
}

bool OperacionPermitidaTubTech(char casilla, int op)
{
  if (casilla == 'P' || casilla == 'M')
    return false;

  if (casilla == 'A' && op != 0)
    return false;

  return true;
}

int ImpactoInstallTubTech(char casilla)
{
  if (casilla == 'A') return 50;
  if (casilla == 'H') return 45;
  if (casilla == 'S') return 25;
  if (casilla == 'C' || casilla == 'U') return 15;

  return 30;
}

int ImpactoOperacionTubTech(char casilla, int op)
{
  if (op == 0)
    return 0;

  if (op == 1)
  {
    if (casilla == 'H') return 55;
    if (casilla == 'S') return 30;
    if (casilla == 'C' || casilla == 'U') return 10;

    return 40;
  }

  if (op == -1)
  {
    if (casilla == 'H') return 65;
    if (casilla == 'S') return 40;
    if (casilla == 'C' || casilla == 'U') return 25;

    return 50;
  }

  return 999999;
}

int ImpactoPasoTubTech(char casilla, int op)
{
  return ImpactoInstallTubTech(casilla) + ImpactoOperacionTubTech(casilla, op);
}

list<Paso> CalcularPlanTuberiasTech(
    int origenF,
    int origenC,
    const vector<vector<unsigned char>> &mapaResultado,
    const vector<vector<unsigned char>> &mapaCotas)
{
  const int IMPACTO_MAXIMO = 1000;

  list<Paso> planVacio;

  if (!DentroMapaTubTech(origenF, origenC, mapaResultado))
    return planVacio;

  priority_queue<NodoTubTech, vector<NodoTubTech>, ComparadorNodoTubTech> abiertos;
  map<ClaveTubTech, int> mejorImpacto;

  for (int opInicial = -1; opInicial <= 1; opInicial++)
  {
    char casillaOrigen = mapaResultado[origenF][origenC];

    if (!OperacionPermitidaTubTech(casillaOrigen, opInicial))
      continue;

    int impactoInicial = ImpactoPasoTubTech(casillaOrigen, opInicial);

    if (impactoInicial > IMPACTO_MAXIMO)
      continue;

    NodoTubTech inicial;
    inicial.f = origenF;
    inicial.c = origenC;
    inicial.alturaAjustada = mapaCotas[origenF][origenC] + opInicial;
    inicial.impacto = impactoInicial;
    inicial.longitud = 1;
    inicial.plan.clear();
    inicial.plan.push_back({origenF, origenC, opInicial});

    abiertos.push(inicial);

    ClaveTubTech clave{origenF, origenC, inicial.alturaAjustada};
    mejorImpacto[clave] = impactoInicial;
  }

  int df[4] = {-1, 1, 0, 0};
  int dc[4] = {0, 0, -1, 1};

  while (!abiertos.empty())
  {
    NodoTubTech actual = abiertos.top();
    abiertos.pop();

    ClaveTubTech claveActual{actual.f, actual.c, actual.alturaAjustada};

    if (mejorImpacto.find(claveActual) != mejorImpacto.end() &&
        actual.impacto > mejorImpacto[claveActual])
    {
      continue;
    }

    if (mapaResultado[actual.f][actual.c] == 'U' &&
        !(actual.f == origenF && actual.c == origenC))
    {
      return actual.plan;
    }

    for (int k = 0; k < 4; k++)
    {
      int nf = actual.f + df[k];
      int nc = actual.c + dc[k];

      if (!DentroMapaTubTech(nf, nc, mapaResultado))
        continue;

      char casilla = mapaResultado[nf][nc];

      if (!TransitableTuberiaTech(casilla))
        continue;

      int alturaOriginal = mapaCotas[nf][nc];

      for (int op = -1; op <= 1; op++)
      {
        if (!OperacionPermitidaTubTech(casilla, op))
          continue;

        int alturaNueva = alturaOriginal + op;
        int diferencia = actual.alturaAjustada - alturaNueva;

        if (!(diferencia == 0 || diferencia == 1))
          continue;

        int impactoPaso = ImpactoPasoTubTech(casilla, op);
        int nuevoImpacto = actual.impacto + impactoPaso;

        if (nuevoImpacto > IMPACTO_MAXIMO)
          continue;

        NodoTubTech hijo;
        hijo.f = nf;
        hijo.c = nc;
        hijo.alturaAjustada = alturaNueva;
        hijo.impacto = nuevoImpacto;
        hijo.longitud = actual.longitud + 1;
        hijo.plan = actual.plan;
        hijo.plan.push_back({nf, nc, op});

        ClaveTubTech claveHijo{nf, nc, alturaNueva};

        if (mejorImpacto.find(claveHijo) == mejorImpacto.end() ||
            nuevoImpacto < mejorImpacto[claveHijo])
        {
          mejorImpacto[claveHijo] = nuevoImpacto;
          abiertos.push(hijo);
        }
      }
    }
  }

  return planVacio;
}

/**
 * @brief Comportamiento del técnico para el Nivel 5.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_5(Sensores sensores)
{
  ActualizarMapa(sensores);

  if (sensores.superficie[0] == 'D')
  {
    tiene_zapatillas = true;
  }

  // ============================================================
  // VARIABLES INTERNAS DEL NIVEL 5
  // ============================================================

  static bool plan_tuberias_calculado = false;
  static list<Paso> plan_tuberias_tech;

  static bool pendiente_instalar = false;
  static int ultimo_gotoF = -1;
  static int ultimo_gotoC = -1;

  static int avanceF = -1;
  static int avanceC = -1;

  static int despeje = 0;

  // Control para que el Técnico modifique la altura de SU casilla
  // antes de instalar.
  static bool operacion_altura_tech_hecha = false;

  auto casillaSensorValida = [&](int pos) -> bool
  {
    if (sensores.agentes[pos] != '_')
      return false;

    char casilla = sensores.superficie[pos];

    if (casilla == 'P' || casilla == 'M')
      return false;

    if (casilla == 'B' && !tiene_zapatillas)
      return false;

    int dif = abs((int)sensores.cota[pos] - (int)sensores.cota[0]);

    return dif <= 1;
  };

  auto orientacionHacia = [&](int desdeF, int desdeC, int hastaF, int hastaC) -> int
  {
    if (hastaF == desdeF - 1 && hastaC == desdeC) return 0; // norte
    if (hastaF == desdeF && hastaC == desdeC + 1) return 2; // este
    if (hastaF == desdeF + 1 && hastaC == desdeC) return 4; // sur
    if (hastaF == desdeF && hastaC == desdeC - 1) return 6; // oeste

    return (int)sensores.rumbo;
  };

  auto girarHacia = [&](int orientacionDeseada) -> Action
  {
    int actual = (int)sensores.rumbo;

    if (actual == orientacionDeseada)
      return IDLE;

    int derecha = (orientacionDeseada - actual + 8) % 8;
    int izquierda = (actual - orientacionDeseada + 8) % 8;

    if (derecha <= izquierda)
      return TURN_SR;
    else
      return TURN_SL;
  };

  // ============================================================
  // 0. CALCULAR EL MISMO PLAN DE TUBERÍAS QUE USA EL INGENIERO
  // ============================================================

  if (!plan_tuberias_calculado)
  {
    plan_tuberias_calculado = true;

    plan_tuberias_tech = CalcularPlanTuberiasTech(
        sensores.BelPosF,
        sensores.BelPosC,
        mapaResultado,
        mapaCotas);

    cout << "Tecnico Nivel 5: plan tuberias calculado:" << endl;

    for (auto itp = plan_tuberias_tech.begin(); itp != plan_tuberias_tech.end(); ++itp)
    {
      cout << itp->fil << ", " << itp->col << " (" << itp->op << ")" << endl;
    }

    if (plan_tuberias_tech.empty())
    {
      cout << "Tecnico Nivel 5: no se ha podido calcular plan de tuberias" << endl;
      return IDLE;
    }
  }

  vector<Paso> planVec(plan_tuberias_tech.begin(), plan_tuberias_tech.end());

  auto indiceEnPlan = [&](int f, int c) -> int
  {
    for (int i = 0; i < (int)planVec.size(); i++)
    {
      if (planVec[i].fil == f && planVec[i].col == c)
        return i;
    }

    return -1;
  };

  // ============================================================
  // 1. DESPEJE FINAL
  // Solo se usa al terminar si hiciera falta apartarse.
  // ============================================================

  if (despeje > 0)
  {
    plan_movimiento_n5.clear();

    cout << "Tecnico Nivel 5: despeje final " << despeje << endl;

    if (despeje == 4)
    {
      despeje--;
      return TURN_SL;
    }

    if (despeje == 3)
    {
      if (casillaSensorValida(2))
      {
        despeje--;
        return WALK;
      }
      else
      {
        despeje = 4;
        return TURN_SR;
      }
    }

    if (despeje == 2)
    {
      if (casillaSensorValida(2))
      {
        despeje--;
        return WALK;
      }
      else
      {
        despeje--;
        return TURN_SR;
      }
    }

    if (despeje == 1)
    {
      despeje--;
      return TURN_SR;
    }
  }

  // ============================================================
  // 2. DESPUÉS DE INSTALAR, EL TÉCNICO AVANZA A LA SIGUIENTE
  // CASILLA DEL PLAN PARA DEJAR PASO AL INGENIERO
  // ============================================================

  if (avanceF != -1 && avanceC != -1)
  {
    if (sensores.posF == avanceF && sensores.posC == avanceC)
    {
      avanceF = -1;
      avanceC = -1;
      plan_movimiento_n5.clear();
    }
    else
    {
      if (plan_movimiento_n5.empty())
      {
        bool zap = tiene_zapatillas || sensores.superficie[0] == 'D';

        plan_movimiento_n5 = BuscarPlanTecnicoHasta(
            sensores.posF,
            sensores.posC,
            (int)sensores.rumbo,
            zap,
            avanceF,
            avanceC,
            mapaResultado,
            mapaCotas);

        if (plan_movimiento_n5.empty())
        {
          cout << "Tecnico Nivel 5: no puedo avanzar al siguiente tramo "
               << avanceF << ", " << avanceC << endl;

          avanceF = -1;
          avanceC = -1;

          return IDLE;
        }

        cout << "Tecnico Nivel 5: avanzando al siguiente tramo: ";
        PintaPlan(plan_movimiento_n5);
      }

      if (!plan_movimiento_n5.empty())
      {
        Action sig = plan_movimiento_n5.front();
        plan_movimiento_n5.pop_front();
        last_action = sig;
        return sig;
      }
    }
  }

  // ============================================================
  // 3. GUARDAR LLAMADA DEL INGENIERO
  // ============================================================

  if (sensores.venpaca)
  {
    if (sensores.GotoF != ultimo_gotoF || sensores.GotoC != ultimo_gotoC)
    {
      ultimo_gotoF = sensores.GotoF;
      ultimo_gotoC = sensores.GotoC;

      plan_movimiento_n5.clear();
      operacion_altura_tech_hecha = false;
    }

    pendiente_instalar = true;
  }

  if (!pendiente_instalar)
  {
    plan_movimiento_n5.clear();
    return IDLE;
  }

  int gotoF = ultimo_gotoF;
  int gotoC = ultimo_gotoC;

  // ============================================================
  // 4. BUSCAR LA POSICIÓN DEL INGENIERO EN EL PLAN
  // ============================================================

  int idx = indiceEnPlan(gotoF, gotoC);

  if (idx == -1)
  {
    cout << "Tecnico Nivel 5: Goto no está en el plan de tuberías: "
         << gotoF << ", " << gotoC << endl;

    pendiente_instalar = false;
    plan_movimiento_n5.clear();
    return IDLE;
  }

  int destinoF = -1;
  int destinoC = -1;

  // El Técnico debe ir a la siguiente casilla real del plan.
  if (idx + 1 < (int)planVec.size())
  {
    destinoF = planVec[idx + 1].fil;
    destinoC = planVec[idx + 1].col;
  }
  else
  {
    // Si ya estamos al final, no hay nada más que instalar.
    pendiente_instalar = false;
    plan_movimiento_n5.clear();
    return IDLE;
  }

  // ============================================================
  // 5. SI ESTÁ ENFRENTADO, PRIMERO PREPARA SU ALTURA Y LUEGO INSTALA
  // ============================================================

  if (sensores.enfrente)
  {
    // El Técnico está colocado en plan[idx+1].
    // Antes de instalar, debe aplicar la operación de altura de SU casilla.
    if (!operacion_altura_tech_hecha)
    {
      int opTech = planVec[idx + 1].op;

      if (opTech == -1)
      {
        cout << "Tecnico Nivel 5: DIG en "
             << sensores.posF << ", " << sensores.posC << endl;

        operacion_altura_tech_hecha = true;
        return DIG;
      }

      if (opTech == 1)
      {
        cout << "Tecnico Nivel 5: RAISE en "
             << sensores.posF << ", " << sensores.posC << endl;

        operacion_altura_tech_hecha = true;
        return RAISE;
      }

      operacion_altura_tech_hecha = true;
    }

    cout << "Tecnico Nivel 5: INSTALL coordinado" << endl;

    plan_movimiento_n5.clear();
    pendiente_instalar = false;
    operacion_altura_tech_hecha = false;

    // Después de instalar entre plan[idx] y plan[idx+1],
    // el Técnico se adelanta a plan[idx+2] para dejar paso.
    if (idx + 2 < (int)planVec.size())
    {
      avanceF = planVec[idx + 2].fil;
      avanceC = planVec[idx + 2].col;
    }
    else
    {
      // Último tramo: no hace falta moverse más.
      avanceF = -1;
      avanceC = -1;
      despeje = 0;
    }

    return INSTALL;
  }

  // ============================================================
  // 6. SI YA ESTÁ EN LA CASILLA DESTINO, SE ORIENTA HACIA EL INGENIERO
  // ============================================================

  if (sensores.posF == destinoF && sensores.posC == destinoC)
  {
    plan_movimiento_n5.clear();

    int orientacionDeseada = orientacionHacia(
        sensores.posF,
        sensores.posC,
        gotoF,
        gotoC);

    Action giro = girarHacia(orientacionDeseada);

    if (giro != IDLE)
    {
      cout << "Tecnico Nivel 5: girando hacia Ingeniero" << endl;
      return giro;
    }

    return IDLE;
  }

  // ============================================================
  // 7. MOVERSE A LA SIGUIENTE CASILLA REAL DE LA TUBERÍA
  // ============================================================

  if (plan_movimiento_n5.empty())
  {
    bool zap = tiene_zapatillas || sensores.superficie[0] == 'D';

    plan_movimiento_n5 = BuscarPlanTecnicoHasta(
        sensores.posF,
        sensores.posC,
        (int)sensores.rumbo,
        zap,
        destinoF,
        destinoC,
        mapaResultado,
        mapaCotas);

    if (plan_movimiento_n5.empty())
    {
      cout << "Tecnico Nivel 5: no puedo ir a tramo real "
           << destinoF << ", " << destinoC << endl;

      return IDLE;
    }

    cout << "Tecnico Nivel 5: plan hacia tramo real: ";
    PintaPlan(plan_movimiento_n5);
  }

  if (!plan_movimiento_n5.empty())
  {
    Action sig = plan_movimiento_n5.front();
    plan_movimiento_n5.pop_front();
    last_action = sig;
    return sig;
  }

  return IDLE;
}

/**
 * @brief Comportamiento del técnico para el Nivel 6.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_6(Sensores sensores)
{
  static int fase_n6 = 0;
  static int turnos_explorando_n6 = 0;
  static bool mensaje_cambio_fase_n6 = false;

  ActualizarMapa(sensores);

  // ============================================================
  // Contar cuánto mapa conocemos
  // ============================================================

  int conocidas = 0;
  int total = 0;

  for (int f = 0; f < mapaResultado.size(); f++)
  {
    for (int c = 0; c < mapaResultado[0].size(); c++)
    {
      total++;

      if (mapaResultado[f][c] != '?')
      {
        conocidas++;
      }
    }
  }

  double porcentajeConocido = 0.0;

  if (total > 0)
  {
    porcentajeConocido = (100.0 * conocidas) / total;
  }

  // ============================================================
  // FASE 0: exploración
  // ============================================================

  if (fase_n6 == 0)
  {
    turnos_explorando_n6++;

    // Mismo criterio que el Ingeniero:
    // cuando se conoce suficiente mapa o pasan bastantes turnos,
    // pasamos a construcción.
    if (porcentajeConocido >= 65.0 || turnos_explorando_n6 >= 1200)
    {
      fase_n6 = 1;

      if (!mensaje_cambio_fase_n6)
      {
        cout << "Nivel 6 Tecnico: cambio a fase de construccion. Mapa conocido: "
             << porcentajeConocido << "%" << endl;

        mensaje_cambio_fase_n6 = true;
      }

      return IDLE;
    }

    // Mientras tanto, explorar con el comportamiento del Nivel 1
    return ComportamientoTecnicoNivel_1(sensores);
  }

  // ============================================================
  // FASE 1: construcción
  // ============================================================

  if (fase_n6 == 1)
  {
    // Reutilizamos la lógica del Nivel 5.
    return ComportamientoTecnicoNivel_5(sensores);
  }

  return IDLE;
}



// =========================================================================
// FUNCIONES PROPORCIONADAS
// =========================================================================

/**
 * @brief Actualiza el mapaResultado y mapaCotas con la información de los sensores.
 * @param sensores Datos actuales de los sensores.
 */
void ComportamientoTecnico::ActualizarMapa(Sensores sensores) {
  mapaResultado[sensores.posF][sensores.posC] = sensores.superficie[0];
  mapaCotas[sensores.posF][sensores.posC] = sensores.cota[0];

  int pos = 1;
  switch (sensores.rumbo) {
    case norte:
      for (int j = 1; j < 4; j++)
        for (int i = -j; i <= j; i++) {
          mapaResultado[sensores.posF - j][sensores.posC + i] = sensores.superficie[pos];
          mapaCotas[sensores.posF - j][sensores.posC + i] = sensores.cota[pos++];
        }
      break;
    case noreste:
      mapaResultado[sensores.posF - 1][sensores.posC] = sensores.superficie[1];
      mapaCotas[sensores.posF - 1][sensores.posC] = sensores.cota[1];
      mapaResultado[sensores.posF - 1][sensores.posC + 1] = sensores.superficie[2];
      mapaCotas[sensores.posF - 1][sensores.posC + 1] = sensores.cota[2];
      mapaResultado[sensores.posF][sensores.posC + 1] = sensores.superficie[3];
      mapaCotas[sensores.posF][sensores.posC + 1] = sensores.cota[3];
      mapaResultado[sensores.posF - 2][sensores.posC] = sensores.superficie[4];
      mapaCotas[sensores.posF - 2][sensores.posC] = sensores.cota[4];
      mapaResultado[sensores.posF - 2][sensores.posC + 1] = sensores.superficie[5];
      mapaCotas[sensores.posF - 2][sensores.posC + 1] = sensores.cota[5];
      mapaResultado[sensores.posF - 2][sensores.posC + 2] = sensores.superficie[6];
      mapaCotas[sensores.posF - 2][sensores.posC + 2] = sensores.cota[6];
      mapaResultado[sensores.posF - 1][sensores.posC + 2] = sensores.superficie[7];
      mapaCotas[sensores.posF - 1][sensores.posC + 2] = sensores.cota[7];
      mapaResultado[sensores.posF][sensores.posC + 2] = sensores.superficie[8];
      mapaCotas[sensores.posF][sensores.posC + 2] = sensores.cota[8];
      mapaResultado[sensores.posF - 3][sensores.posC] = sensores.superficie[9];
      mapaCotas[sensores.posF - 3][sensores.posC] = sensores.cota[9];
      mapaResultado[sensores.posF - 3][sensores.posC + 1] = sensores.superficie[10];
      mapaCotas[sensores.posF - 3][sensores.posC + 1] = sensores.cota[10];
      mapaResultado[sensores.posF - 3][sensores.posC + 2] = sensores.superficie[11];
      mapaCotas[sensores.posF - 3][sensores.posC + 2] = sensores.cota[11];
      mapaResultado[sensores.posF - 3][sensores.posC + 3] = sensores.superficie[12];
      mapaCotas[sensores.posF - 3][sensores.posC + 3] = sensores.cota[12];
      mapaResultado[sensores.posF - 2][sensores.posC + 3] = sensores.superficie[13];
      mapaCotas[sensores.posF - 2][sensores.posC + 3] = sensores.cota[13];
      mapaResultado[sensores.posF - 1][sensores.posC + 3] = sensores.superficie[14];
      mapaCotas[sensores.posF - 1][sensores.posC + 3] = sensores.cota[14];
      mapaResultado[sensores.posF][sensores.posC + 3] = sensores.superficie[15];
      mapaCotas[sensores.posF][sensores.posC + 3] = sensores.cota[15];
      break;
    case este:
      for (int j = 1; j < 4; j++)
        for (int i = -j; i <= j; i++) {
          mapaResultado[sensores.posF + i][sensores.posC + j] = sensores.superficie[pos];
          mapaCotas[sensores.posF + i][sensores.posC + j] = sensores.cota[pos++];
        }
      break;
    case sureste:
      mapaResultado[sensores.posF][sensores.posC + 1] = sensores.superficie[1];
      mapaCotas[sensores.posF][sensores.posC + 1] = sensores.cota[1];
      mapaResultado[sensores.posF + 1][sensores.posC + 1] = sensores.superficie[2];
      mapaCotas[sensores.posF + 1][sensores.posC + 1] = sensores.cota[2];
      mapaResultado[sensores.posF + 1][sensores.posC] = sensores.superficie[3];
      mapaCotas[sensores.posF + 1][sensores.posC] = sensores.cota[3];
      mapaResultado[sensores.posF][sensores.posC + 2] = sensores.superficie[4];
      mapaCotas[sensores.posF][sensores.posC + 2] = sensores.cota[4];
      mapaResultado[sensores.posF + 1][sensores.posC + 2] = sensores.superficie[5];
      mapaCotas[sensores.posF + 1][sensores.posC + 2] = sensores.cota[5];
      mapaResultado[sensores.posF + 2][sensores.posC + 2] = sensores.superficie[6];
      mapaCotas[sensores.posF + 2][sensores.posC + 2] = sensores.cota[6];
      mapaResultado[sensores.posF + 2][sensores.posC + 1] = sensores.superficie[7];
      mapaCotas[sensores.posF + 2][sensores.posC + 1] = sensores.cota[7];
      mapaResultado[sensores.posF + 2][sensores.posC] = sensores.superficie[8];
      mapaCotas[sensores.posF + 2][sensores.posC] = sensores.cota[8];
      mapaResultado[sensores.posF][sensores.posC + 3] = sensores.superficie[9];
      mapaCotas[sensores.posF][sensores.posC + 3] = sensores.cota[9];
      mapaResultado[sensores.posF + 1][sensores.posC + 3] = sensores.superficie[10];
      mapaCotas[sensores.posF + 1][sensores.posC + 3] = sensores.cota[10];
      mapaResultado[sensores.posF + 2][sensores.posC + 3] = sensores.superficie[11];
      mapaCotas[sensores.posF + 2][sensores.posC + 3] = sensores.cota[11];
      mapaResultado[sensores.posF + 3][sensores.posC + 3] = sensores.superficie[12];
      mapaCotas[sensores.posF + 3][sensores.posC + 3] = sensores.cota[12];
      mapaResultado[sensores.posF + 3][sensores.posC + 2] = sensores.superficie[13];
      mapaCotas[sensores.posF + 3][sensores.posC + 2] = sensores.cota[13];
      mapaResultado[sensores.posF + 3][sensores.posC + 1] = sensores.superficie[14];
      mapaCotas[sensores.posF + 3][sensores.posC + 1] = sensores.cota[14];
      mapaResultado[sensores.posF + 3][sensores.posC] = sensores.superficie[15];
      mapaCotas[sensores.posF + 3][sensores.posC] = sensores.cota[15];
      break;
    case sur:
      for (int j = 1; j < 4; j++)
        for (int i = -j; i <= j; i++) {
          mapaResultado[sensores.posF + j][sensores.posC - i] = sensores.superficie[pos];
          mapaCotas[sensores.posF + j][sensores.posC - i] = sensores.cota[pos++];
        }
      break;
    case suroeste:
      mapaResultado[sensores.posF + 1][sensores.posC] = sensores.superficie[1];
      mapaCotas[sensores.posF + 1][sensores.posC] = sensores.cota[1];
      mapaResultado[sensores.posF + 1][sensores.posC - 1] = sensores.superficie[2];
      mapaCotas[sensores.posF + 1][sensores.posC - 1] = sensores.cota[2];
      mapaResultado[sensores.posF][sensores.posC - 1] = sensores.superficie[3];
      mapaCotas[sensores.posF][sensores.posC - 1] = sensores.cota[3];
      mapaResultado[sensores.posF + 2][sensores.posC] = sensores.superficie[4];
      mapaCotas[sensores.posF + 2][sensores.posC] = sensores.cota[4];
      mapaResultado[sensores.posF + 2][sensores.posC - 1] = sensores.superficie[5];
      mapaCotas[sensores.posF + 2][sensores.posC - 1] = sensores.cota[5];
      mapaResultado[sensores.posF + 2][sensores.posC - 2] = sensores.superficie[6];
      mapaCotas[sensores.posF + 2][sensores.posC - 2] = sensores.cota[6];
      mapaResultado[sensores.posF + 1][sensores.posC - 2] = sensores.superficie[7];
      mapaCotas[sensores.posF + 1][sensores.posC - 2] = sensores.cota[7];
      mapaResultado[sensores.posF][sensores.posC - 2] = sensores.superficie[8];
      mapaCotas[sensores.posF][sensores.posC - 2] = sensores.cota[8];
      mapaResultado[sensores.posF + 3][sensores.posC] = sensores.superficie[9];
      mapaCotas[sensores.posF + 3][sensores.posC] = sensores.cota[9];
      mapaResultado[sensores.posF + 3][sensores.posC - 1] = sensores.superficie[10];
      mapaCotas[sensores.posF + 3][sensores.posC - 1] = sensores.cota[10];
      mapaResultado[sensores.posF + 3][sensores.posC - 2] = sensores.superficie[11];
      mapaCotas[sensores.posF + 3][sensores.posC - 2] = sensores.cota[11];
      mapaResultado[sensores.posF + 3][sensores.posC - 3] = sensores.superficie[12];
      mapaCotas[sensores.posF + 3][sensores.posC - 3] = sensores.cota[12];
      mapaResultado[sensores.posF + 2][sensores.posC - 3] = sensores.superficie[13];
      mapaCotas[sensores.posF + 2][sensores.posC - 3] = sensores.cota[13];
      mapaResultado[sensores.posF + 1][sensores.posC - 3] = sensores.superficie[14];
      mapaCotas[sensores.posF + 1][sensores.posC - 3] = sensores.cota[14];
      mapaResultado[sensores.posF][sensores.posC - 3] = sensores.superficie[15];
      mapaCotas[sensores.posF][sensores.posC - 3] = sensores.cota[15];
      break;
    case oeste:
      for (int j = 1; j < 4; j++)
        for (int i = -j; i <= j; i++) {
          mapaResultado[sensores.posF - i][sensores.posC - j] = sensores.superficie[pos];
          mapaCotas[sensores.posF - i][sensores.posC - j] = sensores.cota[pos++];
        }
      break;
    case noroeste:
      mapaResultado[sensores.posF][sensores.posC - 1] = sensores.superficie[1];
      mapaCotas[sensores.posF][sensores.posC - 1] = sensores.cota[1];
      mapaResultado[sensores.posF - 1][sensores.posC - 1] = sensores.superficie[2];
      mapaCotas[sensores.posF - 1][sensores.posC - 1] = sensores.cota[2];
      mapaResultado[sensores.posF - 1][sensores.posC] = sensores.superficie[3];
      mapaCotas[sensores.posF - 1][sensores.posC] = sensores.cota[3];
      mapaResultado[sensores.posF][sensores.posC - 2] = sensores.superficie[4];
      mapaCotas[sensores.posF][sensores.posC - 2] = sensores.cota[4];
      mapaResultado[sensores.posF - 1][sensores.posC - 2] = sensores.superficie[5];
      mapaCotas[sensores.posF - 1][sensores.posC - 2] = sensores.cota[5];
      mapaResultado[sensores.posF - 2][sensores.posC - 2] = sensores.superficie[6];
      mapaCotas[sensores.posF - 2][sensores.posC - 2] = sensores.cota[6];
      mapaResultado[sensores.posF - 2][sensores.posC - 1] = sensores.superficie[7];
      mapaCotas[sensores.posF - 2][sensores.posC - 1] = sensores.cota[7];
      mapaResultado[sensores.posF - 2][sensores.posC] = sensores.superficie[8];
      mapaCotas[sensores.posF - 2][sensores.posC] = sensores.cota[8];
      mapaResultado[sensores.posF][sensores.posC - 3] = sensores.superficie[9];
      mapaCotas[sensores.posF][sensores.posC - 3] = sensores.cota[9];
      mapaResultado[sensores.posF - 1][sensores.posC - 3] = sensores.superficie[10];
      mapaCotas[sensores.posF - 1][sensores.posC - 3] = sensores.cota[10];
      mapaResultado[sensores.posF - 2][sensores.posC - 3] = sensores.superficie[11];
      mapaCotas[sensores.posF - 2][sensores.posC - 3] = sensores.cota[11];
      mapaResultado[sensores.posF - 3][sensores.posC - 3] = sensores.superficie[12];
      mapaCotas[sensores.posF - 3][sensores.posC - 3] = sensores.cota[12];
      mapaResultado[sensores.posF - 3][sensores.posC - 2] = sensores.superficie[13];
      mapaCotas[sensores.posF - 3][sensores.posC - 2] = sensores.cota[13];
      mapaResultado[sensores.posF - 3][sensores.posC - 1] = sensores.superficie[14];
      mapaCotas[sensores.posF - 3][sensores.posC - 1] = sensores.cota[14];
      mapaResultado[sensores.posF - 3][sensores.posC] = sensores.superficie[15];
      mapaCotas[sensores.posF - 3][sensores.posC] = sensores.cota[15];
      break;
  }
}



/**
 * @brief Determina si una casilla es transitable para el técnico.
 * En esta práctica, si el técnico tiene zapatillas, el bosque ('B') es transitable.
 * @param f Fila de la casilla.
 * @param c Columna de la casilla.
 * @param tieneZapatillas Indica si el agente posee las zapatillas.
 * @return true si la casilla es transitable.
 */
bool ComportamientoTecnico::EsCasillaTransitableLevel0(int f, int c, bool tieneZapatillas) {
  if (f < 0 || f >= mapaResultado.size() || c < 0 || c >= mapaResultado[0].size()) return false;
  return es_camino(mapaResultado[f][c]);  // Solo 'C', 'S', 'D', 'U' son transitables en Nivel 0
}

/**
 * @brief Comprueba si la casilla de delante es accesible por diferencia de altura.
 * Para el técnico: desnivel máximo siempre 1.
 * @param actual Estado actual del agente (fila, columna, orientacion).
 * @return true si el desnivel con la casilla de delante es admisible.
 */
bool ComportamientoTecnico::EsAccesiblePorAltura(const ubicacion &actual) {
  ubicacion del = Delante(actual);
  if (del.f < 0 || del.f >= mapaCotas.size() || del.c < 0 || del.c >= mapaCotas[0].size()) return false;
  int desnivel = abs(mapaCotas[del.f][del.c] - mapaCotas[actual.f][actual.c]);
  if (desnivel > 1) return false;
  return true;
}

/**
 * @brief Devuelve la posición (fila, columna) de la casilla que hay delante del agente.
 * Calcula la casilla frontal según la orientación actual (8 direcciones).
 * @param actual Estado actual del agente (fila, columna, orientacion).
 * @return Estado con la fila y columna de la casilla de enfrente.
 */
ubicacion ComportamientoTecnico::Delante(const ubicacion &actual) const {
  ubicacion delante = actual;
  switch (actual.brujula) {
    case 0: delante.f--; break;                        // norte
    case 1: delante.f--; delante.c++; break;     // noreste
    case 2: delante.c++; break;                     // este
    case 3: delante.f++; delante.c++; break;     // sureste
    case 4: delante.f++; break;                        // sur
    case 5: delante.f++; delante.c--; break;     // suroeste
    case 6: delante.c--; break;                     // oeste
    case 7: delante.f--; delante.c--; break;     // noroeste
  }
  return delante;
}


/**
 * @brief Imprime por consola la secuencia de acciones de un plan.
 *
 * @param plan  Lista de acciones del plan.
 */
void ComportamientoTecnico::PintaPlan(const list<Action> &plan)
{
  auto it = plan.begin();
  while (it != plan.end())
  {
    if (*it == WALK)
    {
      cout << "W ";
    }
    else if (*it == JUMP)
    {
      cout << "J ";
    }
    else if (*it == TURN_SR)
    {
      cout << "r ";
    }
    else if (*it == TURN_SL)
    {
      cout << "l ";
    }
    else if (*it == COME)
    {
      cout << "C ";
    }
    else if (*it == IDLE)
    {
      cout << "I ";
    }
    else
    {
      cout << "-_ ";
    }
    it++;
  }
  cout << "( longitud " << plan.size() << ")" << endl;
}



/**
 * @brief Convierte un plan de acciones en una lista de casillas para
 *        su visualización en el mapa 2D.
 *
 * @param st    Estado de partida.
 * @param plan  Lista de acciones del plan.
 */
void ComportamientoTecnico::VisualizaPlan(const ubicacion &st,
                                            const list<Action> &plan)
{
   listaPlanCasillas.clear();
  ubicacion cst = st;

  listaPlanCasillas.push_back({cst.f, cst.c, WALK});
  auto it = plan.begin();
  while (it != plan.end())
  {

    switch (*it)
    {
    case JUMP:
      switch (cst.brujula)
      {
      case 0:
        cst.f--;
        break;
      case 1:
        cst.f--;
        cst.c++;
        break;
      case 2:
        cst.c++;
        break;
      case 3:
        cst.f++;
        cst.c++;
        break;
      case 4:
        cst.f++;
        break;
      case 5:
        cst.f++;
        cst.c--;
        break;
      case 6:
        cst.c--;
        break;
      case 7:
        cst.f--;
        cst.c--;
        break;
      }
      if (cst.f >= 0 && cst.f < mapaResultado.size() &&
          cst.c >= 0 && cst.c < mapaResultado[0].size())
        listaPlanCasillas.push_back({cst.f, cst.c, JUMP});
    case WALK:
      switch (cst.brujula)
      {
      case 0:
        cst.f--;
        break;
      case 1:
        cst.f--;
        cst.c++;
        break;
      case 2:
        cst.c++;
        break;
      case 3:
        cst.f++;
        cst.c++;
        break;
      case 4:
        cst.f++;
        break;
      case 5:
        cst.f++;
        cst.c--;
        break;
      case 6:
        cst.c--;
        break;
      case 7:
        cst.f--;
        cst.c--;
        break;
      }
      if (cst.f >= 0 && cst.f < mapaResultado.size() &&
          cst.c >= 0 && cst.c < mapaResultado[0].size())
        listaPlanCasillas.push_back({cst.f, cst.c, WALK});
      break;
    case TURN_SR:
      cst.brujula = (Orientacion) (( (int) cst.brujula + 1) % 8);
      break;
    case TURN_SL:
      cst.brujula = (Orientacion) (( (int) cst.brujula + 7) % 8);
      break;
    }
    it++;
  }
}


