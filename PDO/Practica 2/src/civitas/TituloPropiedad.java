package civitas;

public class TituloPropiedad {

    private float alquilerBase;
    private static final float factorInteresesHipoteca; /* = 1.1 ?¿¿?¿?¿ */
    private float factorRevalorizacion;
    private float hipotecaBase;
    private boolean hipotecado;
    private String nombre;
    private int numCasas;
    private int numHoteles;
    private float precioCompra;
    private float precioEdificar;
    
    private Jugador propietario;

  
    /* ---------------- CONSTRUCTOR ---------------- */
    
    TituloPropiedad(String nom, float ab, float fr,float hb, float pc, float pe) {

    }

    
    
    /* ---------------- METODOS ---------------- */


    void actualizaPropietarioPorConversion(Jugador jugador) {
        
    }

    boolean cancelarHipoteca(Jugador jugador) {
         
    }

    int cantidadCasasHoteles() {
        
    }

    boolean comprar(Jugador jugador) {
        
        
    }

    boolean construirCasa(Jugador jugador) {
        
        
    }

    boolean construirHotel(Jugador jugador) {
        
        
    }

    boolean derruirCasas(int n, Jugador jugador) {
        
        
    }

    private boolean esEsteElPropietario(Jugador jugador) {
        
        
    }

    boolean hipotecar(Jugador jugador) {
        
        
    }

    private boolean propietarioEncarcelado() {
        
        
    }

    boolean tienePropietario() {
        
    }

    public String toString() {

    }

    void tramitarAlquiler(Jugador jugador) {
        
    }

    boolean vender(Jugador jugador) {
        
    }

    /* ---------------- SETTERS / GETTERS ---------------- */

    public boolean getHipotecado() {

    }

    float getImporteCancelarHipoteca() {
        

    }

    private float getImporteHipoteca() {
        

    }

    String getNombre() {
    
    }

    int getNumCasas() {
    
    }

    int getNumHoteles() {
    
    }

    private float getPrecioAlquiler() {
        
    
    }

    float getPrecioCompra() {
    
    }

    float getPrecioEdificar() {
    
    }

    private float getPrecioVenta() {
        
    
    }

    Jugador getPropietario() {
    
    }
}

