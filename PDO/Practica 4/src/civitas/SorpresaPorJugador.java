package civitas;

public class SorpresaPorJugador extends Sorpresa {
    
	private int valor;


	/* ----------------- CONSTRUCTORES ----------------- */

	SorpresaPorJugador( int valor, String texto) {
        
        this.valor = valor;
        
		super(texto);

    }

    @Override
	public void aplicarAJugador(int actual, Jugador[] Jugadores){

        if (jugadorCorrecto(actual, Jugadores)) {

            informe(actual, Jugadores);
            Diario.getInstance().ocurreEvento("Se ha usado porJugador en: " + Jugadores[actual].getNombre() );


            int numJugadores = Jugadores.length;

            SorpresaPagarCobrar paga = new SorpresaPagarCobrar( -valor, "Paga al jugador " + Jugadores[actual].getNombre());

            for (int i = 0; i < numJugadores; i++) {
                if ( i != actual ) {
                    paga.aplicarAJugador(actual, Jugadores);
                }
            }

            SorpresaPagarCobrar cobra = new SorpresaPagarCobrar(valor * (numJugadores - 1),"Cobra del resto de Jugadores");

            cobra.aplicarAJugador(actual, Jugadores);
        }
    }

}
