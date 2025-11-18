public class SalaGym{

    private static int numClientes = 20;

    public static void main(String[] args) {
        ColaGym cola = new ColaGym();
        for(int i = 1; i <= numClientes; i++){
            Cliente c = new Cliente(i, cola);
            c.start();
            try{
                Thread.sleep(100);
            }catch(InterruptedException e){ }
        }
    }
}
