package civitas;

import java.util.ArrayList;

public class CivitasJuego {
    
    private int indiceJugadorActual;

    private Jugador jugadores[]; /* Tiene que ser un array con todos los jugadores */
    private EstadosJuego estado;
    private GestorEstados gestorEstados;
    private Tablero tablero;
    OperacionesJuego tipoOperacion;
    private static final Dado dado = Dado.getInstance();
    private MazoSorpresa mazo;


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

        this.inicializarTablero(this.tablero); /* Ahora mismo tablero es null */

        this.inicializarMazoSorpresa(this.mazo);
    }
    
    
    
    
    
    /* ---------------- METODOS ---------------- */
    /* SIGUIENTE PRACTICA */
    private void avanzaJugador(){

    }

    public boolean cancelarHipoteca(int ip){

    }

    /* SIGUIENTE PRACTICA */
    public boolean comprar(){

    }

    public boolean comprarCasa(int ip){

    }   

    public boolean comprarHotel(int ip){

    }

    private void contabilizarPasosPorSalida(Jugador jugadorActual){

    }

    public boolean finalDelJuego(){

    }

    public String infoJugadorTexto(){

    }

    private void inicializarMazoSorpresa(MazoSorpresa mazo){
        
    }    
    
    private void inicializarTablero(Tablero tablero){
        
    }         

    private void pasarTurno(){

    }

    private Jugador[] ranking(){

    }

    public boolean salirCarcelPagando(){

    }

    public boolean salirCarcelTirando(){

    }

    /* SIGUIENTE PRACTICA */
    public OperacionesJuego siguientePaso(){

    }

    public void siguientePasoCompletado(OperacionesJuego operacion){
        
    }

    public boolean vender(int ip){
        
    }




    
    /* ---------------- SETTERS / GETTERS ---------------- */

    public Casilla getCasillaActual(){
        
    }

    public Jugador getJugadorActual(){

    }

}
