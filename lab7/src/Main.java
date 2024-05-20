import java.util.Map;
import java.util.Scanner;
import java.util.concurrent.*;

public class Main {
    private static class CachingPrimeChecker {
        private final Map<Long, CompletableFuture<Boolean>> cache = new ConcurrentHashMap<>();

        public boolean isPrime(final long x) throws ExecutionException, InterruptedException {
            CompletableFuture<Boolean> result = cache.computeIfAbsent(x, this::computeIfPrime);
            return result.get();
        }

        private CompletableFuture<Boolean> computeIfPrime(long x) {
            return CompletableFuture.supplyAsync(() -> {
                final String currentThreadName = Thread.currentThread().getName();
                System.out.printf("\t[%s] Running computation for: %d%n", currentThreadName, x);
                try {
                    // simulating long computations
                    Thread.sleep(TimeUnit.SECONDS.toMillis(2));
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                if (x < 2) {
                    return false;
                }
                for (long i = 2; i * i <= x; i++) {
                    if (x % i == 0) {
                        return false;
                    }
                }
                return true;
            });
        }
    }

    public static void main(String[] args) throws Exception {
        CachingPrimeChecker primeChecker = new CachingPrimeChecker();
        ExecutorService threadPool = Executors.newFixedThreadPool(4);
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("Enter 4 numbers separated by space (or type 'exit' to quit):");
            String input = scanner.nextLine();
            if (input.equalsIgnoreCase("exit")) {
                break;
            }

            String[] inputs = input.split("\\s+");
            if (inputs.length != 4) {
                System.out.println("Please enter exactly 4 numbers.");
                continue;
            }

            long[] numbers = new long[4];
            try {
                for (int i = 0; i < 4; i++) {
                    numbers[i] = Long.parseLong(inputs[i]);
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter 4 valid numbers.");
                continue;
            }

            CountDownLatch latch = new CountDownLatch(4);
            for (long number : numbers) {
                threadPool.submit(() -> {
                    try {
                        boolean isPrime = primeChecker.isPrime(number);
                        System.out.printf("%d is %s%n", number, isPrime ? "a prime number" : "not a prime number");
                    } catch (ExecutionException | InterruptedException e) {
                        System.err.printf("Error checking if %d is a prime number: %s%n", number, e.getMessage());
                    } finally {
                        latch.countDown();
                    }
                });
            }

            latch.await();
        }

        threadPool.shutdown();
        scanner.close();
        System.out.println("Program ended.");
    }
}
