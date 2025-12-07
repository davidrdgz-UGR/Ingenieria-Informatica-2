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
        
        if(!this.tienePropietario() && jugador.getSaldo() >= this.precioEdificar){
            jugador.paga(this.precioCompra);
            this.propietario = jugador;
            
            return true;
        }

        return false;
        
    }

    boolean construirCasa(Jugador jugador) {
        
        boolean puedeConstruir = false;

        if(esEsteElPropietario(jugador) && jugador.getSaldo() >= this.precioEdificar ){
            jugador.paga(this.precioEdificar);
            this.numCasas++;
            
            puedeConstruir=true;
            
            return puedeConstruir;
        }
        return puedeConstruir;
        
    }

    boolean construirHotel(Jugador jugador) {
        
        boolean puedeConstruir = false;

        if(esEsteElPropietario(jugador) && jugador.getSaldo() >= this.precioEdificar){
            jugador.paga(this.precioEdificar);
            this.numHoteles++;
            
            puedeConstruir=true;
            
            return puedeConstruir;
        }
        return puedeConstruir;
        
    }

    boolean derruirCasas(int n, Jugador jugador) {

        if (esEsteElPropietario(jugador) && this.numCasas >= n) {
            this.numCasas = this.numCasas - n;
            return true;
        }

        return false;
    }

    private boolean esEsteElPropietario(Jugador jugador) {
        return (this.propietario == jugador ) ? true : false;   
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
        return (this.propietario != null ) ? true : false;
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
        
        if(this.tienePropietario()){
            float devolver = this.precioCompra + ( (this.numCasas * factorRevalorizacion * precioEdificar) + (this.numHoteles * factorRevalorizacion * precioEdificar) );

            this.numCasas = 0;
            this.numHoteles = 0;

            jugador.recibe(devolver);
            this.propietario = null;
            
            return true;
        }

        return false;
    }

    /* ---------------- SETTERS / GETTERS ---------------- */

    public boolean getHipotecado() {
        return this.hipotecado;
    }

    float getImporteCancelarHipoteca() {
        
        float total = this.hipotecaBase * ( 1f + ( this.numCasas * 0.5f ) + ( this.numHoteles * 2.5f ) ) ;
        return  total * factorInteresesHipoteca;
        
    }

    private float getImporteHipoteca() {
        return this.hipotecaBase;
    }

    /* Era de paquete pero no se puede accedeer desde VistaTextual.gestionar() */
    public String getNombre() {
        return this.nombre;
    }

    int getNumCasas() {
        return this.numCasas;  
    }

    int getNumHoteles() {
        return  this.numHoteles;
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
        return this.precioCompra;
    }

    float getPrecioEdificar() {
        return this.precioEdificar;
    }

    private float getPrecioVenta() {
    
        float total = this.precioCompra + this.cantidadCasasHoteles() * precioEdificar;
        
        return total;
    }

    Jugador getPropietario() {
        return this.propietario;
    }
}

