package civitas;

import java.util.ArrayList;

@SuppressWarnings("all")

public class Jugador implements Comparable<Jugador>{

    protected static final int CasasMax = 4;
    protected static final int CasasPorHotel = 4;
    protected static final int HotelesMax = 4;

    protected static final float PasoPorSalida = 1000;
    protected static final float PrecioLibertad = 200;
    private static final float SaldoInicial = 7500;

    protected boolean encarcelado;

    private String nombre;
    private int numCasillaActual;
    

    
    private boolean puedeComprar;
    private float saldo;
    
    

    private ArrayList<TituloPropiedad> propiedades;
    private Sorpresa salvoconducto; /* Tipo = SalirCarcel */


    /* ---------------- CONSTRUCTORES ---------------- */

    Jugador(String nombre) {
        this.encarcelado = false;
        this.nombre = nombre;
        this.numCasillaActual = 0;
        this.saldo = SaldoInicial;
        this.salvoconducto = null;
        this.propiedades = null;
    }

    protected Jugador(Jugador otro) {
        this.encarcelado = otro.encarcelado;
        this.nombre = otro.nombre;
        this.numCasillaActual = otro.numCasillaActual;
        this.saldo = otro.saldo;
        this.salvoconducto = otro.salvoconducto;
        this.propiedades = otro.propiedades;
    }


    /* ---------------- METODOS ---------------- */
    
    /* Siguiente Práctica */
    /* boolean cancelarHipoteca(int ip) {

    } */

    int cantidadCasasHoteles() {

        int total = 0;

        for (TituloPropiedad propiedad : propiedades) {
            total += propiedad.getNumCasas() + propiedad.getNumHoteles();
        }

        return total;
    }

    
    public int compareTo(Jugador otro) {
        return Float.compare(this.saldo, otro.saldo);
    }

    /* Próxima Práctica */
    /* boolean comprar(TituloPropiedad titulo) {

    } */

    /* Próxima Práctica */
    /* boolean construirCasa(int ip) {

    } */

    /* Próxima Práctica */
    /* boolean construirHotel(int ip) {

    } */

    protected boolean debeSerEncarcelado() {
        if ( !this.encarcelado) {
            Diario.getInstance().ocurreEvento("El jugador " + this.nombre + "ha caído en la carcel.");
            return true;
        }else if( this.salvoconducto == null ){
            perderSalvoconducto();
            Diario.getInstance().ocurreEvento("El jugador " + this.nombre + "se ha salvado de la carcel por salvaconducto.");
            return false;
        }
        return false;
    }

    boolean enBancarrota() {
        return this.saldo < 0;
    }

    boolean encarcelar(int numCasillaCarcel) {
        if( this.debeSerEncarcelado() ){
            this.moverACasilla(numCasillaCarcel);
            this.encarcelado = true;
            Diario.getInstance().ocurreEvento("El jugador " + this.nombre + "ha sido encarcelado");
        }
        return this.encarcelado;
    }

    private boolean existeLaPropiedad(int ip) {
        return (this.propiedades.get(ip) != null);
    }

    /* Próxima Práctica */
    /* boolean hipotecar(int ip) {

    } */

    boolean modificarSaldo(float cantidad) {
        this.saldo = this.saldo + cantidad;
        Diario.getInstance().ocurreEvento("Se le han aplicado a " + this.nombre + ", " + cantidad + " a su saldo.");
        return true;
    }

    boolean moverACasilla(int numCasilla) {

        if (this.encarcelado){
            return false;
        }

        this.numCasillaActual = numCasilla;
        this.puedeComprar = false;
        Diario.getInstance().ocurreEvento( "El jugador " + this.nombre + " se mueve a la casilla " + this.numCasillaActual);

        return true;
    }

    boolean obtenerSalvoconducto(Sorpresa sorpresa) {
        if(!this.encarcelado){
            this.salvoconducto = sorpresa ; /* Hacer referencia a una sorpresa tipo SalirCarcel */
            return true;
        }
        return false;
    }

    boolean paga(float cantidad) {
        return this.modificarSaldo(-1 * cantidad);
    }

    boolean pagaAlquiler(float cantidad) {
        if (this.encarcelado){
            return false;
        }
        return paga(cantidad);
    }

    boolean pagaImpuesto(float cantidad) {
        if(this.encarcelado){
            return false;
        }else{
            return this.paga(cantidad);
        }
    }

    boolean pasaPorSalida() {
        modificarSaldo(PasoPorSalida);

        Diario.getInstance().ocurreEvento("El jugador " + this.nombre + " ha pasado por la salida y recibe " + PasoPorSalida );

        return true;
    }

    private void perderSalvoconducto() {
        this.salvoconducto.usada();
        this.salvoconducto = null;
    }

    boolean puedeComprarCasilla() {
        this.puedeComprar = !this.encarcelado;
        return this.puedeComprar;
    }

    private boolean puedeSalirCarcelPagando() {
        return this.saldo >= PrecioLibertad;
    }

    private boolean puedeEdificarCasa(TituloPropiedad propiedad) {
        return !(this.encarcelado || !puedoGastar(propiedad.getPrecioEdificar()) || propiedad.getNumCasas() >= CasasMax);
        
    }

    private boolean puedeEdificarHotel(TituloPropiedad propiedad) {
        return !(this.encarcelado || !puedoGastar(propiedad.getPrecioEdificar()) || propiedad.getNumCasas() < CasasPorHotel || propiedad.getNumHoteles() >= HotelesMax );
    }

    private boolean puedoGastar(float precio) {
        if (this.encarcelado){
            return false;
        }
        return this.saldo >= precio;
    }

    boolean recibe(float cantidad) {
        if (this.encarcelado){
            return false;
        }

        return modificarSaldo(cantidad);
    }

    boolean salirCarcelPagando() {
        if (!this.encarcelado) return false;
        if (!puedeSalirCarcelPagando()) return false;

        paga(PrecioLibertad);
        this.encarcelado = false;

        Diario.getInstance().ocurreEvento("El jugador " + this.nombre + " ha salido de la cárcel pagando " + PrecioLibertad);

        return true;
    }

    boolean salirCarcelTirando() {
        if (!this.encarcelado) return false;

        boolean sale = Dado.getInstance().salgoDeLaCarcel();

        if (sale) {
            this.encarcelado = false;

            Diario.getInstance().ocurreEvento("El jugador " + this.nombre + " ha salido de la cárcel tirando el dado y sacando un " + Dado.getInstance().getNumSalirCarcel());
        }

        return sale;
    }

    boolean tieneAlgoQueGestionar() {
        return !propiedades.isEmpty();
    }

    boolean tieneSalvoconducto() {
        return this.salvoconducto != null;
    }

    
    @Override
    public String toString() {

        String estado = this.encarcelado ? "ENCARCELADO" : "LIBRE";

        String texto = 
            "Jugador: " + this.nombre +
            "\n  Estado: " + estado +
            "\n  Casilla actual: " + this.numCasillaActual +
            "\n  Saldo: " + this.saldo +
            "\n  Puede comprar: " + this.puedeComprar +
            "\n  Salvoconducto: " + (this.salvoconducto != null ? "SI" : "NO") +
            "\n  Propiedades:";

        for (TituloPropiedad propiedad : propiedades) {
            texto += "\n    - " + propiedad.getNombre() +
                    " (Casas: " + propiedad.getNumCasas() +
                    ", Hoteles: " + propiedad.getNumHoteles() + ")";
        }

        return texto;
    }


    boolean vender(int ip) {
        if (this.encarcelado){
            return false;
        }else if (!existeLaPropiedad(ip)){
            return false;
        }else{
            TituloPropiedad propiedad = propiedades.get(ip);

            boolean vendido = propiedad.vender(this);

            if (vendido) {
                propiedades.remove(ip);
                Diario.getInstance().ocurreEvento("El jugador " + nombre + " ha vendido la propiedad " + propiedad.getNombre());
            }

            return vendido;
        }
    }


    /* ---------------- SETTERS / GETTERS ---------------- */

    private int getCasasMax() {
        return CasasMax;
    }

    int getCasasPorHotel() {
        return CasasPorHotel;
    }

    private int getHotelesMax() {
        return HotelesMax;
    }

    protected String getNombre() {
        return this.nombre;
    }

    int getNumCasillaActual() {
        return this.numCasillaActual;
    }

    private float getPrecioLibertad() {
        return PrecioLibertad;
    }

    private float getPremioPasoSalida() {
        return PasoPorSalida;
    }

    protected ArrayList<TituloPropiedad> getPropiedades() {
        return this.propiedades;
    }

    boolean getPuedeComprar() {
        return this.puedeComprar;
    }

    protected float getSaldo() {
        return this.saldo;
    }

    public boolean isEncarcelado() {
        return this.encarcelado;
    }

}
