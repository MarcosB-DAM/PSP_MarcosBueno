import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.Scanner;

public class TCPFactClient{
    public static void main (String[] args) throws Exception{
        String Host = "localhost";
        int Puerto = 6060;

        //Datos de la factura
        String numFact, fechFact, tip_IVA;
        double impFact;

        //Recojo los datos de la factura
        Scanner sc = new Scanner(System.in);
        System.out.println("Programa CLIENTE iniciado");

        Socket cliente = new Socket(Host, Puerto);

        System.out.println("Introduce el número de la factura: ");
        numFact = sc.nextLine();
        

        System.out.println("Introduce la fecha de la factura: ");
        fechFact = sc.nextLine();

        System.out.println("Introduzca el importe de la factura: ");
        impFact = sc.nextDouble();
        sc.nextLine();

        System.out.println("Introduzca el tipo de IVA (IGC, ESP o EUR): ");
        tip_IVA = sc.next();

        Factura fact = new Factura(numFact, fechFact, impFact, tip_IVA);

        ObjectOutputStream factSal = new ObjectOutputStream(cliente.getOutputStream());

        factSal.writeObject(fact);
        System.out.println("Factura enviada al servidor correctamente");


        ObjectInputStream entFact = new ObjectInputStream(cliente.getInputStream());
        Factura facturaFinal = (Factura) entFact.readObject();

        System.out.println("==============================================");
        System.out.println("Factura calculada correctamente");
        System.out.println("Número de Factura: " + facturaFinal.getNumero());
        System.out.println("Fecha de emisión: " + facturaFinal.getFecha());
        System.out.println("Importe: " + facturaFinal.getImporte());
        System.out.println("Tipo de IVA: " + facturaFinal.getTipo_iva());
        System.out.println("IVA: " + facturaFinal.getIva());
        System.out.println("TOTAL: " + facturaFinal.getTotal());

        entFact.close();
        factSal.close();
        cliente.close();
    }
}