package civitas;

public class CasillaSorpresa extends Casilla {

	Sorpresa sorpresa;
	MazoSorpresa mazo;



    /* ----------------- Constructores ----------------- */

	CasillaSorpresa(MazoSorpresa mazo, String nombre){
        
		super(nombre);
        this.mazo = mazo;
        
    }



	/* ----------------- MODULOS ----------------- */

    @Override
    void recibeJugador(int iActual, Jugador[] Jugadores){
        if (jugadorCorrecto(iActual, Jugadores)) {
            informe(iActual, Jugadores);
            this.sorpresa = this.mazo.siguiente();
            this.sorpresa.aplicarAJugador(iActual, Jugadores);
        }
    }

    @Override
    public String toString(){
        String info = "Casilla{" +
                        "nombre='" + this.getNombre() + '\'' + ", mazoSorpresas" + "}";
        return info;
    }
}
