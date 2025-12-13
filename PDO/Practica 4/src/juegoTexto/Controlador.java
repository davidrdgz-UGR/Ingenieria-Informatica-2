package juegoTexto;

/* CLASES */
import civitas.CivitasJuego;
import civitas.GestionInmobilarias;
import civitas.OperacionesJuego;
import civitas.Respuestas;
import civitas.SalidasCarcel;

public class Controlador {
    private CivitasJuego juego;
    private VistaTextual vista;


    
    /* ---------------------- Constructor ---------------------- */ 

    Controlador(CivitasJuego juego, VistaTextual vista){
        this.juego = juego;
        this.vista = vista;
    }

    
    /*  ---------------------- Métodos ---------------------- */

    void juega(){

        this.vista.setCivitasJuego(this.juego);

        while(!this.juego.finalDelJuego()){

            this.vista.actualizarVista();

            this.vista.pausa();

            

            OperacionesJuego OperacionSiguiente = this.juego.siguientePaso();

            /* Es SOLO un texto de comprobacion */
            this.vista.mostrarSiguienteOperacion(OperacionSiguiente);

            /* Texto del Diario.EventosPendientes() SI NO SE PASA DE TURNO */
            if (OperacionSiguiente != OperacionesJuego.PASAR_TURNO) {
                vista.mostrarEventos();
            }


            if( !this.juego.finalDelJuego() ){
                
                switch (OperacionSiguiente) {
                    
                    case COMPRAR -> {
                        if(Respuestas.SI == this.vista.comprar()){
                            this.juego.comprar();
                        }
                    }

                    case GESTIONAR -> {
                        while (true) {
                            vista.gestionar();

                            GestionInmobilarias gestion = GestionInmobilarias.values()[vista.getGestion()];
                            int ip = vista.getPropiedad();

                            if (gestion == GestionInmobilarias.TERMINAR) {
                                ip = -1;
                                break; // salir de la fase gestionar
                            }

                            // Si no hay propiedad válida, re-muestra el menú
                            if (ip < 0) {
                                continue;
                            }

                            switch (gestion) {
                                case VENDER -> juego.vender(ip);
                                case HIPOTECAR -> juego.hipotecar(ip);
                                case CANCELAR_HIPOTECA -> juego.cancelarHipoteca(ip);
                                case CONSTRUIR_CASA -> juego.comprarCasa(ip);
                                case CONSTRUIR_HOTEL -> juego.comprarHotel(ip);
                            }
                        }
                    }

                    case SALIR_CARCEL -> {

                        if (vista.salirCarcel() == SalidasCarcel.PAGANDO) {
                            juego.salirCarcelPagando();
                        } else {
                            juego.salirCarcelTirando();
                        }
                        
                    }

                    default -> {

                    }
                }

                this.juego.siguientePasoCompletado(OperacionSiguiente);
            
                // System.out.println("\n--- RANKING FINAL ---");
                // System.out.println(juego.ranking());

            }
        }

    }

}
