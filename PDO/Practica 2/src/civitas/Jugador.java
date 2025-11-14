package civitas;

import java.util.ArrayList;

@SuppressWarnings("all")

public class Jugador{

    protected static final int CasasMax = 4;
    protected static final int CasasPorHotel = 4;
    protected static final int HotelesMax = 4;

    protected boolean encarcelado;

    private String nombre;
    private int numCasillaActual;
    
    protected static final float PasoPorSalida = 1000;
    protected static final float PrecioLibertad = 200;
    private static final float SaldoInicial = 7500;
    
    private boolean puedeComprar;
    private float saldo;
    
    

    private ArrayList<TituloPropiedad> propiedades;
    private Sorpresa salvoconducto; /* Tipo = SalirCarcel */


    /* ---------------- CONSTRUCTORES ---------------- */

    Jugador(String nombre) {

    }

    protected Jugador(Jugador otro) {

    }


    /* ---------------- METODOS ---------------- */

    boolean cancelarHipoteca(int ip) {

    }

    int cantidadCasasHoteles() {

    }

    
    public int compareTo(Jugador otro) {

    }

    boolean comprar(TituloPropiedad titulo) {

    }

    boolean construirCasa(int ip) {

    }

    boolean construirHotel(int ip) {

    }

    protected boolean debeSerEncarcelado() {

    }

    boolean enBancarrota() {

    }

    boolean encarcelar(int numCasillaCarcel) {

    }

    private boolean existeLaPropiedad(int ip) {

    }

    boolean hipotecar(int ip) {

    }

    boolean modificarSaldo(float cantidad) {

    }

    boolean moverACasilla(int numCasilla) {

    }

    boolean obtenerSalvoconducto(Sorpresa sorpresa) {

    }

    boolean paga(float cantidad) {

    }

    boolean pagaAlquiler(float cantidad) {

    }

    boolean pagaImpuesto(float cantidad) {

    }

    boolean pasaPorSalida() {

    }

    private void perderSalvoconducto() {

    }

    boolean puedeComprarCasilla() {

    }

    private boolean puedeSalirCarcelPagando() {

    }

    private boolean puedeEdificarCasa(TituloPropiedad propiedad) {

    }

    private boolean puedeEdificarHotel(TituloPropiedad propiedad) {

    }

    private boolean puedoGastar(float precio) {

    }

    boolean recibe(float cantidad) {

    }

    boolean salirCarcelPagando() {

    }

    boolean salirCarcelTirando() {

    }

    boolean tieneAlgoQueGestionar() {

    }

    boolean tieneSalvoconducto() {

    }

    
    public String toString() {

    }

    boolean vender(int ip) {

    }


    /* ---------------- SETTERS / GETTERS ---------------- */

    private int getCasasMax() {

    }

    int getCasasPorHotel() {

    }

    private int getHotelesMax() {

    }

    protected String getNombre() {

    }

    int getNumCasillaActual() {

    }

    private float getPrecioLibertad() {

    }

    private float getPremioPasoSalida() {

    }

    protected ArrayList<TituloPropiedad> getPropiedades() {

    }

    boolean getPuedeComprar() {

    }

    protected float getSaldo() {

    }

    public boolean isEncarcelado() {

    }
}
