package civitas;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;


public class CivitasJuego {

    private Jugador jugadores[]; /* Tiene que ser un array con todos los jugadores */
    private EstadosJuego estado;
    private GestorEstados gestorEstados;
    private Tablero tablero;
    OperacionesJuego tipoOperacion;
    private static final Dado dado = Dado.getInstance();
    private MazoSorpresa mazo;

    private int indiceJugadorActual;


    /* ---------------- CONSTRUCTOR ---------------- */

    /* Se supone que es DE PAQUETE pero se necesita public para usarlo en el main. */
    public CivitasJuego(ArrayList<String> nombres) {

        this.jugadores = new Jugador[nombres.size()];

        for (int i = 0; i < nombres.size(); i++) {
            this.jugadores[i] = new Jugador(nombres.get(i));

            // System.out.println("\n Creado jugador: " + this.jugadores[i].getNombre() + "\n");
            // System.out.println(this.jugadores[i].toString());

        }

        this.gestorEstados = new GestorEstados();   
        this.estado = gestorEstados.estadoInicial();    /* Inicializa estado a "INICIO_TURNO" */
            // System.out.println("\n" + this.estado  + "\n");

        this.indiceJugadorActual = dado.quienEmpieza(this.jugadores.length);

        
        this.mazo = new MazoSorpresa();

        this.inicializarTablero(this.mazo); 

        this.inicializarMazoSorpresa(this.tablero);
    }
    
    
    
    
    
    /* ---------------- METODOS ---------------- */

    void actualizarInfo() {
        Jugador jugadorActual = jugadores[indiceJugadorActual];

        System.out.println("=== INFORMACIÓN DEL JUGADOR ACTUAL ===");
        System.out.println(jugadorActual.toString());

        System.out.println("\n=== CASILLA ACTUAL ===");
        int pos = jugadorActual.getNumCasillaActual();
        System.out.println(tablero.getCasilla(pos).toString()); /* Aunque no sea ninguna de las herencias nos sirve como muestra */

        if (jugadorActual.enBancarrota()) {
            System.out.println("\n*** EL JUGADOR HA CAÍDO EN BANCARROTA ***");
            System.out.println("=== RANKING FINAL ===");
            System.out.println(ranking());   // lo implementas más adelante
        }
    }


    /* SIGUIENTE PRACTICA */
    private void avanzaJugador(){

        Jugador jugadorActual = this.jugadores[this.indiceJugadorActual];

        int posicionActual = jugadorActual.getNumCasillaActual();

        int tirada = Dado.getInstance().tirar();

        int posicionNueva = tablero.nuevaPosicion(posicionActual, tirada);

        jugadorActual.setNumCasillaActual( posicionNueva );


        // System.out.println("Comprobacion avanzaJugador: " + jugadorActual.getNombre() + " - " + posicionActual + " - " + posicionNueva + " - " + this.tablero.getCasilla(posicionNueva).getNombre());
        
        contabilizarPasosPorSalida(jugadorActual);
        
        // jugadorActual.moverACasilla(posicionNueva);
        this.tablero.getCasilla(posicionNueva).recibeJugador(this.indiceJugadorActual,this.jugadores);

        this.tablero.getCasilla(posicionNueva).recibeJugador(this.indiceJugadorActual, this.jugadores);
        contabilizarPasosPorSalida(jugadorActual);

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

        Jugador jugador = getJugadorActual();
        Casilla casilla = this.tablero.getCasilla(jugador.getNumCasillaActual());
        // TituloPropiedad titulo = casilla.getTituloPropiedad();
        
        if (!(casilla instanceof CasillaCalle)) {
            return false; 
        }

        CasillaCalle calle = (CasillaCalle) casilla;
        TituloPropiedad titulo = calle.getTituloPropiedad();


        return jugador.comprar(titulo);

        
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

        /* En principio mazo no va a ser null, pero por si acaso */
        // System.out.println( this.mazo );

        if (this.mazo == null) {
            // System.out.println("Comprobacion");
            this.mazo = new MazoSorpresa();
        }

        /* Esto se debe ajustar en otro sitio */
        Random r = new Random();
        int casillaAleatoria = r.nextInt(20);


        this.mazo.alMazo(new SorpresaIrCarcel(tablero,"Vas directo a la cárcel"));
        this.mazo.alMazo(new SorpresaIrCasilla(tablero ,"Te mueves a la casilla "+ casillaAleatoria, casillaAleatoria));
        this.mazo.alMazo(new SorpresaPagarCobrar(-200,"Pagas 200"));
        this.mazo.alMazo(new SorpresaPagarCobrar(200,"Cobras 200"));
        this.mazo.alMazo(new SorpresaPorCasaHotel(50,"Cobras 50 por cada casa y hotel"));
        this.mazo.alMazo(new SorpresaPorJugador(100,"Cada jugador te paga 100"));
        this.mazo.alMazo(new SorpresaSalirCarcel(this.mazo,"SalvodConducto"));
        this.mazo.alMazo(new SorpresaConvertir(3000f,"El jugador/a " + this.jugadores[this.indiceJugadorActual].getNombre() + " se ha convertido en un Especulador"));
        

        // this.mazo.revisarMazo();
    }  
    
    private void inicializarTablero(MazoSorpresa mazo){
        int numCasillaCarcel = 14;
        this.tablero = new Tablero(numCasillaCarcel);


        /* TABLERO PROVISIONAL */
        
        /*  0 */tablero.añadeCasilla(new Casilla("SALIDA")); /* Ya se crea por defecto, no hace falta. */
        /*  1 */tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("calle1",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /*  2 */tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("calle2",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /*  3 */tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("calle3",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /*  4 */tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("calle4",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /*  5 */tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("calle5",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /*  6 */tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("calle6",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /*  7 */tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("calle7",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /*  8 */tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("calle8",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /*  9 */tablero.añadeCasilla(new CasillaJuez(14,"JUEZ"));
        /* 10 */tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("calle10",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 11 */tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("calle11",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 12 */tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("calle12",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 13 */tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("calle13",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 14 */tablero.añadeCasilla(new Casilla("CARCEL"));
        /* 15 */tablero.añadeCasilla(new CasillaSorpresa( mazo /* this.mazo */ ,"SORPRESA"));
        /* 16 */tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("calle16",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 17 */tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("calle17",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 18 */tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("calle18",  10.00f,  1.1f, 100.00f,  500.00f,  250.00f )));
        /* 19 */tablero.añadeCasilla(new CasillaImpuesto((float) 250.00,"IMPUESTO"));
        
        this.tablero.añadeJuez();

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
        Jugador jugadorActual = this.getJugadorActual();
        return jugadorActual.salirCarcelTirando();
    }

    /* COMPLETAR MÉTODO  ?¿?¿?¿ */
    public OperacionesJuego siguientePaso(){
        
        // System.out.println("\n Estado Actual: " + this.estado + " Jugador Actual: " + this.getJugadorActual().getNombre() + " - Casilla " + this.getJugadorActual().getNumCasillaActual() + " / " + this.tablero.getCasilla(this.getJugadorActual().getNumCasillaActual()).getNombre() +"\n" );

        OperacionesJuego operacion = gestorEstados.operacionesPermitidas(this.getJugadorActual(), this.estado);

        if (operacion == OperacionesJuego.PASAR_TURNO) {
            this.pasarTurno();
            this.estado = gestorEstados.siguienteEstado(this.getJugadorActual(), this.estado, operacion);

        } else if (operacion == OperacionesJuego.AVANZAR) {
            this.avanzaJugador();
            
        }

        return operacion;
        
    }

    public void siguientePasoCompletado(OperacionesJuego operacion){
        // System.out.println("\n Entramos a SiguientePasoCompletado, Operacion: " + operacion + " Estado - " + this.estado );


        Jugador jugadorActual = this.jugadores[this.indiceJugadorActual];
        // System.out.println("\n Jugador Actual: " + jugadorActual.getNombre());

        this.estado = gestorEstados.siguienteEstado(jugadorActual, this.estado, operacion);
        // System.out.println("\n Estado Nuevo: " + this.estado + "\n" );

    }

    public boolean vender(int ip){
        Jugador jugadorActual = this.jugadores[indiceJugadorActual];
        return jugadorActual.vender(ip);
    }




    
    /* ---------------- SETTERS / GETTERS ---------------- */

    public Casilla getCasillaActual(){
        return this.tablero.getCasilla(this.jugadores[indiceJugadorActual].getNumCasillaActual());
    }

    public Jugador getJugadorActual(){
        return this.jugadores[this.indiceJugadorActual];
    }

    public Tablero getTablero(){
        return this.tablero;
    }

}
