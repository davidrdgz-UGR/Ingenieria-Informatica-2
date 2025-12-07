package juegoTexto;

/* CLASES */
import civitas.CivitasJuego;
import civitas.Diario;
// import civitas.Casilla;
// import civitas.Jugador;
import civitas.TituloPropiedad;

/* ENUMS */
import civitas.OperacionesJuego;
import civitas.GestionInmobilarias;
import civitas.OperacionInmobilaria;
import civitas.SalidasCarcel;
import civitas.Respuestas;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;


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

            this.vista.mostrarSiguienteOperacion(OperacionSiguiente);

            if (OperacionSiguiente != OperacionesJuego.PASAR_TURNO) {
                vista.mostrarEventos();
            }

            if( !this.juego.finalDelJuego() ){
                
                switch (OperacionSiguiente) {
                    case COMPRAR -> {
                        if(Respuestas.SI == this.vista.comprar()){
                            this.juego.comprar();

                            this.juego.siguientePasoCompletado(OperacionSiguiente);
                        }
                    }

                    case GESTIONAR -> {
                        this.vista.gestionar();

                        GestionInmobilarias gestion = GestionInmobilarias.values()[vista.getGestion()];
                        int ip = vista.getPropiedad();

                        OperacionInmobilaria operacionInmobiliaria = new OperacionInmobilaria(gestion,ip);

                        switch (gestion) {
                            case VENDER -> {
                                this.juego.vender(operacionInmobiliaria.getNumPropiedad());
                            }
                            case HIPOTECAR -> {
                                this.juego.hipotecar(operacionInmobiliaria.getNumPropiedad());
                            }
                            case CANCELAR_HIPOTECA -> {
                                this.juego.cancelarHipoteca(operacionInmobiliaria.getNumPropiedad());
                            }

                            /* Revisar estas 2 / Se deben usar desde juego y no desde el jugador !!!!!  */
                            case CONSTRUIR_CASA -> {
                                this.juego.comprarCasa(operacionInmobiliaria.getNumPropiedad());
                            }
                            case CONSTRUIR_HOTEL -> {
                                this.juego.comprarHotel(operacionInmobiliaria.getNumPropiedad());
                            }
                            case TERMINAR -> {

                            }
                        }

                        this.juego.siguientePasoCompletado(OperacionSiguiente);
                    }

                    case SALIR_CARCEL -> {

                        if (vista.salirCarcel() == SalidasCarcel.PAGANDO) {
                            juego.salirCarcelPagando();
                        } else {
                            juego.salirCarcelTirando();
                        }
                        
                        this.juego.siguientePasoCompletado(OperacionSiguiente);
                    }

                    default -> {
                        
                    }
                }
            
                // System.out.println("\n--- RANKING FINAL ---");
                // System.out.println(juego.ranking());

            }
        }

    }

}
