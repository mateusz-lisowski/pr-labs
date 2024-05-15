import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Warehouse {
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