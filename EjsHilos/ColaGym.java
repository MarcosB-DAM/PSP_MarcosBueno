public class ColaGym{
    private int contador;
    private int aforoMax = 5;
    
    public synchronized void entrar(int id){
        while (contador == aforoMax) {
            try{
                wait();
            }catch(InterruptedException e){ }
        }
        contador++;
        System.out.println("Entra al Gym el cliente " + id + ", aforo actual " + contador);
    }

    public synchronized void salir(int id){
        contador--;
        System.out.println("Sale del Gym el cliente " + id + ", aforo actual " + contador);
        notifyAll();
    }

}
