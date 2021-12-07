import java.util.Random;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;

class Monitor{
    private enum State{
        THINKING,
        HUNGRY,
        EATING
    };
    private State[] StatesOfPhilosophers;

    public Monitor(int N){
        StatesOfPhilosophers = new State[N];
        for (int i=0; i < N ;i++) StatesOfPhilosophers[i] = State.EATING;
    }

    public synchronized void put_fork(int id){
        StatesOfPhilosophers[id] = State.THINKING;
        notifyAll();
    }

    private boolean test(int id){
        if(StatesOfPhilosophers[(id + 1) % 5] == State.EATING && StatesOfPhilosophers[(id + 4) % 5] == State.EATING)
            return true;
        return false;
    }

    public synchronized void take_forks(int id) throws InterruptedException{
        StatesOfPhilosophers[id] = State.HUNGRY;
        while (test(id)) wait();
        StatesOfPhilosophers[id] = State.EATING;
    }
}

class Philosopher implements Runnable{
    private int id;
    private Monitor monitor;
    private Random sleepTime = new Random();

    public Philosopher(int id, Monitor monitor){
        this.id = id;
        this.monitor = monitor;
    }

    @Override
    public void run() {
        while (true){
            try {
                think();
                monitor.take_forks(id);
                eat();
                monitor.put_fork(id);
            }
            catch (InterruptedException e) e.printStackTrace();
        }
    }

    private void eat() throws InterruptedException{
        System.out.println("Philosopher " + id + " is eating");
        Thread.sleep(sleepTime.nextInt(10));
    }

    private void think() throws InterruptedException{
        System.out.println("Philosopher "+ id + " is thinking");
        Thread.sleep(sleepTime.nextInt(5) * 1000);
    }
}

public class DPProblem {
    private static int N = 5;
    public static void main(String[] args) {
        Philosopher[] philosophers = new Philosopher[N];
        Monitor monitor = new Monitor(N);
        ThreadPoolExecutor executor = (ThreadPoolExecutor) Executors.newCachedThreadPool();
        
        for (int i=0;i<N;i++){
            philosophers[i] = new Philosopher(i,monitor);
            executor.execute(philosophers[i]);
        }
        executor.shutdown();
    }
}




