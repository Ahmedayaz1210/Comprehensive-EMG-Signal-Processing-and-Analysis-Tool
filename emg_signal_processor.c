#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define SAMPLE_SIZE 1000
#define WINDOW_SIZE 20
#define FREQUENCY 1000 // Hz

// Structure to hold raw and processed EMG data
typedef struct {
    double raw[SAMPLE_SIZE];
    double filtered[SAMPLE_SIZE];
    double envelope[SAMPLE_SIZE];
} EMGSignal;

// Simulates acquisition of EMG signal
void acquireEMGSignal(EMGSignal* signal) {
    srand(time(NULL));
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        // Generate random values between -10 and 10
        signal->raw[i] = (rand() % 200) / 10.0 - 10.0;
    }
}

// Calculates Root Mean Square (RMS) of the signal
double calculateRMS(double signal[], int start, int end) {
    double sum = 0;
    for (int i = start; i < end; i++) {
        sum += signal[i] * signal[i];
    }
    return sqrt(sum / (end - start));
}

// Applies a simple moving average filter
void applyMovingAverageFilter(double input[], double output[], int size, int windowSize) {
    for (int i = 0; i < size; i++) {
        double sum = 0;
        int count = 0;
        for (int j = i - windowSize / 2; j <= i + windowSize / 2; j++) {
            if (j >= 0 && j < size) {
                sum += input[j];
                count++;
            }
        }
        output[i] = sum / count;
    }
}

// Calculates the envelope of the signal using RMS
void calculateEnvelope(double input[], double output[], int size, int windowSize) {
    for (int i = 0; i < size; i++) {
        output[i] = calculateRMS(input, i - windowSize / 2, i + windowSize / 2);
    }
}

// Calculates the mean frequency of the signal
double calculateMeanFrequency(double signal[], int size) {
    double sum = 0;
    double weightedSum = 0;
    for (int i = 0; i < size / 2; i++) {
        double magnitude = fabs(signal[i]);
        sum += magnitude;
        weightedSum += magnitude * i * FREQUENCY / size;
    }
    return weightedSum / sum;
}

// Saves processed data to a CSV file
void saveToFile(const char* filename, EMGSignal* signal) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "Time,Raw,Filtered,Envelope\n");
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        fprintf(file, "%.3f,%.2f,%.2f,%.2f\n", 
                (double)i / FREQUENCY, signal->raw[i], signal->filtered[i], signal->envelope[i]);
    }
    fclose(file);
    printf("Data saved to %s\n", filename);
}

int main() {
    EMGSignal emgSignal;
    memset(&emgSignal, 0, sizeof(EMGSignal));

    printf("EMG Signal Processing and Analysis\n");

    // Generate and process EMG signal
    acquireEMGSignal(&emgSignal);
    applyMovingAverageFilter(emgSignal.raw, emgSignal.filtered, SAMPLE_SIZE, WINDOW_SIZE);
    calculateEnvelope(emgSignal.filtered, emgSignal.envelope, SAMPLE_SIZE, WINDOW_SIZE);

    // Calculate and display RMS
    printf("RMS of raw signal: %.2f\n", calculateRMS(emgSignal.raw, 0, SAMPLE_SIZE));
    printf("RMS of filtered signal: %.2f\n", calculateRMS(emgSignal.filtered, 0, SAMPLE_SIZE));

    // Calculate and display mean frequency
    printf("Mean Frequency: %.2f Hz\n", calculateMeanFrequency(emgSignal.raw, SAMPLE_SIZE));

    // Find maximum activation
    double maxActivation = 0;
    int maxActivationTime = 0;
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        if (emgSignal.envelope[i] > maxActivation) {
            maxActivation = emgSignal.envelope[i];
            maxActivationTime = i;
        }
    }
    printf("Maximum Activation: %.2f at %.3f seconds\n", maxActivation, (double)maxActivationTime / FREQUENCY);

    // Save processed data to file
    saveToFile("emg_analysis.csv", &emgSignal);

    return 0;
}