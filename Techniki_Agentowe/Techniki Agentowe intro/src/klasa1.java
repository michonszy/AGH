import jade.core.Agent;

public class klasa1 extends Agent {

    protected void setup() {
        System.out.println("startuję");

        // Make this agent terminate
        doDelete();

    }
    protected void takeDown() {
        System.out.println("zaraz się usunę");
    }
}