package juegoTexto;

import civitas.CivitasJuego;
import civitas.Dado;
import java.util.ArrayList;


public class Main{

	public static void main(String[] args) {
		
		ArrayList<String> nombresPorDefecto = new ArrayList<>();
    	nombresPorDefecto.add("David");
    	nombresPorDefecto.add("Jose");
    	nombresPorDefecto.add("Patri");
	
		Dado.getInstance().setDebug(true);

		CivitasJuego juego = new CivitasJuego(nombresPorDefecto);

		VistaTextual vista = new VistaTextual();
		Controlador controlador = new Controlador(juego, vista);

		controlador.juega();
	}
	

}
