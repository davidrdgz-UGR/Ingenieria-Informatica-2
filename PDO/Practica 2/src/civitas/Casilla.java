package civitas;

public class Casilla {
    
        
    private int carcel;                     /* DUDA: se podría poner como tipo casilla ??  */
    private float importe;
    private String nombre;
    
    TipoCasilla tipo;
    TituloPropiedad tituloPropiedad;    /*  tituloPropiedad tipo="CALLE"  ?¿?¿? */
    Sorpresa sorpresa;                  /* tipo = "SORPRESA" */
    MazoSorpresa mazo;                  /* tipo = "SORPRESA" */
    


    /* ----------------- Constructores ----------------- */

    /* REVISAR CONSTRUCTORES */
    
    Casilla(String nombre) {
        this.init();
        this.nombre = nombre;

    }

    Casilla(TituloPropiedad titulo){
        this.init();
        
        this.tituloPropiedad = titulo;
        this.nombre = titulo.getNombre();
        this.tipo = TipoCasilla.CALLE;
        
    }

    Casilla(float cantidad,String nombre){
        this.init();
        
        this.importe = cantidad;
        this.nombre = nombre;
        this.tipo = TipoCasilla.IMPUESTO;
        
    }

    Casilla(int numCasillaCarcel, String nombre){
        this.init();
        
        this.carcel = numCasillaCarcel;
        this.nombre = nombre;
        this.tipo = TipoCasilla.JUEZ;
        
    }

    Casilla(MazoSorpresa mazo, String nombre){
        this.init();
        
        this.mazo = mazo;
        this.nombre = nombre;
        this.tipo = TipoCasilla.SORPRESA;
        // this.sorpresa = mazo.siguiente();
        
        
    }

    






    /* ----------------- METODOS ----------------- */

    private void informe(int iActual, Jugador[] Jugadores){
        Diario.getInstance().ocurreEvento("El jugador " + Jugadores[iActual].getNombre() + " ha caído en la casilla: " + toString());
    }


    private void init(){
        this.nombre = "";
        this.importe = 0.0f;
        this.carcel = -1;
        this.tipo = TipoCasilla.DESCANSO;
        this.tituloPropiedad = null;
        this.sorpresa = null;
        this.mazo = null;
    }

    public boolean jugadorCorrecto(int iActual,  Jugador[] Jugadores){
        return iActual >= 0 && iActual < Jugadores.length;  /* Ya existe una de estas en:  Sopresa | ?¿?¿ */
    }

    
    void recibeJugador(int iActual, Jugador[] Jugadores){

        /* Se debería poner en la siguiente práctica  */
        /* switch (this.tipo) {

            case CALLE -> this.recibeJugador_calle(iActual, Jugadores);
            case IMPUESTO -> this.recibeJugador_impuesto(iActual, Jugadores);
            case JUEZ -> this.recibeJugador_juez(iActual, Jugadores);
            case SORPRESA -> this.recibeJugador_sorpresa(iActual, Jugadores);
            case DESCANSO -> {
                if (jugadorCorrecto(iActual, Jugadores))
                    informe(iActual, Jugadores);
            }
        } */
    }

    private void recibeJugador_calle(int iActual, Jugador[] Jugadores){
        /* if (jugadorCorrecto(iActual, Jugadores)) {
            informe(iActual, Jugadores);
            Diario.getInstance().ocurreEvento("El jugador " + Jugadores[iActual].getNombre() + " ha recibido: " + this.tituloPropiedad.getNombre()  );
            tituloPropiedad.tramitarAlquiler(Jugadores[iActual]);
        } */
    }

    private void recibeJugador_impuesto(int iActual, Jugador[] Jugadores){
        if (jugadorCorrecto(iActual, Jugadores)) {
            informe(iActual, Jugadores);
            Diario.getInstance().ocurreEvento("El jugador " + Jugadores[iActual].getNombre() + " ha caido en: " + this.nombre );

            Jugadores[iActual].pagaImpuesto(importe);
        }
    }

    private void recibeJugador_juez(int iActual, Jugador[] Jugadores){
        if (jugadorCorrecto(iActual, Jugadores)) {
            informe(iActual, Jugadores);
            Jugadores[iActual].encarcelar(carcel);
        }
    }

    private void recibeJugador_sorpresa(int iActual, Jugador[] Jugadores){
        /* if (jugadorCorrecto(iActual, Jugadores)) {
            informe(iActual, Jugadores);
            sorpresa = mazo.siguiente();
            sorpresa.aplicarJugador(iActual, Jugadores);
        } */
    }
    
    @Override
    public String toString(){
        String info = "Casilla{" +
                        "nombre='" + this.nombre + '\'' +
                        ", tipo=" + this.tipo;

            switch (this.tipo) {
                case CALLE -> info += ", titulo=" + tituloPropiedad.getNombre();
                case IMPUESTO -> info += ", importe=" + this.importe;
                case JUEZ -> info += ", carcel=" + this.carcel;
                case SORPRESA -> info += ", mazoSorpresas";
                case DESCANSO -> info += ", casilla normal";
            }

            info += "}";
            return info;
    }

    
    /* ----------------- GETTERS / SETTERS ----------------- */

    public String getNombre() {
        return this.nombre;
    }

    TituloPropiedad getTituloPropiedad(){
        return this.tituloPropiedad;
    }

}
