import java.io.DataInput;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;

public class Sockets01Cliente2{
    public static void main (String[] args){
        String host = "192.168.204.103"; //Ip del server
        int puerto = 7777; //Puerto

        try(Socket cliente = new Socket(host, puerto)){
            DataInputStream dis = new DataInputStream(cliente.getInputStream());
            DataOutputStream dos = new DataOutputStream(cliente.getOutputStream());

            //Recibo el número generado desde cliente1 y enviado desde server
            int num = dis.readInt();
            System.out.println("Recibiendo " + num + " del servidor");

            //Calculo el factorial
            int total = 1;
            if (num == 0) {
                total = 1;
            }
            else{
                for(int i = num; i > 0; i--){
                    total *= i;
                }
            }
            
            dos.writeInt(total);
            System.out.println("Resultado enviado de vuelta a serviror");

            dis.close();
            dos.close();
            cliente.close();
        }
        catch(IOException e){
            e.printStackTrace();
        } 
    }
}