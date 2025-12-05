import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Random;
import java.util.Scanner;

public class Sockets01Cliente1{
    public static void main (String[] args){
        Scanner sc = new Scanner(System.in);
        String host = "192.168.204.103"; //Ip del servidor
        int puerto = 7777; //puerto

        try(Socket cliente1 = new Socket(host, puerto)){
            //Pasaremos un valor al servidor
            DataOutputStream dos = new DataOutputStream(cliente1.getOutputStream());
            DataInputStream dis = new DataInputStream(cliente1.getInputStream());

            //Enviamos el número
            int numRnd;
            System.out.println("Introduce un número para calcular su factorial");
            numRnd = sc.nextInt();
            dos.writeInt(numRnd);

            System.out.println("Enviando " + numRnd + " al server");

            //Recibo el resultado para mostrarlo
            int factorial = dis.readInt();
            System.out.println("El resultado de la operación factorial es " + factorial);

            dos.close();
            dis.close();
            cliente1.close();
        }
        catch(IOException e){
            e.printStackTrace();
        }
    }
}