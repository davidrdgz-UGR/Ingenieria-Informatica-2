package civitas;

public class testExamen {
    
    public static void main() {
        Jugador jugador1 = new Jugador("David");

        jugador1.recibe(200);
        jugador1.recibe(100);
        jugador1.moverACasilla(5);

        System.out.println(jugador1.descripcionEstado());
        System.out.println(jugador1.mostrarHistorial());
        
    }
}
