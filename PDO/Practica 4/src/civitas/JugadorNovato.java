package civitas;

public class JugadorNovato extends Jugador {

	private float bonusBienvenida;

	public JugadorNovato(Jugador otro, float bonusBienvenida) {
        super(otro);
        this.bonusBienvenida = bonusBienvenida;

		for (TituloPropiedad propiedad : this.propiedades) {
            propiedad.setPropietario(this);
        }

        Diario.getInstance().ocurreEvento(
            "El jugador " + this.getNombre() + " se ha convertido en NOVATO  " + ")"
        );

    }

	@Override
	boolean recibe(float cantidad) {
		cantidad = cantidad * 1.1f;

        return super.recibe( cantidad );
    }

	@Override
	boolean pagaImpuesto(float cantidad) {
		return super.pagaImpuesto(cantidad * 0.8f);
    }

	@Override
    public String toString() {
		return super.toString() + "\n [Tipo: Novato] ";
	}
	
}
