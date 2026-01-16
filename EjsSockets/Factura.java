import java.io.Serializable;
@SuppressWarnings("serial")

public class Factura implements Serializable{
    String numero, fecha;
    double importe;
    String tipo_iva;
    double iva;
    double total;

    public Factura(String numero, String fecha, double importe, String tipo_iva){
        super();
        this.numero = numero;
        this.fecha = fecha;
        this.importe = importe;
        this.tipo_iva = tipo_iva;
    }
    public Factura(){super();}

    public String getNumero() {
        return numero;
    }
    public void setNumero(String numero) {
        this.numero = numero;
    }
    public String getFecha() {
        return fecha;
    }
    public void setFecha(String fecha) {
        this.fecha = fecha;
    }
    public double getImporte() {
        return importe;
    }
    public void setImporte(double importe) {
        this.importe = importe;
    }
    public String getTipo_iva() {
        return tipo_iva;
    }
    public void setTipo_iva(String tipo_iva) {
        this.tipo_iva = tipo_iva;
    }
    public double getIva() {
        return iva;
    }
    public void setIva(double iva) {
        this.iva = iva;
    }
    public double getTotal() {
        return total;
    }
    public void setTotal(double total) {
        this.total = total;
    }
}