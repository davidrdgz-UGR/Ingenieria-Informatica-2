package civitas;
import java.util.ArrayList;
import java.util.Collections;


@SuppressWarnings("all")
class MazoSorpresa{

    
    private boolean barajada;                      
    private int usadas;                            
    private boolean debug;                         
    
    private Sorpresa ultimaSorpresa;   

    private ArrayList<Sorpresa> sorpresas;         
    private ArrayList<Sorpresa> cartasEspeciales;  
    
                
    



    /* ---------------------- Constructor ---------------------- */ 
    MazoSorpresa(boolean debug) {
        
        this.debug = debug;
        
        init();
        
        if (debug) {
            Diario.getInstance().ocurreEvento("Modo DEBUG de Mazo Sopresa.");
        }
    }

    MazoSorpresa() {
        this(false); /* DUDA -> porque solo se le da false. ?¿?¿?¿?¿ */
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


    void alMazo(Sorpresa sorpresa) {
        if (!barajada) {
            sorpresas.add(sorpresa);
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

    /* No salen en el diagrama UML / Puede que para TestP1 */
    boolean isBarajada() {
        return barajada;
    }

    int tamañoMazo() {
        return sorpresas.size();
    }


    /* ----------------- GETTERS / SETTERS ----------------- */

    int getUsadas() {
        return usadas;
    }

    Sorpresa getUltimaSorpresa() {
        return ultimaSorpresa;
    }

}