import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class Warehouse {
    private final Map<String, Integer> inventory = new HashMap<>();
    private final int capacity;
    private final Lock lock = new ReentrantLock();

    public Warehouse(int capacity) {
        this.capacity = capacity;
    }

    public boolean addProduct(String product, int quantity) {
        lock.lock();
        try {
            int currentQuantity = inventory.getOrDefault(product, 0);
            if (currentQuantity + quantity <= capacity) {
                inventory.put(product, currentQuantity + quantity);
                System.out.println("Produced: " + quantity + " of " + product + ". Current stock: " + inventory);
                return true;
            }
            return false;
        } finally {
            lock.unlock();
        }
    }

    public boolean consumeProduct(String product, int quantity) {
        lock.lock();
        try {
            int currentQuantity = inventory.getOrDefault(product, 0);
            if (currentQuantity >= quantity) {
                inventory.put(product, currentQuantity - quantity);
                System.out.println("Consumed: " + quantity + " of " + product + ". Current stock: " + inventory);
                return true;
            } else if (currentQuantity > 0) {
                inventory.put(product, 0);
                System.out.println("Partially consumed: " + currentQuantity + " of " + product + ". Current stock: " + inventory);
                return true;
            }
            return false;
        } finally {
            lock.unlock();
        }
    }
}

class Producer implements Runnable {
    private final Warehouse warehouse;
    private final Random random = new Random();
    private final String[] products = {"A", "B", "C"};
    private volatile boolean running = true;

    public Producer(Warehouse warehouse) {
        this.warehouse = warehouse;
    }

    public void stop() {
        running = false;
    }

    @Override
    public void run() {
        while (running) {
            String product = products[random.nextInt(products.length)];
            int quantity = random.nextInt(5) + 1;
            if (warehouse.addProduct(product, quantity)) {
                try {
                    Thread.sleep(random.nextInt(500) + 200);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }
    }
}

class Consumer implements Runnable {
    private final Warehouse warehouse;
    private final Random random = new Random();
    private final String[] products = {"A", "B", "C"};
    private volatile boolean running = true;

    public Consumer(Warehouse warehouse) {
        this.warehouse = warehouse;
    }

    public void stop() {
        running = false;
    }

    @Override
    public void run() {
        while (running) {
            String product = products[random.nextInt(products.length)];
            int quantity = random.nextInt(5) + 1;
            if (warehouse.consumeProduct(product, quantity)) {
                try {
                    Thread.sleep(random.nextInt(500) + 200);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }
    }
}

public class Main {
    public static void main(String[] args) throws Exception {
        Warehouse warehouse = new Warehouse(20);
        ExecutorService producerPool = Executors.newFixedThreadPool(3);
        ExecutorService consumerPool = Executors.newFixedThreadPool(3);

        Producer[] producers = new Producer[3];
        Consumer[] consumers = new Consumer[3];

        for (int i = 0; i < 3; i++) {
            producers[i] = new Producer(warehouse);
            consumers[i] = new Consumer(warehouse);
            producerPool.submit(producers[i]);
            consumerPool.submit(consumers[i]);
        }

        System.out.println("Press Enter to stop...");
        int read = System.in.read();
        System.out.println(read);

        for (Producer producer : producers) {
            producer.stop();
        }
        for (Consumer consumer : consumers) {
            consumer.stop();
        }

        producerPool.shutdown();
        consumerPool.shutdown();

        while (!producerPool.isTerminated() || !consumerPool.isTerminated()) {
            Thread.sleep(100);
        }

        System.out.println("Program finished.");
    }
}

