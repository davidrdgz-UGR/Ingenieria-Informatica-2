package civitas;

public class SorpresaSalirCarcel extends Sorpresa{

	

	/* ----------------- CONSTRUCTORES ----------------- */

	SorpresaSalirCarcel(MazoSorpresa mazo, String texto) {

        super(texto);
    }


    @Override
	public void aplicarAJugador(int actual, Jugador[] Jugadores){
        if (jugadorCorrecto(actual, Jugadores)) {

            informe(actual, Jugadores);
            Diario.getInstance().ocurreEvento("Se ha usado salirCarcel en: " + Jugadores[actual].getNombre() );


            boolean alguienTieneSalvoconducto = false;

            for (int i = 0; i < Jugadores.length && !alguienTieneSalvoconducto; i++) {
                if (Jugadores[i].tieneSalvoconducto()) {
                    alguienTieneSalvoconducto = true;
                }
            }

            if (!alguienTieneSalvoconducto) {
                Jugadores[actual].obtenerSalvoconducto(this);
                salirDelMazo();
            }
        }
    }

}
