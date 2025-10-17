

package civitas;
import java.util.ArrayList;

@SuppressWarnings("all")
public  class Tablero{

    private int numCasillaCarcel;
    private ArrayList<Casilla> casillas; 
    private int porSalida;
    private boolean tieneJuez;
    


     
    /* ---------------------- Constructor ---------------------- */
    Tablero (int numCasillaCarcel ){
        
        this.numCasillaCarcel = ( numCasillaCarcel >= 1 ) ? numCasillaCarcel : 1 ;
        this.casillas = new ArrayList<>();
        this.porSalida = 0;
        this.tieneJuez = false;

    }

    /*  ---------------------- Métodos ---------------------- */

    private Boolean tableroCorrecto(){

        return ( (casillas.size() > numCasillaCarcel) && tieneJuez ) ; /* Aqui se hace la comprobacion entera y devuelve true/false */
    }

    private Boolean tableroCorrecto(int numCasilla){

        return ( (casillas.size() > numCasillaCarcel) && tieneJuez &&  numCasilla < casillas.size() ) ; /* Compureba si la casilla de la carcel y la casilla pasada existen en el tablero */
    }


    private void añadeCasilla (Casilla casilla){
        
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
            casillas.add(new Casilla("Juez"));
            this.tieneJuez = true;
        }
    }

    private int nuevaPosicion(int actual, int tirada){
        
        if( this.tableroCorrecto() ){
            return -1;
        }else{
            
            int nuevaPosicion = actual + tirada;

            if(nuevaPosicion > casillas.size() ){
                
                nuevaPosicion = nuevaPosicion - casillas.size();
                
                this.porSalida++;
            }

            

            return nuevaPosicion;
        }
    }

    private int calcularTirada( int origen, int destino){
        int numeroDado;

        if(destino < origen ){

            numeroDado = this.casillas.size() - origen + destino;
            
        }else{
            numeroDado = destino - origen;
        }

        return numeroDado;
    }



    /* ------------------------ Getters ------------------------ */
    private int getCarcel(){
        
        return this.numCasillaCarcel;
    }

    private int getPorSalida(){
        if( this.porSalida > 0){
            
            this.porSalida--;
            return this.porSalida+1;

        }else{
            return this.porSalida;
        }
    }

    private Casilla getCasilla(int numCasilla){
        
        return ( tableroCorrecto(numCasilla) ) ?  casillas.get(numCasilla) : null; /* La funcion get devuelve lo que haya en el indice de ese array ->  casillas[numCasilla] = .... */
    }



}