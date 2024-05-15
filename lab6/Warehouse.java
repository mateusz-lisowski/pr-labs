import java.util.HashMap;
import java.util.Map;

public class Warehouse {
    private final Map<String, Integer> inventory = new HashMap<>();
    private final int capacity;

    public Warehouse(int capacity) {
        this.capacity = capacity;
    }

    public synchronized boolean addProduct(String product, int quantity) {
        int currentQuantity = inventory.getOrDefault(product, 0);
        if (currentQuantity + quantity <= capacity) {
            inventory.put(product, currentQuantity + quantity);
            System.out.println("Produced: " + quantity + " of " + product + ". Current stock: " + inventory);
            return true;
        }
        return false;
    }

    public synchronized boolean consumeProduct(String product, int quantity) {
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
    }
}