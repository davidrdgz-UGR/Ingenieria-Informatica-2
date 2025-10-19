package civitas;
import java.util.ArrayList;
import java.util.Collections;


@SuppressWarnings("all")
class MazoSorpresa{

    private ArrayList<Sorpresa> sorpresas;         
    private boolean barajada;                      
    private int usadas;                            
    private boolean debug;                         
    private ArrayList<Sorpresa> cartasEspeciales;  
    private Sorpresa ultimaSorpresa;               
    



    /* ---------------------- Constructor ---------------------- */ 
    MazoSorpresa(boolean debug) {
        
        this.debug = debug;
        
        init();
        
        if (debug) {
            Diario.getInstance().ocurreEvento("Modo DEBUG de Mazo Sopresa.");
        }
    }

    MazoSorpresa() {
        this(false);

        init();
    }

    /*  ---------------------- Métodos ---------------------- */

    /* Digamos que es el constructor pero llamado desde un método privado */
    private void init() {
        sorpresas = new ArrayList<>();
        cartasEspeciales = new ArrayList<>();
        barajada = false;
        usadas = 0;
        ultimaSorpresa = null;
    }


    void alMazo(Sorpresa s) {
        if (!barajada) {
            sorpresas.add(s);
        }
    }

    
    Sorpresa siguiente() {
        if (sorpresas.isEmpty()) {
            return null;
        }

        // Comprobación para hacer reset
        if (!barajada || usadas == sorpresas.size()) {
            
            if (!debug) {
                Collections.shuffle(sorpresas);
            }

            usadas = 0;
            barajada = true;
        }

        usadas++;

        Sorpresa s = sorpresas.remove(0); 
        sorpresas.add(s);                 
        ultimaSorpresa = s;
        return s;
    }


    /* Sin revisar */
    void inhabilitarCartaEspecial(Sorpresa sorpresa) {
        boolean estabaEnMazo = sorpresas.remove(sorpresa);
        if (estabaEnMazo) {
            cartasEspeciales.add(sorpresa);
            Diario.getInstance().ocurreEvento(
                "Carta especial inhabilitada: movida de mazo a cartasEspeciales."
            );
        }
    }

    void habilitarCartaEspecial(Sorpresa sorpresa) {
        boolean estabaEspecial = cartasEspeciales.remove(sorpresa);
        if (estabaEspecial) {
            sorpresas.add(sorpresa);
            Diario.getInstance().ocurreEvento(
                "Carta especial habilitada: movida de cartasEspeciales al mazo."
            );
        }
    }

    Sorpresa getUltimaSorpresa() {
        return ultimaSorpresa;
    }

    int getUsadas() {
        return usadas;
    }

    boolean isBarajada() {
        return barajada;
    }

    int tamañoMazo() {
        return sorpresas.size();
    }

}