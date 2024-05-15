import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

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