package civitas;
import java.util.ArrayList;


public  class Tablero{

    private int numCasillaCarcel;
    private ArrayList<Casilla> casillas; 
    private int porSalida;
    private boolean tieneJuez;
    

    Tablero (int numCasillaCarcel ){
        
        this.numCasillaCarcel = ( numCasillaCarcel >= 1 ) ? numCasillaCarcel : 1 ;
        this.casillas = new ArrayList<>();
        this.porSalida = 0;
        this.tieneJuez = false;

    }
}