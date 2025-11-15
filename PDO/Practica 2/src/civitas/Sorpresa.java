package civitas;


class Sorpresa{
    private String texto;
    private int valor;
    
    TipoSorpresa tipo;
    MazoSorpresa mazo;
    Tablero tablero;


    /* ----------------- CONSTRUCTORES ----------------- */

    Sorpresa(TipoSorpresa tipo, Tablero tablero) {
        this.init();
        this.tipo = tipo;
        this.tablero = tablero;

        this.texto = "";
        this.valor = -1;  
        this.mazo = null;
    }

    Sorpresa(TipoSorpresa tipo, Tablero tablero, int valor, String texto) {
        this.init();
        this.tipo = tipo;
        this.tablero = tablero;
        this.valor = valor;
        this.texto = texto;

        this.mazo = null;
    }

    Sorpresa(TipoSorpresa tipo, int valor, String texto) {
        this.init();
        this.tipo = tipo;
        this.valor = valor;
        this.texto = texto;

        this.tablero = null;
        this.mazo = null;
    }

    Sorpresa(TipoSorpresa tipo, MazoSorpresa mazo) {
        this.init();
        this.tipo = tipo;
        this.mazo = mazo;

        this.texto = "";
        this.valor = -1;
        this.tablero = null;
    }



    /* ----------------- METODOS ----------------- */
    
    void aplicarJugador(int actual, Jugador[] Jugadores){
        /* ¿Le falta pasar algun valor? */

        switch (this.tipo) {
            /* Hay 6 valores posibles, Casilla | Carcel | PagarCobrar | PorCasaHotel | PorJugador | Salir Carcel */
            case :
                
                break;
            
            case :
                
                break;

            case :
                
                break;

            case :
                
                break;

            case :
                
                break;

            case :
                
                break;

            default:
                throw new AssertionError();
        }
    }

    private void aplicarJugador_irCasilla(int actual, Jugador[] Jugadores){

    }

    private void aplicarJugador_irCarcel(int actual, Jugador[] Jugadores){

    }

    private void aplicarJugador_pagarCobrar(int actual, Jugador[] Jugadores){

    }

    private void aplicarJugador_porCasaHotel(int actual, Jugador[] Jugadores){

    }

    private void aplicarJugador_porJugador(int actual, Jugador[] Jugadores){

    }

    private void aplicarJugador_salirCarcel(int actual, Jugador[] Jugadores){

    }

    private void informe(int actual, Jugador[] Jugadores){
        Diario.getInstance().ocurreEvento( "Se le está aplicando una sorpresa a: " + Jugadores[actual] );
    }

    public boolean jugadorCorrecto(int actual, Jugador[] Jugadores){
        return (actual >= 0 && actual < Jugadores.size()) ? true : false;
    }

    void salirDelMazo(){

    }

    public String toString(){

    }

    void usada(){

    }
    
    private void init(){
        this.valor = -1;
    }



}