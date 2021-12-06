import java.util.Random;
import java.util.concurrent.Executors;
import java.util.Scanner;
import java.util.concurrent.ThreadPoolExecutor;


public class Solution {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a number of philosophers");
        int N = sc.nextInt();
        Philosopher[] philosopher_array = new Philosopher[N];
        Chopstick[] chopstick_array = new Chopstick[N];
        Monitor monitor = new Monitor();
        // in newCachedThreadPool doesn't need a number of pools as newFixedThreadPool
        ThreadPoolExecutor poolExecutor = (ThreadPoolExecutor) Executors.newCachedThreadPool();
        for (int i = 0; i < N; i++) {
            philosopher_array[i] = new Philosopher(i, monitor, chopstick_array[(i - 1 + N) % N], chopstick_array[i]);
            poolExecutor.execute(philosopher_array[i]);
        }
        poolExecutor.shutdown();
        sc.close();
    }
}

public class Philosopher implements Runnable {
    public enum State {
        PlanningToEat,
        Thinking,
        Eating
    }

    public State state;
    public int id;
    public Monitor monitor;
    public Chopstick leftChopstick;
    public Chopstick rightChopstick;

    public Philosopher(int id, Monitor monitor, Chopstick leftChopstick, Chopstick rightChopstick) {
        this.id = id;
        this.monitor = monitor;
        this.leftChopstick = leftChopstick;
        this.rightChopstick = rightChopstick;
        this.state = State.Thinking;
    }

    public void run() {
        while (true) {
            think();
            monitor.takeChopsticks(this);
            eat();
            monitor.freeChopsticks(this);
        }
    }

    private void think() {
        Thread.sleep(1000);
    }

    private void eat() {
        Thread.sleep(1000);
    }
}

class Monitor {
    public synchronized void takeChopsticks(Philosopher philosopher) throws InterruptedException {
        philosopher.state = Philosopher.State.Eating;
        while (philosopher.leftChopstick.isTaken() || philosopher.rightChopstick.isTaken()) {
            wait();
        }
        philosopher.leftChopstick.take();
        philosopher.rightChopstick.take();
        philosopher.state = Philosopher.State.Eating;
    }

    public synchronized void freeChopsticks(Philosopher philosopher) {
        philosopher.state = Philosopher.State.Thinking;
        philosopher.leftChopstick.put();
        philosopher.rightChopstick.put();
        notifyAll();
    }
}

public class Chopstick {
    private boolean taken = false;

    public boolean isTaken() {
        return taken;
    }

    public boolean put() {
        taken = false;
    }

    public boolean take() {
        taken = true;
    }
}