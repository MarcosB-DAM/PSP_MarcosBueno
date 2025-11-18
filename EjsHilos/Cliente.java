public class Cliente extends Thread{
    private int id;
    private ColaGym cola;

    public Cliente(int id, ColaGym cola){
        this.cola = cola;
        this.id = id;
    }

    public void run(){
        Random rand = new Random();
        int estancia;
        estancia = rand.nextInt(600 - 200 + 1) + 200;
        try{
            cola.entrar(id);
            sleep(estancia);
            System.out.println("Cliente " + id + " entrenando");
            cola.salir(id);
        }catch(InterruptedException e){
            e.printStackTrace();
        }
    }
}
