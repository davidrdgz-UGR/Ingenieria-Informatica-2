package civitas;
import java.util.ArrayList;
import java.util.Collections;

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
        this(false); 
        // init();

        // System.out.println("Mazo Inicializado");
        
    }

    /*  ---------------------- Métodos ---------------------- */

    /* Digamos que es el constructor pero llamado desde un método privado */
    private void init() {
        sorpresas = new ArrayList<>();
        cartasEspeciales = new ArrayList<>();
        barajada = false;
        usadas = 0;
        ultimaSorpresa = null;

/*             System.out.println("MazoSorpresa creado: " + System.identityHashCode(this));
            System.out.println("[DEBUG] MazoSorpresa inicializado correctamente");
            System.out.println("  sorpresas: " + sorpresas.size());
            System.out.println("  cartasEspeciales: " + cartasEspeciales.size());
            System.out.println("  barajada: " + barajada);
            System.out.println("  usadas: " + usadas);
            System.out.println("  ultimaSorpresa: " + ultimaSorpresa); */
    }

    void revisarMazo(){
            
            System.out.println("MazoSorpresa creado: " + System.identityHashCode(this));
            System.out.println("[DEBUG] MazoSorpresa inicializado correctamente");
            System.out.println("  sorpresas: " + sorpresas.size());
            System.out.println("  cartasEspeciales: " + cartasEspeciales.size());
            System.out.println("  barajada: " + barajada);
            System.out.println("  usadas: " + usadas);
            System.out.println("  ultimaSorpresa: " + ultimaSorpresa);


            System.out.println("\n " + this.sorpresas  );
            for (int i=0; i < this.sorpresas.size(); i++) {
                System.out.println("\n " + this.sorpresas.get(i) );
            }
            System.out.println("\n ");

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