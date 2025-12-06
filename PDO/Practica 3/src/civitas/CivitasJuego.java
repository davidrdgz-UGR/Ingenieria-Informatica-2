package civitas;

import java.util.ArrayList;
import java.util.Arrays;
// import java.util.Collections;

public class CivitasJuego {
    
    private int indiceJugadorActual;

    private Jugador jugadores[]; /* Tiene que ser un array con todos los jugadores */
    private EstadosJuego estado;
    private GestorEstados gestorEstados;
    private Tablero tablero;
    OperacionesJuego tipoOperacion;
    private static final Dado dado = Dado.getInstance();
    private MazoSorpresa mazo;

    private int indiceJugadorActual;


    /* ---------------- CONSTRUCTOR ---------------- */

    CivitasJuego(ArrayList<String> nombres) {

        this.jugadores = new Jugador[nombres.size()];

        for (int i = 0; i < nombres.size(); i++) {
            this.jugadores[i] = new Jugador(nombres.get(i));
        }

        this.gestorEstados = new GestorEstados();
        this.estado = gestorEstados.estadoInicial();

        this.indiceJugadorActual = dado.quienEmpieza(this.jugadores.length);

        this.mazo = new MazoSorpresa();

        this.inicializarTablero(this.mazo); /* Ahora mismo tablero es null */

        this.inicializarMazoSorpresa(this.tablero);
    }
    
    
    
    
    
    /* ---------------- METODOS ---------------- */

    void actualizarInfo() {
        Jugador jugadorActual = jugadores[indiceJugadorActual];

        System.out.println("=== INFORMACIÓN DEL JUGADOR ACTUAL ===");
        System.out.println(jugadorActual.toString());

        System.out.println("\n=== CASILLA ACTUAL ===");
        int pos = jugadorActual.getNumCasillaActual();
        System.out.println(tablero.getCasilla(pos).toString());

        if (jugadorActual.enBancarrota()) {
            System.out.println("\n*** EL JUGADOR HA CAÍDO EN BANCARROTA ***");
            System.out.println("=== RANKING FINAL ===");
            System.out.println(ranking());   // lo implementas más adelante
        }
    }


    /* SIGUIENTE PRACTICA */
    private void avanzaJugador(){

    }

    public boolean hipotecar(int ip){
        Jugador jugadorActual = this.jugadores[indiceJugadorActual];
        return jugadorActual.hipotecar(ip);
    }

    public boolean cancelarHipoteca(int ip){
        Jugador jugadorActual = this.jugadores[indiceJugadorActual];
        return jugadorActual.cancelarHipoteca(ip);
    }

    /* SIGUIENTE PRACTICA */
    public boolean comprar(){

        return true;
    }

    public boolean comprarCasa(int ip){
        Jugador jugadorActual = this.jugadores[indiceJugadorActual];

        return jugadorActual.construirCasa(ip);
    }   

    public boolean comprarHotel(int ip){
        Jugador jugadorActual = this.jugadores[indiceJugadorActual];

        return jugadorActual.construirHotel(ip);
    }

    private void contabilizarPasosPorSalida(Jugador jugadorActual){
        while (this.tablero.getPorSalida() > 0) {
            jugadorActual.pasaPorSalida();
        }
    }

    public boolean finalDelJuego(){
        for (Jugador jugador : this.jugadores) {
                if (jugador.enBancarrota()) {
                    return true;
                }
            }
        return false;
    }

    public String infoJugadorTexto(){
        return this.jugadores[indiceJugadorActual].toString();
    }

    /* REVISAR + Ver Reglas */
    private void inicializarMazoSorpresa(Tablero tablero) {

        if (this.mazo == null) this.mazo = new MazoSorpresa();

        this.mazo.alMazo(new Sorpresa(TipoSorpresa.IRCARCEL,tablero,tablero.getCarcel(),"Vas directo a la cárcel"));
        this.mazo.alMazo(new Sorpresa(TipoSorpresa.IRCASILLA,tablero,3,"Te mueves a la casilla 3"));

        this.mazo.alMazo(new Sorpresa(TipoSorpresa.PAGARCOBRAR,-200,"Pagas 200"));
        this.mazo.alMazo(new Sorpresa(TipoSorpresa.PAGARCOBRAR,200,"Cobras 200"));

        this.mazo.alMazo(new Sorpresa(TipoSorpresa.PORCASAHOTEL,50,"Cobras 50 por cada casa y hotel"));
        this.mazo.alMazo(new Sorpresa(TipoSorpresa.PORJUGADOR,100,"Cada jugador te paga 100"));

        this.mazo.alMazo(new Sorpresa(TipoSorpresa.SALIRCARCEL,this.mazo));
    }  
    
    private void inicializarTablero(MazoSorpresa mazo){
        int numCasillaCarcel = 5;
        this.tablero = new Tablero(numCasillaCarcel);


        /* TABLERO PROVISIONAL */
        
        /* 1 */tablero.añadeCasilla(new Casilla("SALIDA"));
        /* 2 */tablero.añadeCasilla(new Casilla(new TituloPropiedad("calle1",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 3 */tablero.añadeCasilla(new Casilla(new TituloPropiedad("calle2",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 4 */tablero.añadeCasilla(new Casilla(new TituloPropiedad("calle3",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 5 */tablero.añadeCasilla(new Casilla(new TituloPropiedad("calle4",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 6 */tablero.añadeCasilla(new Casilla(new TituloPropiedad("calle5",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 7 */tablero.añadeCasilla(new Casilla(new TituloPropiedad("calle6",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 8 */tablero.añadeCasilla(new Casilla(new TituloPropiedad("calle7",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 9 */tablero.añadeCasilla(new Casilla(new TituloPropiedad("calle8",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 10 */tablero.añadeCasilla(new Casilla(15,"JUEZ"));
        /* 11 */tablero.añadeCasilla(new Casilla(new TituloPropiedad("calle11",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 12 */tablero.añadeCasilla(new Casilla(new TituloPropiedad("calle12",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 13 */tablero.añadeCasilla(new Casilla(new TituloPropiedad("calle13",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 14 */tablero.añadeCasilla(new Casilla(new TituloPropiedad("calle14",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 15 */tablero.añadeCasilla(new Casilla("CARCEL"));
        /* 16 */tablero.añadeCasilla(new Casilla(new MazoSorpresa(),"SORPRESA"));
        /* 17 */tablero.añadeCasilla(new Casilla(new TituloPropiedad("calle17",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 18 */tablero.añadeCasilla(new Casilla(new TituloPropiedad("calle18",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 19 */tablero.añadeCasilla(new Casilla(new TituloPropiedad("calle19",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 20 */tablero.añadeCasilla(new Casilla((float) 250.00,"IMPUESTO"));
        

    }         

    private void pasarTurno(){
        this.indiceJugadorActual = (this.indiceJugadorActual + 1) % jugadores.length;
    }

    private Jugador[] ranking() {

        Jugador[] copiaJugadores = jugadores.clone(); /* Con .clone() se copia el array. */

        Arrays.sort(copiaJugadores); /* Se supone que ordena por saldo gracias a compareTo, ya que sobreescribe un método existente. */

        return copiaJugadores;
    }

    public boolean salirCarcelPagando(){
        Jugador jugadorActual = this.jugadores[indiceJugadorActual];
        return jugadorActual.salirCarcelPagando();
    }

    public boolean salirCarcelTirando(){
        Jugador jugadorActual = this.jugadores[indiceJugadorActual];
        return jugadorActual.salirCarcelTirando();
    }

    /* SIGUIENTE PRACTICA */
    /* public OperacionesJuego siguientePaso(){
            
    } */

    public void siguientePasoCompletado(OperacionesJuego operacion){
        Jugador jugadorActual = this.jugadores[indiceJugadorActual];

        this.estado = gestorEstados.siguienteEstado(jugadorActual, this.estado, operacion);
    }

    public boolean vender(int ip){
        Jugador jugadorActual = this.jugadores[indiceJugadorActual];
        return jugadorActual.vender(ip);
    }




    
    /* ---------------- SETTERS / GETTERS ---------------- */

    public Casilla getCasillaActual(){
        return this.tablero.getCasilla(this.indiceJugadorActual);
    }

    public Jugador getJugadorActual(){
        return this.jugadores[this.indiceJugadorActual];
    }

}
