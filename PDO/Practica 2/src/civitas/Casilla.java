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

    Casilla(String nombre) {
        this.nombre = nombre;
    }

    Casilla(TituloPropiedad titulo){
        /* this.tipo = "CALLE";  // tipo */
    }

    Casilla(float Cantidad,String nombre){
        
    }

    Casilla(int numCasillaCarcel, String nombre){
        
    }

    Casilla(MazoSorpresa mazo, String nombre){
        
    }

    


    /* ----------------- GETTERS / SETTERS ----------------- */

    public String getNombre() {
        return nombre;
    }

    TituloPropiedad getTituloPropiedad(){

    }



    /* ----------------- METODOS ----------------- */

    private void informe(int iActual, /* ¿Jugadores? */){

    }


    private void init(){

    }

    public jugadorCorrecto(int iActual, /*  ?¿ Jugadores */){

    }

    
    void recibeJugador(int iActual,/*  ?¿ Jugadores */){

    }

    private recibeJugador_calle(int iActual,/*  ?¿ Jugadores */){
        
    }

    private recibeJugador_impuesto(int iActual,/*  ?¿ Jugadores */){
        
    }

    private recibeJugador_juez(int iActual,/*  ?¿ Jugadores */){
        
    }

    private recibeJugador_sorpresa(int iActual,/*  ?¿ Jugadores */){
        
    }

    public String toString(){

    }


}
