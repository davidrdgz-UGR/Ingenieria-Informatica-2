package juegoTexto;

/* CLASES */
import civitas.CivitasJuego;
import civitas.Diario;
import civitas.GestionInmobilarias;
import civitas.OperacionesJuego;
import civitas.Respuestas;
import civitas.SalidasCarcel;
import civitas.TituloPropiedad;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;


public class VistaTextual {

    CivitasJuego juegoModel; 
    int iGestion=-1;
    int iPropiedad=-1;

    private static String separador = "=====================";

    private final Scanner in;

    /* ---------------------- Constructor ---------------------- */ 

    VistaTextual () {
       in = new Scanner (System.in);
    }


    /*  ---------------------- Métodos ---------------------- */

    void mostrarEstado(String estado) {
        System.out.println (estado);
    }
                
    void pausa() {
        System.out.print ("Pulsa una tecla");
        in.nextLine();
    }

    int leeEntero (int max, String msg1, String msg2) {
        Boolean ok;
        String cadena;
        int numero = -1;
        do {
          System.out.print (msg1);
          cadena = in.nextLine();
          try {  
            numero = Integer.parseInt(cadena);
            ok = true;
          } catch (NumberFormatException e) { // No se ha introducido un entero
            System.out.println (msg2);
            ok = false;  
          }
          if (ok && (numero < 0 || numero >= max)) {
            System.out.println (msg2);
            ok = false;
          }
        } while (!ok);

        return numero;
    }

    int menu (String titulo, ArrayList<String> lista) {
        String tab = "  ";
        int opcion;
        System.out.println (titulo);
        for (int i = 0; i < lista.size(); i++) {
          System.out.println (tab+i+"-"+lista.get(i));
        }

        opcion = leeEntero(lista.size(),
                              "\n"+tab+"Elige una opción: ",
                              tab+"Valor erróneo");
        return opcion;
    }

    SalidasCarcel salirCarcel() {
        int opcion = menu ("Elige la forma para intentar salir de la carcel",
          new ArrayList<> (Arrays.asList("Pagando","Tirando el dado")));          
        
        return (SalidasCarcel.values()[opcion]);
    }

    Respuestas comprar() {
        int opcion = menu ("Quieres comprar " + this.juegoModel.getCasillaActual().getNombre(),
        new ArrayList<> (Arrays.asList("SI","NO")));
      
        return (Respuestas.values()[opcion]);
    }

    void gestionar () {
        ArrayList<String> opcionesGestiones = new ArrayList<>(
            Arrays.asList(
                "VENDER",
                "HIPOTECAR",
                "CANCELAR_HIPOTECA",
                "CONSTRUIR_CASA",
                "CONSTRUIR_HOTEL",
                "TERMINAR"
            )
        );

        iGestion = menu("¿Qué gestión quiere realizar?", opcionesGestiones);

        if (GestionInmobilarias.values()[iGestion] == GestionInmobilarias.TERMINAR) {
            iPropiedad = -1;
            return;
        }

        ArrayList<String> nombresPropiedades = new ArrayList<>();

        for (TituloPropiedad propiedad : this.juegoModel.getJugadorActual().getPropiedades()) {
            nombresPropiedades.add(propiedad.getNombre());
        }

        if (nombresPropiedades.isEmpty()) {
            System.out.println("El jugador actual no tiene propiedades que gestionar.");
            iPropiedad = -1;
        } else {
            iPropiedad = menu(
                "¿Sobre qué propiedad quiere realizar la gestión?",
                nombresPropiedades
            );
        }

    }

    void mostrarSiguienteOperacion(OperacionesJuego operacion) {
        
      /* Esta clase no tiene toString sobreescrito ------------ REVISAR ------------ */
        System.out.println("Siguiente Operacion: " + operacion.toString());

    }

    void mostrarEventos() {
      while (Diario.getInstance().eventosPendientes()) {
          System.out.println("EVENTO: " + Diario.getInstance().leerEvento());
      }
    }


    void actualizarVista(){
      System.out.println (this.juegoModel.infoJugadorTexto());
    } 

    public void setCivitasJuego(CivitasJuego civitas){ 
        this.juegoModel=civitas;
        // this.actualizarVista();
    }

    
    /* ----------------- GETTERS / SETTERS ----------------- */

    public int getGestion(){
      return this.iGestion;
    }

    public int getPropiedad(){
      return this.iPropiedad;
    }
    
}
