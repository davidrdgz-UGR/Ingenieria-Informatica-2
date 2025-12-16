package civitas;

public class CasillaJuez extends Casilla{
    


	private int carcel;

    /* ----------------- Constructores ----------------- */

	CasillaJuez(int numCasillaCarcel, String nombre){
        
		super(nombre);

        this.carcel = numCasillaCarcel;
        
    }


	/* ----------------- MODULOS ----------------- */

    @Override
	void recibeJugador(int iActual, Jugador[] Jugadores){
        if (jugadorCorrecto(iActual, Jugadores)) {
            informe(iActual, Jugadores);
            Jugadores[iActual].encarcelar(carcel);
        }
    }

    @Override
    public String toString(){
        String info = "Casilla{" +
                        "nombre='" + this.getNombre() + '\'' + ", carcel=" + this.carcel + "}";
        return info;
    }

}