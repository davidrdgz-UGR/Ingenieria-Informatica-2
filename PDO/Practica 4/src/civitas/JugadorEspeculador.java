package civitas;

import java.util.ArrayList;

public class JugadorEspeculador extends Jugador {

    private static final int FACTOR_ESPECULADOR = 2;
    private float fianza;

    /* ---------------- CONSTRUCTOR ---------------- */

    public JugadorEspeculador(Jugador otro, float fianza) {
        super(otro);
        this.fianza = fianza;

        for (TituloPropiedad propiedad : this.propiedades) {
            propiedad.setPropietario(this);
        }

        Diario.getInstance().ocurreEvento(
            "El jugador " + this.getNombre() + " se ha convertido en ESPECULADOR (fianza: " + fianza + ")"
        );
    }

	/* ---------------- METODOS ---------------- */

    @Override
    boolean pagaImpuesto(float cantidad) {
        // El especulador paga la mitad
        return super.pagaImpuesto(cantidad / FACTOR_ESPECULADOR);
    }

    @Override
    protected boolean debeSerEncarcelado() {

        // Si ya tiene salvoconducto - comportamiento normal
        if (!super.debeSerEncarcelado()) {
            return false;
        }

        // Si puede pagar la fianza, no entra en la cárcel
        if (getSaldo() >= fianza) {
            paga(fianza);
            Diario.getInstance().ocurreEvento(
                "El jugador " + getNombre() + " paga la fianza (" + fianza + ") y evita la cárcel"
            );
            return false;
        }

        return true;
    }

    @Override
    public int getCasasMax() {
        return super.getCasasMax() * FACTOR_ESPECULADOR;
    }

    @Override
    public int getHotelesMax() {
        return super.getHotelesMax() * FACTOR_ESPECULADOR;
    }


    @Override
    public String toString() {
        return super.toString() + " [ESPECULADOR | fianza=" + fianza + "]";
    }
}
