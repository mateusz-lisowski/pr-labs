import java.util.Random;

public class Producer implements Runnable {
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