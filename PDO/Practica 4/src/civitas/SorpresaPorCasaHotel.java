package civitas;

public class SorpresaPorCasaHotel extends Sorpresa{
    
	private int valor;

	/* ----------------- CONSTRUCTORES ----------------- */

	SorpresaPorCasaHotel(int valor, String texto) {
        this.valor = valor;

		super(texto);

    }

    @Override
	public void aplicarAJugador(int actual, Jugador[] Jugadores){

        if (jugadorCorrecto(actual, Jugadores)) {
            informe(actual, Jugadores);
            Diario.getInstance().ocurreEvento("Se ha usado porCasaHotel en: " + Jugadores[actual].getNombre() );

            int numCasasHoteles = Jugadores[actual].cantidadCasasHoteles();

            int cantidad = valor * numCasasHoteles;

            Jugadores[actual].modificarSaldo(cantidad);
    	}

	}

}
