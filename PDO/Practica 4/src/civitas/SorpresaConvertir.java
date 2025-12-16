package civitas;

public class SorpresaConvertir extends Sorpresa {

    private final float fianza;

    /* ----------------- CONSTRUCTOR ----------------- */
    public SorpresaConvertir(float fianza, String texto) {
        super(texto);
        this.fianza = fianza;
    }

    /* ----------------- APLICAR ----------------- */
	@Override
    void aplicarAJugador(int actual, Jugador[] jugadores) {
        if (!jugadorCorrecto(actual, jugadores)) return;

        Jugador jugador = jugadores[actual];

        // Evita convertir dos veces (si ya es especulador)
        if (jugador instanceof JugadorEspeculador) {
            Diario.getInstance().ocurreEvento("El jugador " + jugador.getNombre() + " ya es ESPECULADOR.");
            return;
        }

        JugadorEspeculador nuevo = new JugadorEspeculador(jugador, fianza);

        // Sustitución en el array (esto ES la conversión real)
        jugadores[actual] = nuevo;

        Diario.getInstance().ocurreEvento(
            "El jugador " + jugador.getNombre() + " se convierte en ESPECULADOR con fianza " + fianza
        );
    }
}