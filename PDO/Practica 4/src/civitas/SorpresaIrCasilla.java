package civitas;

public class SorpresaIrCasilla extends Sorpresa{
    
    Tablero tablero;
	private int valor;
	
	/* ----------------- CONSTRUCTORES ----------------- */

	/* Para IRCASILLA */
    SorpresaIrCasilla(Tablero tablero,String texto,int valor) {
        
		this.tablero = tablero;
        this.valor = valor;

		super(texto);

    }


    @Override
	public void aplicarAJugador(int actual, Jugador[] Jugadores){
        if(jugadorCorrecto(actual, Jugadores)){
            informe(actual, Jugadores);
            Diario.getInstance().ocurreEvento("Se ha usado irCasilla en: " + Jugadores[actual].getNombre() );
            

            int casillaActual = Jugadores[actual].getNumCasillaActual();

            int tirada = tablero.calcularTirada(casillaActual, this.valor); /* Falta añadir el numero del dado. ?¿ */

            int nuevaPosicion = tablero.nuevaPosicion(casillaActual, tirada);

            Jugadores[actual].moverACasilla(nuevaPosicion);

            tablero.getCasilla(nuevaPosicion).recibeJugador(actual, Jugadores);   
        }
    }
}
