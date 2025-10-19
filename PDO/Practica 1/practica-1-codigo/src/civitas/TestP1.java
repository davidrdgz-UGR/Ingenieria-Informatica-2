package civitas;

import java.util.Arrays;


class TestP1 {

    public static void main() {
        System.out.println("===== TEST P1 Civitas =====");

        // ------------------------------------------------------------
        // 1) quienEmpieza() 100 veces con 4 jugadores y conteo
        
        System.out.println("\n[1] Probando quienEmpieza() 100 veces con 4 jugadores");
        Dado dado = Dado.getInstance();
        int jugadores = 4;
        int[] frecuencias = new int[jugadores];

        Arrays.fill(frecuencias, 0);

        for (int i = 0; i < 100; i++) {
            int idx = dado.quienEmpieza(jugadores);
            frecuencias[idx]++;
        }
        for (int i = 0; i < jugadores; i++) {
            System.out.printf("Jugador %d elegido %d veces\n", i, frecuencias[i]);
        }

        // ------------------------------------------------------------
        // 2) Modo debug on/off y tiradas

        System.out.println("\n[2] Probando modo debug ON/OFF y tiradas");
        dado.setDebug(true);
        System.out.println("Tiradas en DEBUG (debe salir siempre 1):");
        for (int i = 0; i < 3; i++) {
            System.out.println("tirar() = " + dado.tirar());
        }

        dado.setDebug(false);
        System.out.println("Tiradas en NORMAL (aleatorio):");
        for (int i = 0; i < 3; i++) {
            System.out.println("tirar() = " + dado.tirar());
        }

        // ------------------------------------------------------------
        // 3) getUltimoResultado() y salgoDeLaCarcel()
        
        System.out.println("\n[3] Probando getUltimoResultado() y salgoDeLaCarcel()");
        int ultimo = dado.getUltimoResultado();
        System.out.println("Último resultado guardado en el dado = " + ultimo);
        boolean sale = dado.salgoDeLaCarcel();
        System.out.println("¿Salgo de la cárcel? " + (sale ? "Sí" : "No"));

        // ------------------------------------------------------------
        // 4) Mostrar valores de los enumerados
        
        System.out.println("\n[4] Mostrando valores de TipoCasilla y TipoSorpresa");
        System.out.println("TipoCasilla: " + Arrays.toString(TipoCasilla.values()));
        System.out.println("TipoSorpresa: " + Arrays.toString(TipoSorpresa.values()));

        // ------------------------------------------------------------
        // 5) MazoSorpresas: añadir 2 sorpresas, siguiente, inhabilitar/habilitar

        System.out.println("\n[5] Probando MazoSorpresa");
        MazoSorpresa mazo = new MazoSorpresa(false); // normal
        Sorpresa s1 = new Sorpresa();
        Sorpresa s2 = new Sorpresa();
        mazo.alMazo(s1);
        mazo.alMazo(s2);

        Sorpresa activa = mazo.siguiente();
        System.out.println("Siguiente sorpresa obtenida (no nula): " + (activa != null));

        // Inhabilitar la segunda carta añadida
        mazo.inhabilitarCartaEspecial(s2);
        // Habilitar de nuevo la segunda carta
        mazo.habilitarCartaEspecial(s2);

        // ------------------------------------------------------------
        // 6) Diario: probar sus métodos (leer eventos pendientes)
        System.out.println("\n[6] Probando Diario (eventos pendientes)");
        Diario diario = Diario.getInstance();
        // Forzamos algunos eventos
        diario.ocurreEvento("Evento de prueba A");
        diario.ocurreEvento("Evento de prueba B");
        while (diario.eventosPendientes()) {
            System.out.println("Diario -> " + diario.leerEvento());
        }

        // ------------------------------------------------------------
        // 7) Tablero: casillas, errores controlados, tiradas y nuevaPosicion()
        System.out.println("\n[7] Probando Tablero");
        Tablero Tablero = new Tablero(5);
        Tablero.añadeCasilla(new Casilla("Calle 1"));
        Tablero.añadeCasilla(new Casilla("Calle 2"));
        Tablero.añadeCasilla(new Casilla("Impuesto"));
        Tablero.añadeCasilla(new Casilla("Sorpresa"));
        Tablero.añadeJuez(); 

        
        int idxInvalido = 999;
        System.out.println("getCasilla(" + idxInvalido + ") = " + Tablero.getCasilla(idxInvalido));

        
        int posicionActual = 3;
        int tirada = 20;
        int destino = Tablero.nuevaPosicion(posicionActual, tirada);
        int vecesSalida = Tablero.getPorSalida(); 
        System.out.printf("Desde %d con tirada %d -> destino %d (pasos por salida reportados: %d)\n",
                posicionActual, tirada, destino, vecesSalida);

        
        int[] tiradas = {1, 3, 6, 0};
        int pos = 0;
        for (int t : tiradas) {
            int dest = Tablero.nuevaPosicion(pos, t);
            int ps = Tablero.getPorSalida();
            System.out.printf("Pos %d + %d -> %d | porSalida=%d\n", pos, t, dest, ps);
            pos = dest;
        }

        System.out.println("\n===== FIN TEST P1 =====");
    }
}
