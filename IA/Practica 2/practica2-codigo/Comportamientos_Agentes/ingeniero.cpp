#include "ingeniero.hpp"
#include "motorlib/util.h"
#include <iostream>
#include <queue>
#include <set>

/* Añadidas */
#include <map>
#include <list>
#include <cmath>

using namespace std;

// =========================================================================
// ÁREA DE IMPLEMENTACIÓN DEL ESTUDIANTE
// =========================================================================

Action ComportamientoIngeniero::think(Sensores sensores)
{
  Action accion = IDLE;

  // Decisión del agente según el nivel
  switch (sensores.nivel)
  {
  case 0: accion = ComportamientoIngenieroNivel_0(sensores); break;
  case 1: accion = ComportamientoIngenieroNivel_1(sensores); break;
  case 2: accion = ComportamientoIngenieroNivel_2(sensores); break;
  case 3: accion = ComportamientoIngenieroNivel_3(sensores); break;
  case 4: accion = ComportamientoIngenieroNivel_4(sensores); break;
  case 5: accion = ComportamientoIngenieroNivel_5(sensores); break;
  case 6: accion = ComportamientoIngenieroNivel_6(sensores); break;
  }

  return accion;
}

/**
 * @brief Determina la mejor casilla interesante para el Ingeniero.
 * Devuelve:
 * 2 -> avanzar
 * 1 -> girar izquierda
 * 3 -> girar derecha
 * 0 -> no hay opción interesante
 */
int VeoCasillaInteresanteI(char i, char c, char d, bool zap)
{
  // Primero, prioridad absoluta: llegar a U
  if (c == 'U') return 2;
  else if (i == 'U') return 1;
  else if (d == 'U') return 3;

  // Si no tengo zapatillas, interesa cogerlas
  if (!zap)
  {
    if (c == 'D') return 2;
    else if (i == 'D') return 1;
    else if (d == 'D') return 3;
  }

  // Después seguir camino
  if (c == 'C') return 2;
  else if (i == 'C') return 1;
  else if (d == 'C') return 3;

  return 0;
}

/**
 * @brief Filtra una casilla según si es viable por altura para el Ingeniero.
 * Sin zapatillas permite desnivel máximo 1.
 * Con zapatillas permite desnivel máximo 2.
 */
char ViablePorAlturaI(char casilla, int dif, bool zap)
{
  if (abs(dif) <= 1 || (zap && abs(dif) <= 2))
    return casilla;
  else
    return 'P';
}


// Niveles iniciales (Comportamientos reactivos simples)
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_0(Sensores sensores)
{
  Action accion = IDLE;

  // 1. Actualización del mapa conocido
  ActualizarMapa(sensores);

  // Si tengo giros pendientes, los ejecuto antes de decidir otra cosa.
  // Esto sirve para completar un giro de 180º cuando hay bloqueo con otro agente.
  if (giros_pendientes > 0)
  {
    giros_pendientes--;
    last_action = TURN_SR;
    return TURN_SR;
  }

  // 2. Actualización de variables de estado
  if (sensores.superficie[0] == 'D')
  {
    tiene_zapatillas = true;
  }

  // 3. Si ya he llegado a una planta de tratamiento, me quedo quieto
  if (sensores.superficie[0] == 'U')
  {
    accion = IDLE;
  }
  else
  {
    // 4. Filtramos las tres casillas cercanas por altura
    char i = ViablePorAlturaI(
        sensores.superficie[1],
        sensores.cota[1] - sensores.cota[0],
        tiene_zapatillas);

    char c = ViablePorAlturaI(
        sensores.superficie[2],
        sensores.cota[2] - sensores.cota[0],
        tiene_zapatillas);

    char d = ViablePorAlturaI(
        sensores.superficie[3],
        sensores.cota[3] - sensores.cota[0],
        tiene_zapatillas);

    
    

    // 5. Evitamos avanzar si hay otro agente justo delante

    // Si tengo otro agente justo delante, me doy la vuelta.
    // El Ingeniero actúa primero, así que él toma la iniciativa para desbloquear.
    if (sensores.agentes[2] != '_')
    {
      giros_pendientes = 3; // este turno giro + 3 más = 4 giros de 45º = 180º
      accion = TURN_SR;
      last_action = accion;
      return accion;
    }

    // 6. Elegimos la mejor casilla interesante
    int pos = VeoCasillaInteresanteI(i, c, d, tiene_zapatillas);

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
      accion = TURN_SL;
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
bool ComportamientoIngeniero::es_camino(unsigned char c) const
{
  return (c == 'C' || c == 'D' || c == 'U');
}




bool EsTransitableNivel1I(char casilla)
{
  return casilla == 'C' || casilla == 'S' || casilla == 'D' || casilla == 'U';
}

int VeoCasillaInteresanteNivel1I(char i, char c, char d)
{
  // Prioridad: avanzar si se puede
  if (c == 'C' || c == 'S' || c == 'D' || c == 'U')
    return 2;

  // Ingeniero prioriza izquierda
  if (i == 'C' || i == 'S' || i == 'D' || i == 'U')
    return 1;

  if (d == 'C' || d == 'S' || d == 'D' || d == 'U')
    return 3;

  return 0;
}


/**
 * @brief Comportamiento reactivo del ingeniero para el Nivel 1.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_1(Sensores sensores)
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

  char i = ViablePorAlturaI(
      sensores.superficie[1],
      sensores.cota[1] - sensores.cota[0],
      tiene_zapatillas);

  char c = ViablePorAlturaI(
      sensores.superficie[2],
      sensores.cota[2] - sensores.cota[0],
      tiene_zapatillas);

  char d = ViablePorAlturaI(
      sensores.superficie[3],
      sensores.cota[3] - sensores.cota[0],
      tiene_zapatillas);

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
  // Esto evita quedarse girando en el mismo sitio.
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
                     + 2; // pequeña preferencia por avanzar

    if (puntuacion > mejorPuntuacion)
    {
      mejorPuntuacion = puntuacion;
      mejorAccion = WALK;
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

  if (mejorAccion != IDLE)
  {
    accion = mejorAccion;
  }
  else
  {
    accion = TURN_SL;
  }

  last_action = accion;
  return accion;
}


// Niveles avanzados (Uso de búsqueda)

struct EstadoN2
{
  int f;
  int c;
  int brujula;
  bool zapatillas;

  bool operator<(const EstadoN2 &otro) const
  {
    if (f != otro.f) return f < otro.f;
    if (c != otro.c) return c < otro.c;
    if (brujula != otro.brujula) return brujula < otro.brujula;
    return zapatillas < otro.zapatillas;
  }
};

struct NodoN2
{
  EstadoN2 estado;
  list<Action> plan;
};

/**
 * @brief Comportamiento del ingeniero para el Nivel 2 (búsqueda).
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_2(Sensores sensores)
{
  // Si ya estoy en la Belkanita, no hago nada.
  if (sensores.posF == sensores.BelPosF && sensores.posC == sensores.BelPosC)
  {
    return IDLE;
  }

  // Si ya tengo un plan calculado, ejecuto la siguiente acción.
  if (!plan_n2.empty())
  {
    Action sig = plan_n2.front();
    plan_n2.pop_front();
    return sig;
  }

  // ============================================================
  // Cálculo del plan mediante BFS
  // ============================================================

  auto dentroMapa = [&](int f, int c) -> bool
  {
    return f >= 0 && f < mapaResultado.size() &&
           c >= 0 && c < mapaResultado[0].size();
  };

  auto transitableIngeniero = [&](int f, int c) -> bool
  {
    if (!dentroMapa(f, c)) return false;

    unsigned char casilla = mapaResultado[f][c];

    // Para el Ingeniero consideramos intransitables precipicio, muro y bosque.
    // El resto de terrenos principales se pueden atravesar.
    if (casilla == 'P' || casilla == 'M' || casilla == 'B')
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

  auto alturaValida = [&](int f1, int c1, int f2, int c2, bool zap) -> bool
  {
    if (!dentroMapa(f1, c1) || !dentroMapa(f2, c2)) return false;

    int dif = abs((int)mapaCotas[f2][c2] - (int)mapaCotas[f1][c1]);

    if (zap)
      return dif <= 2;
    else
      return dif <= 1;
  };

  queue<NodoN2> abiertos;
  set<EstadoN2> cerrados;

  EstadoN2 inicial;
  inicial.f = sensores.posF;
  inicial.c = sensores.posC;
  inicial.brujula = (int)sensores.rumbo;
  inicial.zapatillas = tiene_zapatillas || sensores.superficie[0] == 'D';

  NodoN2 nodoInicial;
  nodoInicial.estado = inicial;
  nodoInicial.plan.clear();

  abiertos.push(nodoInicial);
  cerrados.insert(inicial);

  bool encontrado = false;
  list<Action> mejorPlan;

  while (!abiertos.empty() && !encontrado)
  {
    NodoN2 actual = abiertos.front();
    abiertos.pop();

    EstadoN2 st = actual.estado;

    // Objetivo: llegar a la casilla de Belkanita
    if (st.f == sensores.BelPosF && st.c == sensores.BelPosC)
    {
      encontrado = true;
      mejorPlan = actual.plan;
      break;
    }

    // ------------------------------------------------------------
    // Acción TURN_SL
    // ------------------------------------------------------------
    {
      EstadoN2 hijo = st;
      hijo.brujula = (hijo.brujula + 7) % 8;

      if (cerrados.find(hijo) == cerrados.end())
      {
        NodoN2 nuevo;
        nuevo.estado = hijo;
        nuevo.plan = actual.plan;
        nuevo.plan.push_back(TURN_SL);

        abiertos.push(nuevo);
        cerrados.insert(hijo);
      }
    }

    // ------------------------------------------------------------
    // Acción TURN_SR
    // ------------------------------------------------------------
    {
      EstadoN2 hijo = st;
      hijo.brujula = (hijo.brujula + 1) % 8;

      if (cerrados.find(hijo) == cerrados.end())
      {
        NodoN2 nuevo;
        nuevo.estado = hijo;
        nuevo.plan = actual.plan;
        nuevo.plan.push_back(TURN_SR);

        abiertos.push(nuevo);
        cerrados.insert(hijo);
      }
    }

    // ------------------------------------------------------------
    // Acción WALK
    // ------------------------------------------------------------
    {
      pair<int, int> sig = siguienteCasilla(st.f, st.c, st.brujula);
      int nf = sig.first;
      int nc = sig.second;

      if (transitableIngeniero(nf, nc) &&
          alturaValida(st.f, st.c, nf, nc, st.zapatillas))
      {
        EstadoN2 hijo = st;
        hijo.f = nf;
        hijo.c = nc;

        if (mapaResultado[nf][nc] == 'D')
          hijo.zapatillas = true;

        if (cerrados.find(hijo) == cerrados.end())
        {
          NodoN2 nuevo;
          nuevo.estado = hijo;
          nuevo.plan = actual.plan;
          nuevo.plan.push_back(WALK);

          abiertos.push(nuevo);
          cerrados.insert(hijo);
        }
      }
    }

    // ------------------------------------------------------------
    // Acción JUMP
    // ------------------------------------------------------------
    {
      pair<int, int> intermedia = siguienteCasilla(st.f, st.c, st.brujula);
      pair<int, int> fin = siguienteCasilla(intermedia.first, intermedia.second, st.brujula);

      int fi = intermedia.first;
      int ci = intermedia.second;
      int nf = fin.first;
      int nc = fin.second;

      if (transitableIngeniero(fi, ci) &&
          transitableIngeniero(nf, nc) &&
          alturaValida(st.f, st.c, nf, nc, st.zapatillas))
      {
        EstadoN2 hijo = st;
        hijo.f = nf;
        hijo.c = nc;

        if (mapaResultado[fi][ci] == 'D' || mapaResultado[nf][nc] == 'D')
          hijo.zapatillas = true;

        if (cerrados.find(hijo) == cerrados.end())
        {
          NodoN2 nuevo;
          nuevo.estado = hijo;
          nuevo.plan = actual.plan;
          nuevo.plan.push_back(JUMP);

          abiertos.push(nuevo);
          cerrados.insert(hijo);
        }
      }
    }
  }

  if (encontrado)
  {
    plan_n2 = mejorPlan;

    cout << "Plan Nivel 2 encontrado: ";
    PintaPlan(plan_n2);

    VisualizaPlan({sensores.posF, sensores.posC, sensores.rumbo}, plan_n2);

    if (!plan_n2.empty())
    {
      Action sig = plan_n2.front();
      plan_n2.pop_front();
      return sig;
    }
  }

  // Si no encuentra plan, se queda quieto.
  return IDLE;
}

/**
 * @brief Comportamiento del ingeniero para el Nivel 3.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_3(Sensores sensores)
{
  return IDLE;
}

/**
 * @brief Comportamiento del ingeniero para el Nivel 4.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_4(Sensores sensores)
{
  return IDLE;
}

/**
 * @brief Comportamiento del ingeniero para el Nivel 5.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_5(Sensores sensores)
{
  return IDLE;
}

/**
 * @brief Comportamiento del ingeniero para el Nivel 6.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_6(Sensores sensores)
{
  return IDLE;
}

// =========================================================================
// FUNCIONES PROPORCIONADAS
// =========================================================================

/**
 * @brief Actualiza el mapaResultado y mapaCotas con la información de los sensores.
 * @param sensores Datos actuales de los sensores.
 */
void ComportamientoIngeniero::ActualizarMapa(Sensores sensores)
{
  mapaResultado[sensores.posF][sensores.posC] = sensores.superficie[0];
  mapaCotas[sensores.posF][sensores.posC] = sensores.cota[0];

  int pos = 1;
  switch (sensores.rumbo)
  {
  case norte:
    for (int j = 1; j < 4; j++)
      for (int i = -j; i <= j; i++)
      {
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
      for (int i = -j; i <= j; i++)
      {
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
      for (int i = -j; i <= j; i++)
      {
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
      for (int i = -j; i <= j; i++)
      {
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
 * @brief Determina si una casilla es transitable para el ingeniero.
 * @param f Fila de la casilla.
 * @param c Columna de la casilla.
 * @param tieneZapatillas Indica si el agente posee las zapatillas.
 * @return true si la casilla es transitable (no es muro ni precipicio).
 */
bool ComportamientoIngeniero::EsCasillaTransitableLevel0(int f, int c, bool tieneZapatillas)
{
  if (f < 0 || f >= mapaResultado.size() || c < 0 || c >= mapaResultado[0].size())
    return false;
  return es_camino(mapaResultado[f][c]); // Solo 'C', 'D', 'U' son transitables en Nivel 0
}

/**
 * @brief Comprueba si la casilla de delante es accesible por diferencia de altura.
 * Para el ingeniero: desnivel máximo 1 sin zapatillas, 2 con zapatillas.
 * @param actual Estado actual del agente (fila, columna, orientacion, zap).
 * @return true si el desnivel con la casilla de delante es admisible.
 */
bool ComportamientoIngeniero::EsAccesiblePorAltura(const ubicacion &actual, bool zap)
{
  ubicacion del = Delante(actual);
  if (del.f < 0 || del.f >= mapaCotas.size() || del.c < 0 || del.c >= mapaCotas[0].size())
    return false;
  int desnivel = abs(mapaCotas[del.f][del.c] - mapaCotas[actual.f][actual.c]);
  if (zap && desnivel > 2)
    return false;
  if (!zap && desnivel > 1)
    return false;
  return true;
}

/**
 * @brief Devuelve la posición (fila, columna) de la casilla que hay delante del agente.
 * Calcula la casilla frontal según la orientación actual (8 direcciones).
 * @param actual Estado actual del agente (fila, columna, orientacion).
 * @return Estado con la fila y columna de la casilla de enfrente.
 */
ubicacion ComportamientoIngeniero::Delante(const ubicacion &actual) const
{
  ubicacion delante = actual;
  switch (actual.brujula)
  {
  case 0:
    delante.f--;
    break; // norte
  case 1:
    delante.f--;
    delante.c++;
    break; // noreste
  case 2:
    delante.c++;
    break; // este
  case 3:
    delante.f++;
    delante.c++;
    break; // sureste
  case 4:
    delante.f++;
    break; // sur
  case 5:
    delante.f++;
    delante.c--;
    break; // suroeste
  case 6:
    delante.c--;
    break; // oeste
  case 7:
    delante.f--;
    delante.c--;
    break; // noroeste
  }
  return delante;
}

/**
 * @brief Imprime por consola la secuencia de acciones de un plan.
 *
 * @param plan  Lista de acciones del plan.
 */
void ComportamientoIngeniero::PintaPlan(const list<Action> &plan)
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
 * @brief Imprime las coordenadas y operaciones de un plan de tubería.
 *
 * @param plan  Lista de pasos (fila, columna, operación),
 *              donde operacion = -1 (DIG), operación = 1 (RAISE).
 */
void ComportamientoIngeniero::PintaPlan(const list<Paso> &plan)
{
  auto it = plan.begin();
  while (it != plan.end())
  {
    cout << it->fil << ", " << it->col << " (" << it->op << ")\n";
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
void ComportamientoIngeniero::VisualizaPlan(const ubicacion &st,
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

/**
 * @brief Convierte un plan de tubería en la lista de casillas usada
 *        por el sistema de visualización.
 *
 * @param st    Estado de partida (no utilizado directamente).
 * @param plan  Lista de pasos del plan de tubería.
 */
void ComportamientoIngeniero::VisualizaRedTuberias(const list<Paso> &plan)
{
  listaCanalizacionTuberias.clear();
  auto it = plan.begin();
  while (it != plan.end())
  {
    listaCanalizacionTuberias.push_back({it->fil, it->col, it->op});
    it++;
  }
}
