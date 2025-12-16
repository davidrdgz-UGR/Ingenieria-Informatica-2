package civitas;

public class Casilla {
    
        
    // private int carcel;                     /* DUDA: se podría poner como tipo casilla ??  */
    // private float importe;
    private String nombre;
    
    // TipoCasilla tipo;
    // TituloPropiedad tituloPropiedad;    /*  tituloPropiedad tipo="CALLE"  ?¿?¿? */
    // Sorpresa sorpresa;                  /* tipo = "SORPRESA" */
    // MazoSorpresa mazo;                  /* tipo = "SORPRESA" */
    


    /* ----------------- Constructores ----------------- */

    /* REVISAR CONSTRUCTORES */
    
    /* Constructor para herencias */
    Casilla (){

    }

    public Casilla(String nombre) {
        // this.init();
        this.nombre = nombre;
        // this.tipo = TipoCasilla.DESCANSO;
        
    }


    /* ----------------- METODOS ----------------- */

    protected void informe(int iActual, Jugador[] Jugadores){
        Diario.getInstance().ocurreEvento("El jugador " + Jugadores[iActual].getNombre() + " ha caído en la casilla: " + toString());
    }




    public boolean jugadorCorrecto(int iActual,  Jugador[] Jugadores){
        return iActual >= 0 && iActual < Jugadores.length;  /* Ya existe una de estas en:  Sopresa | ?¿?¿ */
    }


    void recibeJugador(int iActual, Jugador[] Jugadores){
        if (jugadorCorrecto(iActual, Jugadores)){ 
            informe(iActual, Jugadores);
        }        
    }
    

    @Override
    public String toString(){
        String info = "Casilla{" +
                        "nombre='" + this.nombre + '\'' + "}";
            return info;
    }
    
    /* ----------------- GETTERS / SETTERS ----------------- */

    public String getNombre() {
        return this.nombre;
    }
}
