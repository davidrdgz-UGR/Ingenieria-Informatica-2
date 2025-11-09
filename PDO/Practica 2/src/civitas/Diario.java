package civitas;



import java.util.ArrayList;

public class Diario {
  static final private Diario instance = new Diario();
  
  private ArrayList<String> eventos;

  
  /* --------------- CONSTRUCTOR - SINGLETON --------------- */
  private Diario () {
    eventos = new ArrayList<>();
  }



  /* --------------- METODOS --------------- */
  
  void ocurreEvento (String evento) {
    eventos.add (evento);
  }
  
  public boolean eventosPendientes () {
    return !eventos.isEmpty();
  }
  
  public String leerEvento () {
    String salida = "";
    if (!eventos.isEmpty()) {
      salida = eventos.remove(0);
    }
    return salida;
  }


  /* --------------- GETTERS / SETTERS --------------- */

  static public Diario getInstance() {
    return instance;
  }

}
