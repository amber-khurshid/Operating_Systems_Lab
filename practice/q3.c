#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

// Mutex for synchronization
pthread_mutex_t lock;

// Device update intervals (in seconds)
#define HEART_RATE_INTERVAL 4
#define OXYGEN_INTERVAL 3
#define BLOOD_PRESSURE_INTERVAL 10
#define GLUCOSE_INTERVAL 3
#define RESPIRATORY_INTERVAL 5

// Structure to hold device information
struct device {
    char* name;
    int interval;
};

// Function to simulate device application
void* device_application(void* arg) {
    struct device* dev = (struct device*)arg;
    pthread_mutex_lock(&lock);
    printf("%s started and running for %d seconds\n", dev->name, dev->interval);
    pthread_mutex_unlock(&lock);
    sleep(dev->interval);
    pthread_mutex_lock(&lock);
    printf("%s updated and took %d seconds\n", dev->name, dev->interval);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // Device information
    struct device devices[] = {
        {"Heart Rate Monitor", HEART_RATE_INTERVAL},
        {"Oxygen Monitor", OXYGEN_INTERVAL},
        {"Blood Pressure Monitor", BLOOD_PRESSURE_INTERVAL},
        {"Glucose Monitor", GLUCOSE_INTERVAL},
        {"Respiratory Monitor", RESPIRATORY_INTERVAL}
    };

    // Number of devices
    int num_devices = sizeof(devices) / sizeof(devices[0]);

    // Thread array
    pthread_t threads[num_devices];

    // Start time
    time_t start_time = time(NULL);

    printf("Initializing OS +++++++++++++\n");
    printf("Starting all the applications +++++++++++++\n");

    // Create threads for each device application
    for (int i = 0; i < num_devices; i++) {
        pthread_create(&threads[i], NULL, device_application, (void*)&devices[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < num_devices; i++) {
        pthread_join(threads[i], NULL);
    }

    // End time
    time_t end_time = time(NULL);

    // Total time taken
    double total_time = difftime(end_time, start_time);

    printf("Total time taken by all applications: %.2f seconds\n", total_time);
    printf("Terminating Kernel Process +++++++++++++\n");

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    return 0;
}