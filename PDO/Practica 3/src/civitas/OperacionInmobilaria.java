package civitas;

public class OperacionInmobilaria {
    private int numPropiedad;
    private GestionInmobilarias gestion;



    /* ---------------------- Constructor ---------------------- */ 

    /* Era de paquete / Necesita ser pública para usarse en Controlador */
    public OperacionInmobilaria(GestionInmobilarias gestiones, int ipPropiedad){

    }



    /*  ---------------------- Métodos ---------------------- */




    /* ----------------- GETTERS / SETTERS ----------------- */

    public GestionInmobilarias getGestion(){
        return this.gestion;
    }

    public int getNumPropiedad(){
        return this.numPropiedad;
    }
}
