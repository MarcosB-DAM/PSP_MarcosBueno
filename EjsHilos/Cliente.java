public class Cliente extends Thread{
    private int id;
    private ColaGym cola;

    public Cliente(int id, ColaGym cola){
        this.cola = cola;
        this.id = id;
    }

    public void run(){
        try{
            cola.entrar(id);
            sleep(500);
            System.out.println("Cliente " + id + " entrenando");
            cola.salir(id);
        }catch(InterruptedException e){
            e.printStackTrace();
        }
    }
}