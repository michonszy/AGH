import jade.core.Agent;
import jade.core.behaviours.OneShotBehaviour;

public class klasa2 extends Agent {

    protected void setup() {
        System.out.println("startuję");

        //jednokrotne zachowanie
        addBehaviour(new OneShotBehaviour() {
            public void action() {
                System.out.println("Wykonuję");
            }
        });
    }

    protected void takeDown() {
        System.out.println("zaraz się usunę");
    }
}