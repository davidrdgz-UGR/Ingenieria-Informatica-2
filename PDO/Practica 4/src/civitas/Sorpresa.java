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

    /* Para IRCASILLA */
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
        if(tipo == TipoSorpresa.SALIRCARCEL ) this.texto = "Salvoconducto";

        this.valor = -1;
        this.tablero = null;
    }



    /* ----------------- METODOS ----------------- */
    
    void aplicarJugador(int actual, Jugador[] Jugadores){

        /* Hay 6 valores posibles, Casilla | Carcel | PagarCobrar | PorCasaHotel | PorJugador | Salir Carcel */
        switch (this.tipo) { 
            case IRCARCEL -> this.aplicarJugador_irCarcel(actual, Jugadores);
            case IRCASILLA -> this.aplicarJugador_irCasilla(actual, Jugadores);
            case PAGARCOBRAR -> this.aplicarJugador_pagarCobrar(actual, Jugadores);
            case PORCASAHOTEL -> this.aplicarJugador_porCasaHotel(actual, Jugadores);
            case PORJUGADOR -> this.aplicarJugador_porJugador(actual, Jugadores);
            case SALIRCARCEL -> this.aplicarJugador_salirCarcel(actual, Jugadores);
        }
    }

    private void aplicarJugador_irCasilla(int actual, Jugador[] Jugadores){
        if(jugadorCorrecto(actual, Jugadores)){
            informe(actual, Jugadores);
            Diario.getInstance().ocurreEvento("Se ha usado irCasilla en: " + Jugadores[actual].getNombre() );
            

            int casillaActual = Jugadores[actual].getNumCasillaActual();

            int tirada = tablero.calcularTirada(casillaActual, this.valor); /* Falta añadir el numero del dado. ?¿ */

            int nuevaPosicion = tablero.nuevaPosicion(casillaActual, tirada);

            Jugadores[actual].moverACasilla(nuevaPosicion);

            tablero.getCasilla(nuevaPosicion).recibeJugador(actual, Jugadores);   
        }
    }

    private void aplicarJugador_irCarcel(int actual, Jugador[] Jugadores){
        if(jugadorCorrecto(actual, Jugadores)){
            Jugadores[actual].encarcelar( tablero.getCarcel() );/*   Casilla de la carcel  */
            Diario.getInstance().ocurreEvento("Se ha encarcelado al jugador: " + Jugadores[actual].getNombre() );
        }
    }

    private void aplicarJugador_pagarCobrar(int actual, Jugador[] Jugadores){
        if(jugadorCorrecto(actual, Jugadores)){
            informe(actual, Jugadores);
            Diario.getInstance().ocurreEvento("Se ha usado pagarCobrar en: " + Jugadores[actual].getNombre() );
            Jugadores[actual].modificarSaldo(this.valor);

        }
    }

    private void aplicarJugador_porCasaHotel(int actual, Jugador[] Jugadores){

        if (jugadorCorrecto(actual, Jugadores)) {
            informe(actual, Jugadores);
            Diario.getInstance().ocurreEvento("Se ha usado porCasaHotel en: " + Jugadores[actual].getNombre() );

            int numCasasHoteles = Jugadores[actual].cantidadCasasHoteles();

            int cantidad = valor * numCasasHoteles;

            Jugadores[actual].modificarSaldo(cantidad);
    }
}

    private void aplicarJugador_porJugador(int actual, Jugador[] Jugadores){

        if (jugadorCorrecto(actual, Jugadores)) {

            informe(actual, Jugadores);
            Diario.getInstance().ocurreEvento("Se ha usado porJugador en: " + Jugadores[actual].getNombre() );


            int numJugadores = Jugadores.length;

            Sorpresa paga = new Sorpresa(TipoSorpresa.PAGARCOBRAR, -valor, "Paga al jugador " + Jugadores[actual].getNombre());

            for (int i = 0; i < numJugadores; i++) {
                if ( i != actual ) {
                    paga.aplicarJugador(i, Jugadores);
                }
            }

            Sorpresa cobra = new Sorpresa(TipoSorpresa.PAGARCOBRAR,valor * (numJugadores - 1),"Cobra del resto de Jugadores");

            cobra.aplicarJugador(actual, Jugadores);
        }
    }


    private void aplicarJugador_salirCarcel(int actual, Jugador[] Jugadores){
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

    private void informe(int actual, Jugador[] Jugadores){
        Diario.getInstance().ocurreEvento( "Se le está aplicando una sorpresa a: " + Jugadores[actual] );
    }

    public boolean jugadorCorrecto(int actual, Jugador[] Jugadores){
        return (actual >= 0 && actual < Jugadores.length);
    }

    void salirDelMazo(){
        if (tipo == TipoSorpresa.SALIRCARCEL && mazo != null) {
            mazo.inhabilitarCartaEspecial(this);
        }
    }

    @Override
    public String toString() {
        return this.texto;
    }

    void usada(){
        if (tipo == TipoSorpresa.SALIRCARCEL && mazo != null) {
                mazo.habilitarCartaEspecial(this);
        }
    }

    TipoSorpresa getTipoCasilla(){
        return this.tipo;
    }
    
    private void init(){
        this.valor = -1;
    }



}