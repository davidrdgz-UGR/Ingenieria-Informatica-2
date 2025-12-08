/* HECHO POR DEFECTO ?¿ */

package civitas;
import java.util.ArrayList;

@SuppressWarnings("all")
class Tablero{

    private int numCasillaCarcel;
    private int porSalida;
    private boolean tieneJuez;
     
    private ArrayList<Casilla> casillas; 

    /* ---------------------- Constructor ---------------------- */
    public Tablero (int numCasillaCarcel ){
        
        this.numCasillaCarcel = ( numCasillaCarcel >= 1 ) ? numCasillaCarcel : 5 ;
        this.casillas = new ArrayList<>();
        this.casillas.add(new Casilla("Salida"));
        this.porSalida = 0;
        this.tieneJuez = false;

    }

    /*  ---------------------- Métodos ---------------------- */

    private Boolean tableroCorrecto(){
        return ( (casillas.size() > numCasillaCarcel) && tieneJuez ) ; 
    }

    Boolean tableroCorrecto(int numCasilla){
        return tableroCorrecto() && numCasilla >= 0 && numCasilla < casillas.size();
    }

    void añadeCasilla (Casilla casilla){
        
        if( casillas.size() == this.numCasillaCarcel ){
            casillas.add( new Casilla("Cárcel") );
        }

        casillas.add( casilla );
        
        if (casillas.size() == numCasillaCarcel) {
            casillas.add(new Casilla("Cárcel")); 
        }

    }

    void añadeJuez() {
        
        if (!this.tieneJuez) {
            // casillas.add(new Casilla("Juez")); /* Lo añadimos manualmente en la propia creacion del tablero */
            this.tieneJuez = true;
        }
    }

    int nuevaPosicion(int actual, int tirada){
        
        if( !this.tableroCorrecto() ){
            return -1;
        }else{
            
            int tamaño = casillas.size();
            int suma = actual + tirada;
            int nuevaPosicion = suma % tamaño;

            if(suma != nuevaPosicion){
                this.porSalida++;
            }
            return nuevaPosicion;
        }
    }

    int calcularTirada( int origen, int destino){
        int numeroDado;

        if(destino < origen ){
            numeroDado = this.casillas.size() - origen + destino;
        }else{
            numeroDado = destino - origen;
        }

        return numeroDado;
    }

    /* ------------------------ SETTERS / Getters ------------------------ */
    int getCarcel(){
        return this.numCasillaCarcel;
    }

    int getPorSalida(){
        if( this.porSalida > 0){
            this.porSalida--;
            return this.porSalida+1;
        }else{
            return this.porSalida;
        }
    }

    Casilla getCasilla(int numCasilla){
        return ( tableroCorrecto(numCasilla) ) ?  casillas.get(numCasilla) : null; 
    }

    /* Tambien se puede usar como retorno List<Casilla> */
    public ArrayList<Casilla> getCasillas(){
       return this.casillas; 
    }

}
