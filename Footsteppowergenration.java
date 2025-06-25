public class FootStepPowerGeneration {
    private static int stepCount = 0;
    private static final int threshold = 100;
    private static boolean stepDetected = false;

    public static void main(String[] args) throws InterruptedException {
        String message = "Foot Step Power Generation. by The SwiftCharge";
        for (int i = 0; i < message.length() - 15; i++) {
            System.out.println(message.substring(i, i + 16));
            Thread.sleep(300);
        }

        Thread.sleep(500);
        System.out.println("Steps: 0");
        System.out.println("Volt: 0.00V");

        // Simulate loop
        while (true) {
            int sensorValue = simulateSensorValue(); // Replace with real value in real application
            float voltage = (float) ((sensorValue * (5.0 / 1023.0)) - 0.41);

            if (sensorValue > threshold && !stepDetected) {
                stepCount++;
                stepDetected = true;
                System.out.println("Steps: " + stepCount);
                System.out.println("Step Detected. Count: " + stepCount);
            }

            if (sensorValue < threshold - 20) {
                stepDetected = false;
            }

            System.out.printf("Volt: %.2fV\n", voltage);
            Thread.sleep(50);
        }
    }

    // Simulate analogRead from piezo sensor
    private static int simulateSensorValue() {
        // You can modify this logic for testing (e.g., random or predefined pattern)
        return (int)(Math.random() * 200); // Returns 0–199 randomly
    }
}
