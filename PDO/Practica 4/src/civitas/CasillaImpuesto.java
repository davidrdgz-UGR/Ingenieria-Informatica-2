package civitas;

public class CasillaImpuesto  extends Casilla {
    
	private float importe;
	
	

    /* ----------------- Constructores ----------------- */

	CasillaImpuesto(float cantidad,String nombre){
        
        this.importe = cantidad;
        super(nombre);        
    }


	/* ----------------- MODULOS ----------------- */

    @Override
	void recibeJugador(int iActual, Jugador[] Jugadores){
        if (jugadorCorrecto(iActual, Jugadores)) {
            informe(iActual, Jugadores);
            Diario.getInstance().ocurreEvento("El jugador " + Jugadores[iActual].getNombre() + " ha caido en: " + this.getNombre() );

            Jugadores[iActual].pagaImpuesto(importe);
        }
    }

    @Override
    public String toString(){
        String info = "Casilla{" +
                        "nombre='" + this.getNombre() + '\'' + ", importe= " + this.importe + "}";
        return info;
    }

}
