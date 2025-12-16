package civitas;


public abstract class Sorpresa{
    private String texto;    
    protected MazoSorpresa mazo;


    /* ----------------- CONSTRUCTORES ----------------- */

    /* Constructor para herencias */
    Sorpresa(){

    }

    Sorpresa(String texto) {
        this.texto = texto;
        this.mazo = null;
    }

    /* ----------------- METODOS ----------------- */

    abstract void aplicarAJugador(int actual, Jugador[] jugadores);

    protected  void informe(int actual, Jugador[] Jugadores){
        Diario.getInstance().ocurreEvento( "Se le está aplicando una sorpresa a: " + Jugadores[actual] );
    }

    public boolean jugadorCorrecto(int actual, Jugador[] Jugadores){
        return (actual >= 0 && actual < Jugadores.length);
    }

    void salirDelMazo(){
        if ((this instanceof SorpresaSalirCarcel ) && mazo != null) {
            mazo.inhabilitarCartaEspecial(this);
        }
    }

    @Override
    public String toString() {
        return this.texto;
    }

    void usada(){
        if ( (this instanceof SorpresaSalirCarcel ) && mazo != null) {
                mazo.habilitarCartaEspecial(this);
        }
    }



}