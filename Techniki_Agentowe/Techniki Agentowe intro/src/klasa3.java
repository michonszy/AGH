import jade.core.Agent;
import jade.core.behaviours.TickerBehaviour;

public class klasa3 extends Agent {

    protected void setup() {
        System.out.println("startuję");

        //cykliczne zachowanie
        addBehaviour(new TickerBehaviour(this, 1000) {
            protected void onTick() {
                System.out.println("Wykonuję");
            }
        });
    }

    protected void takeDown() {
        System.out.println("zaraz się usunę");
    }
}