# Comprehensive EMG Signal Processing and Analysis Tool

## Overview
This C project demonstrates various signal processing techniques applied to simulated Electromyography (EMG) data. It's designed to showcase skills in digital signal processing, data analysis, and scientific computing relevant to biomedical engineering applications.

## Features
- EMG signal simulation
- Moving average filtering
- Root Mean Square (RMS) calculation
- Envelope detection
- Mean frequency analysis
- Maximum activation detection
- Data export to CSV for further analysis

## Requirements
- C99 or later
- Standard C libraries (math.h, time.h)

## Usage
1. Compile the source code:
   ```
   gcc emg_analysis.c -o emg_analysis -lm
   ```
2. Run the executable:
   ```
   ./emg_analysis
   ```
## Output
The program will generate a simulated EMG signal, process it, and provide analysis results including RMS values, mean frequency, and maximum activation. Processed data will be saved to `emg_analysis.csv`.

## Future Enhancements
- Implement additional filtering techniques (e.g., bandpass filter)
- Add more advanced frequency domain analyses (e.g., power spectrum density)
- Develop a user interface for interactive analysis
- Integrate with real EMG acquisition hardware
