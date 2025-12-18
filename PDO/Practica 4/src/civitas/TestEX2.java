package civitas;

public class TestEX2 {
	public static void main(String[] args) {

		Jugador jugador1 = new Jugador("David");
		Jugador jugador2 = new Jugador("Jose"); 

		/* Se le podría hacer una cartaNovato para hacer la conversión, si da tiempo se hace. */
		JugadorNovato jugadorNovato = new JugadorNovato(jugador2, 500);
	

		TituloPropiedad propiedad1 = new TituloPropiedad("Propiedad Examen", 100, 1, 100, 300, 100);

		TituloPropiedad propiedad2 = new TituloPropiedad("Propiedad Parcial", 100, 1, 100, 300, 100);


		jugador1.añadirPropiedad(propiedad1);
		jugadorNovato.añadirPropiedad(propiedad2);

		propiedad1.setPropietario(jugador1);
		propiedad2.setPropietario(jugadorNovato);

		System.out.println( jugador1.toString() ); 
		System.out.println( jugadorNovato.toString() );

		jugador1.recibe(1000);
		jugadorNovato.recibe(1000);

		jugador1.pagaImpuesto( propiedad2.getPrecioAlquiler() );
		float pagoJugador1 = propiedad2.getPrecioAlquiler();
		
		jugadorNovato.pagaImpuesto(propiedad1.getPrecioAlquiler());
		float pagoJugador2 = propiedad1.getPrecioAlquiler();


		System.out.println("Saldo final: \n Jugador1: " + jugador1.getSaldo() + "\n Jugador2: " +jugadorNovato.getSaldo() );
		
		
		String jugadorHaPagadoMas = (pagoJugador1 >= pagoJugador2) ? jugador1.getNombre() : jugadorNovato.getNombre();

		String jugadorMasSaldo = (jugador1.getSaldo() >= jugadorNovato.getSaldo()) ? jugador1.getNombre() : jugadorNovato.getNombre();

		System.out.println("\n El jugador que más ha pagado es: " + jugadorHaPagadoMas);

		System.out.println("\n El jugador que más saldo tiene es: " + jugadorMasSaldo);


	}
}
