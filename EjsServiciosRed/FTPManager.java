import org.apache.commons.net.ftp.FTP;
import org.apache.commons.net.ftp.FTPClient;
import org.apache.commons.net.ftp.FTPFile;
import org.apache.commons.net.ftp.FTPReply;

import java.io.*;
import java.util.Scanner;

public class FTPManager {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        FTPClient cliente = new FTPClient();

        System.out.print("Servidor FTP: ");
        String server = sc.nextLine();
        System.out.print("Usuario: ");
        String user = sc.nextLine();
        System.out.print("Contraseña: ");
        String pass = sc.nextLine();

        try {
            cliente.connect(server);
            int respuesta = cliente.getReplyCode();
            
            if (!FTPReply.isPositiveCompletion(respuesta)) {
                cliente.disconnect();
                System.out.println("Conexión rechazada: " + respuesta);
                return;
            }

            boolean login = cliente.login(user, pass);
            if (login) {
                System.out.println("Login correcto");
                cliente.enterLocalPassiveMode();
                cliente.setFileType(FTP.BINARY_FILE_TYPE); 

                String comando = "";
                while (!comando.equalsIgnoreCase("quit")) {
                    System.out.println("(ls, mkdir, rename, put, get, quit)");
                    System.out.print("> ");
                    String lineaInput = sc.nextLine();
                    System.err.println("");
                    String[] input = lineaInput.split(" ");
                    comando = input[0].toLowerCase();

                    if (comando.equals("ls")) {
                        String ruta;
                        if (input.length > 1) {
                            ruta = input[1];
                        } else {
                            ruta = ".";
                        }
                        
                        FTPFile[] files = cliente.listFiles(ruta);
                        for (int i = 0; i < files.length; i++) {
                            String tipo;
                            if (files[i].isDirectory()) {
                                tipo = "[DIR]";
                            } else {
                                tipo = "[FILE]";
                            }
                            System.out.println(tipo + " " + files[i].getName());
                        }
                    } 
                    else if (comando.equals("mkdir")) {
                        if (input.length > 1) {
                            if (cliente.makeDirectory(input[1])) { 
                                System.out.println("Directorio creado");
                            } else {
                                System.out.println("Error al crear carpeta");
                            }
                        }
                    } 
                    else if (comando.equals("rename")) {
                        if (input.length > 2) {
                            if (cliente.rename(input[1], input[2])) {
                                System.out.println("Renombrado con éxito");
                            } else {
                                System.out.println("Error al renombrar");
                            }
                        }
                    } 
                    else if (comando.equals("put")) {
                        if (input.length > 2) {
                            // Uso: put <rutaLocal> <rutaRemota> 
                            uploadFile(cliente, input[1], input[2]);
                        } else {
                            System.out.println("Error: Uso: put <rutaLocal> <rutaRemota>");
                        }
                    } 
                    else if (comando.equals("get")) {
                        if (input.length > 2) {
                            // Uso: get <rutaRemota> <rutaLocal> 
                            downloadFile(cliente, input[1], input[2], sc);
                        } else {
                            System.out.println("Error: Uso: get <rutaRemota> <rutaLocal>");
                        }
                    } 
                    else if (!comando.equals("quit")) {
                        System.out.println("Comando no reconocido");
                    }
                }
                cliente.logout();
            } else {
                System.out.println("Login Incorrecto");
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (cliente.isConnected()) {
                    cliente.disconnect();
                }
            } catch (IOException ioe) {
                ioe.printStackTrace();
            }
        }
    }

    private static void uploadFile(FTPClient cliente, String rutaLocal, String rutaRemota) throws IOException {
        File localFile = new File(rutaLocal);
        if (!localFile.exists()) {
            System.out.println("El archivo local no existe");
            return;
        }
        FileInputStream is = new FileInputStream(localFile);
        if (cliente.storeFile(rutaRemota, is)) {
            System.out.println("Subida finalizada correctamente");
        } else {
            System.out.println("Error al subir el archivo");
        }
        is.close();
    }

    private static void downloadFile(FTPClient cliente, String rutaRemota, String rutaLocal, Scanner sc) throws IOException {
        File localFile = new File(rutaLocal);
        
        if (localFile.exists()) {
            System.out.print("El archivo ya existe localmente. ¿Sobrescribir? (s/n): ");
            String respuesta = sc.nextLine();
            if (!respuesta.equalsIgnoreCase("s")) {
                System.out.println("Descarga cancelada");
                return;
            }
        }
        
        FileOutputStream os = new FileOutputStream(localFile);
        if (cliente.retrieveFile(rutaRemota, os)) {
            System.out.println("Descarga finalizada correctamente");
        } else {
            System.out.println("Error al descargar el archivo");
        }
        os.close();
    }
}