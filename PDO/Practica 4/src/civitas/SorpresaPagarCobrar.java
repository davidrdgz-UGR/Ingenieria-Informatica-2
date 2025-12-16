package civitas;

public class SorpresaPagarCobrar extends Sorpresa {

	private int valor;

	
	/* ----------------- CONSTRUCTORES ----------------- */

	SorpresaPagarCobrar(int valor, String texto) {

        this.valor = valor;
		super(texto);

    }

    @Override
	public void aplicarAJugador(int actual, Jugador[] Jugadores){
        if(jugadorCorrecto(actual, Jugadores)){
            informe(actual, Jugadores);
            Diario.getInstance().ocurreEvento("Se ha usado pagarCobrar en: " + Jugadores[actual].getNombre() );
            Jugadores[actual].modificarSaldo(this.valor);

        }
    }

}
