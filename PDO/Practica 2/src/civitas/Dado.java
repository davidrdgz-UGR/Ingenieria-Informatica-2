package civitas;
// import java.util.ArrayList;
import java.util.Random;


@SuppressWarnings("all")
class Dado{
    
    private int ultimoResultado;
    private boolean debug;
    private static final int salidaCarcel = 5;

    private Random random;
    private static Dado instance = new Dado(); /* Declara Su propia instancia (Singletone) */
    



    /* ---------------------- Constructor ---------------------- */
    private Dado (){

        random = new Random();
        ultimoResultado = 0;
        this.debug = false;
    }



    /*  ---------------------- Métodos ---------------------- */

    int tirar(){
        
        this.ultimoResultado = ( debug ) ? 1 : random.nextInt(6) + 1;

        return this.ultimoResultado;

    }

    boolean salgoDeLaCarcel() {
        int resultado = tirar();

        return ( resultado == salidaCarcel );
    }

    int quienEmpieza(int n) {
        return random.nextInt(n); /* Se usa n ya que si hay 5 jugadores ( 5-1 = 4), va del 0-4.99999 */
    }

    
    
    public void setDebug(boolean d) {
        debug = d; /* d será true/false */

        String mensaje;

        mensaje = (debug) ? "Modo debug del Dado activado." : "Modo debug del Dado desactivado." ; 

        Diario.getInstance().ocurreEvento(mensaje);
    }

    /* ------------------------ Getters ------------------------ */

    public static Dado getInstance() {
        return instance;
    }

    public int getNumSalirCarcel(){
        return salidaCarcel;
    }

    int getUltimoResultado() {
        return this.ultimoResultado;
    }
}