import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Sockets01Server {
    public static void main (String[] args){
        int numPuerto = 7777; //numPuerto
        try(ServerSocket server = new ServerSocket(numPuerto)){
            
            System.out.println("Esperando al cliente1");
            Socket cliente1 = server.accept();
            System.out.println("Cliente 1 conectado");

            System.out.println("Esperando al cliente2");
            Socket cliente2 = server.accept();
            System.out.println("Cliente2 conectado");

            DataInputStream dis1 = new DataInputStream(cliente1.getInputStream());
            DataOutputStream dos1 = new DataOutputStream(cliente1.getOutputStream());

            DataInputStream dis2 = new DataInputStream(cliente2.getInputStream());
            DataOutputStream dos2 = new DataOutputStream(cliente2.getOutputStream());

            //Recogemos los datos enviados por el cliente1
            int numcli1 = dis1.readInt();
            System.out.println("Server recibe " + numcli1 + " del cliente1");

            //Enviamos el número al cliente2
            dos2.writeInt(numcli1);
            System.out.println("Se envía el número recibido al cliente2");

            //Recogemos el fectorial del cliente2
            int factorial = dis2.readInt();
            System.out.println("Resultado recibido desde el cliente2");

            //Enviamos el resultado al cliente1
            dos1.writeInt(factorial);
            System.out.println("Se envía el resultado al cliente1");

            dis1.close();
            dis2.close();
            dos1.close();
            dos2.close();
            cliente1.close();
            cliente2.close();
        }
        catch(IOException e){
            e.printStackTrace();
        }
    }
}