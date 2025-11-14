package civitas;

public class TituloPropiedad {

    private float alquilerBase;
    private static final float factorInteresesHipoteca = (float) 1.1; /*  ?¿¿?¿?¿ */
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
    
    TituloPropiedad(String nombre, float baseAlquiler, float factorRevalorizacion,float baseHipoteca, float precioCompra, float precioEdificar) {
        this.nombre=nombre;
        this.alquilerBase = baseAlquiler;
        this.factorRevalorizacion = factorRevalorizacion;
        this.hipotecaBase = baseHipoteca;
        this.precioCompra = precioCompra;
        this.precioEdificar = precioEdificar;

        this.propietario = null;
        this.numCasas = 0;
        this.numHoteles = 0;
        this.hipotecado = false;

    }

    
    
    /* ---------------- METODOS ---------------- */


    void actualizaPropietarioPorConversion(Jugador jugador) {
        this.propietario = jugador;
    }

    boolean cancelarHipoteca(Jugador jugador) {
        
        if(this.hipotecado && esEsteElPropietario(jugador) ){
            
            this.hipotecado = false;
            jugador.paga( getImporteCancelarHipoteca() );

            return true;
        }else{

            return false;
        }
    }

    int cantidadCasasHoteles() {
        return this.numCasas + this.numHoteles;
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
        
        if( !this.hipotecado && esEsteElPropietario(jugador) ){
            
            this.hipotecado = true;
            jugador.recibe(this.hipotecaBase);

            return true;
        }else{

            return false;
        }
        
    }

    private boolean propietarioEncarcelado() {
        
        return ( this.propietario != null || this.propietario.encarcelado ) ? true : false;

    }

    boolean tienePropietario() {
        
    }

    public String toString() {
        String representacion;
        
        representacion =
                "Titulo Propiedad:\n" +
                "\t- Nombre = " + nombre + "\n" +
                "\t- Alquiler base = " + alquilerBase + "\n" +
                "\t- Factor de revalorización = " + factorRevalorizacion + "\n" +
                "\t- Hipoteca base = " + hipotecaBase + "\n" +
                "\t- Precio de compra = " + precioCompra + "\n" +
                "\t- Precio de edificar = " + precioEdificar + "\n" +
                "\t- Número de casas = " + numCasas + "\n" +
                "\t- Número de hoteles = " + numHoteles + "\n";

        if (propietario == null)
            representacion += "\t- Propietario = sin propietario\n";
        else
            representacion += "\t- Propietario = " + propietario.getNombre();

        return representacion;
    }

    void tramitarAlquiler(Jugador jugador) {
        
        if(!this.hipotecado && !esEsteElPropietario(jugador)){
            jugador.pagaAlquiler(this.alquilerBase);
            this.propietario.recibe(this.alquilerBase);
        }

    }

    boolean vender(Jugador jugador) {
        
    }

    /* ---------------- SETTERS / GETTERS ---------------- */

    public boolean getHipotecado() {

    }

    float getImporteCancelarHipoteca() {
        
        float total = this.hipotecaBase * ( 1f + ( this.numCasas * 0.5f ) + ( this.numHoteles * 2.5f ) ) ;
        return  total * factorInteresesHipoteca;
        
    }

    private float getImporteHipoteca() {
        

    }

    String getNombre() {
        return this.nombre;
    }

    int getNumCasas() {
    
    }

    int getNumHoteles() {
    
    }

    private float getPrecioAlquiler() {
        
        if( this.hipotecado || this.propietarioEncarcelado() ){
            return (float) 0;
        }else{
            
            float precioReal = this.alquilerBase * ( 1f + ( this.numCasas * 0.5f ) + ( this.numHoteles * 2.5f ) );
            
            return precioReal;
        }
        
    }

    float getPrecioCompra() {
    
    }

    float getPrecioEdificar() {
    
    }

    private float getPrecioVenta() {
    
        float total = this.precioCompra + this.cantidadCasasHoteles() * precioEdificar;
        
        return total;
    }

    Jugador getPropietario() {
    
    }
}

