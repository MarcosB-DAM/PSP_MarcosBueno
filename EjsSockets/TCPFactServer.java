import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPFactServer{
    public static void main (String[] args) throws Exception{
        int Puerto = 6060;
        ServerSocket servidor = new ServerSocket(Puerto);
        System.out.println("Esperando al Cliente...");

        Socket cliente = servidor.accept();

        ObjectInputStream entFact = new ObjectInputStream(cliente.getInputStream());
        Factura factura = (Factura) entFact.readObject();
        System.out.println("Factura " + factura.getNumero() + " recibida correctamente");

        double ivaPorc = 0.0, total, iva;

        switch (factura.getTipo_iva().toUpperCase()) {
            case "IGC":
                ivaPorc = 0.07;
                break;
        
            case "ESP":
                ivaPorc = 0.21;
                break;

            case "EUR":
                ivaPorc = 0.15;
                break;

            default:
                System.out.println("Error: no se ha especificado el tipo de IVA para este factura");
                break;
        }

        iva = factura.getImporte() * ivaPorc;
        total = factura.getImporte() + iva;

        factura.setIva(iva);
        factura.setTotal(total);

        ObjectOutputStream salFact = new ObjectOutputStream(cliente.getOutputStream());
        salFact.writeObject(factura);
        System.out.println("Factura devuelta correctamente al Cliente");

        entFact.close();
        salFact.close();
        cliente.close();

    }
}