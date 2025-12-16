package civitas;

public class SorpresaIrCarcel extends Sorpresa {
    
    Tablero tablero;

	/* ----------------- CONSTRUCTORES ----------------- */

	/* Para IRCASILLA */
    SorpresaIrCarcel(Tablero tablero,String texto) {
        
        this.tablero = tablero;

		super(texto);

    }


    @Override
	public void aplicarAJugador(int actual, Jugador[] Jugadores){
        if(jugadorCorrecto(actual, Jugadores)){
            Jugadores[actual].encarcelar( tablero.getCarcel() );/*   Casilla de la carcel  */
            Diario.getInstance().ocurreEvento("Se ha encarcelado al jugador: " + Jugadores[actual].getNombre() );
        }
    }
}
