/* AÑADIDO EN P2 */

package civitas;

class GestorEstados {

  /* No tiene atributos por lo que no hace falta tener un constructor, se genera un objeto solo para usar sus métodos */
  
  EstadosJuego estadoInicial() {
    return (EstadosJuego.INICIO_TURNO);
  }
  
  OperacionesJuego operacionesPermitidas(Jugador jugador, EstadosJuego estado) {
    OperacionesJuego op = null;

    switch (estado) {
      case INICIO_TURNO -> {
        op = jugador.encarcelado ? OperacionesJuego.SALIR_CARCEL : OperacionesJuego.AVANZAR;
      }

      case DESPUES_CARCEL -> {
        op = OperacionesJuego.PASAR_TURNO;
      }

      case DESPUES_AVANZAR -> {
        if (jugador.encarcelado)
          op = OperacionesJuego.PASAR_TURNO;
        else if (jugador.getPuedeComprar())
          op = OperacionesJuego.COMPRAR;
        else if (jugador.tieneAlgoQueGestionar())
          op = OperacionesJuego.GESTIONAR;
        else
          op = OperacionesJuego.PASAR_TURNO;
      }

      case DESPUES_COMPRAR -> {
        if (jugador.tieneAlgoQueGestionar())
          op = OperacionesJuego.GESTIONAR;
        else
          op = OperacionesJuego.PASAR_TURNO;
      }

      case DESPUES_GESTIONAR -> {
        op = OperacionesJuego.PASAR_TURNO;
      }       
    }

    return op;
  }
  
  EstadosJuego siguienteEstado (Jugador jugador, EstadosJuego estado, OperacionesJuego operacion) {
    EstadosJuego siguienteEstado = null;

    switch (estado) {
      
      case INICIO_TURNO -> {
          if (operacion==OperacionesJuego.SALIR_CARCEL)
            siguienteEstado = EstadosJuego.DESPUES_CARCEL;
          else if (operacion==OperacionesJuego.AVANZAR)
            siguienteEstado = EstadosJuego.DESPUES_AVANZAR;
      }

      case DESPUES_CARCEL -> {
          if (operacion==OperacionesJuego.PASAR_TURNO)
            siguienteEstado = EstadosJuego.INICIO_TURNO;
      }

      case DESPUES_AVANZAR -> {
          
        switch (operacion) {
              case PASAR_TURNO -> siguienteEstado = EstadosJuego.INICIO_TURNO;
              case COMPRAR -> siguienteEstado = EstadosJuego.DESPUES_COMPRAR;
              case GESTIONAR -> siguienteEstado = EstadosJuego.DESPUES_GESTIONAR;
          }
      }

      case DESPUES_COMPRAR -> {
        if (operacion==OperacionesJuego.GESTIONAR)
          siguienteEstado = EstadosJuego.DESPUES_GESTIONAR;
        else if (operacion==OperacionesJuego.PASAR_TURNO)
          siguienteEstado = EstadosJuego.INICIO_TURNO;
      }

      case DESPUES_GESTIONAR -> {
        if (operacion==OperacionesJuego.PASAR_TURNO)
          siguienteEstado = EstadosJuego.INICIO_TURNO;
      }
    }

    Diario.getInstance().ocurreEvento("De: "+estado.toString()+ " con "+operacion.toString()+ " sale: "+siguienteEstado.toString());

    return siguienteEstado;
  }

}