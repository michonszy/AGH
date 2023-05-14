import jade.core.Agent;
import jade.core.behaviours.TickerBehaviour;
import java.util.concurrent.TimeUnit;

public class klasa8 extends Agent {

    @Override
    protected void setup() {
        System.out.println("startuję");

        // mały tick co 2 sekundy
        addBehaviour(new TickerBehaviour(this, TimeUnit.SECONDS.toMillis(2)) {
            @Override
            protected void onTick() {
                System.out.println("mały tick");
            }
        });

        // duży tick co 5 sekund
        TickerBehaviour bigTickBehaviour = new TickerBehaviour(this, TimeUnit.SECONDS.toMillis(5)) {
            @Override
            protected void onTick() {
                System.out.println("duży tick");
            }
        };
        addBehaviour(bigTickBehaviour);

        // usun duzy tick po 50 sek
        addBehaviour(new TickerBehaviour(this, TimeUnit.SECONDS.toMillis(50)) {
            @Override
            protected void onTick() {
                removeBehaviour(bigTickBehaviour);
            }
        });

        // usun agenta po 100 sek
        addBehaviour(new TickerBehaviour(this, TimeUnit.SECONDS.toMillis(100)) {
            @Override
            protected void onTick() {
                System.out.println("zaraz się usunę");
                doDelete();
            }
        });
    }

    @Override
    protected void takeDown() {
        System.out.println("usuwam się");
    }

}
