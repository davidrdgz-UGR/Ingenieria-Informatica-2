package civitas;

public class CasillaCalle extends Casilla {
    

	TituloPropiedad tituloPropiedad;


    /* ----------------- Constructores ----------------- */

	CasillaCalle(TituloPropiedad titulo){
        
		super(titulo.getNombre());
		this.tituloPropiedad = titulo;
        
    }



	/* ----------------- MODULOS ----------------- */
    @Override
	void recibeJugador(int iActual, Jugador[] Jugadores){
        if (jugadorCorrecto(iActual, Jugadores)) {
            informe(iActual, Jugadores);

            // System.out.println("\n recibirjugador_calle - tiene propietario" + tituloPropiedad.tienePropietario());
            
            if (!tituloPropiedad.tienePropietario() /* && this.tipo != TipoCasilla.CALLE */ ) {
                Jugadores[iActual].puedeComprarCasilla();
                // Diario.getInstance().ocurreEvento("El jugador " + Jugadores[iActual].getNombre() + " ha recibido: " + this.tituloPropiedad.getNombre()  );


            } else {
                
                // System.out.println("\n Entada a recibir calle - tramitarAlquiler \n");
                tituloPropiedad.tramitarAlquiler(Jugadores[iActual]);
                
            }
        }
    }

    @Override
    public String toString(){
        String info = "Casilla{" +
                        "nombre='" + this.getNombre() + '\'' + ", titulo=" + tituloPropiedad.getNombre() + "}";
        return info;
    }



    TituloPropiedad getTituloPropiedad(){
        return this.tituloPropiedad;
    }
}
