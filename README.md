# Process Scheduler Simulator in C++

## Overview

This project implements a Process Scheduler Simulator in C++ that demonstrates and compares the First-Come, First-Served (FCFS) and Round Robin (RR) CPU scheduling algorithms. The simulator is designed to randomly generate processes with varying arrival times and CPU burst times, simulate their scheduling using both algorithms, and calculate key performance metrics.  It also integrates with Python and Matplotlib to generate visualizations of the simulation results, including Gantt charts and comparative metric graphs.

This simulator is a valuable tool for understanding the behavior and performance of different CPU scheduling algorithms, particularly in scenarios with varying process loads and the impact of algorithm choice on metrics like waiting time, throughput, CPU utilization, and process starvation.

## Features

* **Algorithm Implementation:** Implements both FCFS and Round Robin scheduling algorithms in C++.
* **Process Generation:** Randomly generates processes with attributes:
    * **Arrival Time:**  Randomly assigned arrival times to simulate processes arriving at different points.
    * **CPU Burst Time:** Randomly assigned CPU burst times to represent varying process execution needs.
* **Configurable Parameters:**
    * **Number of Processes:**  Users can specify the number of processes to simulate via command-line argument.
    * **Time Quantum (Round Robin):** Users can configure the time quantum for the Round Robin algorithm via command-line argument.
* **Performance Metrics Calculation:** Calculates and outputs the following key performance metrics:
    * **CPU Utilization:**  Percentage of time the CPU is busy processing tasks.
    * **Average Waiting Time:** Average time processes spend waiting in the ready queue.
    * **Throughput:** Number of processes completed per unit of time.
    * **Starvation Reduction (Round Robin vs FCFS):**  Quantifies the reduction in starvation achieved by Round Robin compared to FCFS.
* **Output and Logging:**
    * **Detailed Simulation Logs:**  Outputs detailed logs of process scheduling events to the console, showing process execution order and algorithm behavior.
    * **CSV/JSON Output:**  Exports simulation results (metrics and Gantt chart data) to CSV and JSON formats for further analysis and visualization.
* **Python Visualization:**
    * **Matplotlib Integration:**  Includes Python scripts that use Matplotlib to generate insightful visualizations from the simulation output.
    * **Gantt Charts:** Generates Gantt charts for both FCFS and Round Robin algorithms, visually representing the process execution timeline.
    * **Metrics Comparison Charts:** Creates bar graphs comparing the performance metrics of FCFS and Round Robin, facilitating direct performance evaluation.
    * **Starvation Analysis:** Python scripts analyze and highlight the starvation reduction achieved by Round Robin, demonstrating its effectiveness in preventing process starvation.
* **Command-Line Interface (CLI):**  Configurable parameters (number of processes, time quantum, output format) are set via command-line arguments, making the simulator flexible and easy to use.
* **Modular Design:**  The project is designed with a modular structure, separating concerns into different classes and files for better organization, maintainability, and extensibility.
* **Well-Tested:**  The simulator has been tested to ensure the correctness of the scheduling algorithm implementations and metric calculations.
* **Version Control (Git):**  The entire project is managed using Git, with commit history documenting the development process.

## Algorithms Implemented

### 1. First-Come, First-Served (FCFS)

* **Principle:** FCFS is the simplest scheduling algorithm. Processes are executed in the order they arrive in the ready queue.
* **Advantages:**
    * Easy to understand and implement.
    * Simple to manage.
* **Disadvantages:**
    * Can lead to long waiting times for shorter processes if a long process arrives first (convoy effect).
    * Not preemptive, so a long-running process can monopolize the CPU.
    * Can suffer from process starvation if processes with short burst times keep arriving.

### 2. Round Robin (RR)

* **Principle:** RR is a preemptive algorithm designed for time-sharing systems. Each process is given a fixed time quantum to execute. If a process does not complete within its time quantum, it is preempted and moved to the back of the ready queue.
* **Advantages:**
    * Fair to all processes, as each process gets a chance to run within a time quantum.
    * Better response time compared to FCFS, especially for interactive systems.
    * Reduces the risk of starvation, as no single process can monopolize the CPU for long.
* **Disadvantages:**
    * Performance depends heavily on the choice of time quantum.
        * **Small Time Quantum:**  Increases context switching overhead, reducing CPU efficiency.
        * **Large Time Quantum:**  Approaches FCFS behavior, potentially losing RR's benefits.
    * Can have higher average waiting time compared to FCFS in some scenarios, especially when all processes have similar burst times.

### Starvation and Round Robin's Mitigation

Starvation occurs when a process is perpetually denied CPU time and cannot make progress. FCFS is prone to starvation if short processes keep arriving before long processes can get scheduled. Round Robin effectively mitigates starvation by ensuring that each process gets a slice of CPU time within a defined time quantum. This prevents any single process from monopolizing the CPU and ensures fairer allocation of resources, thus reducing the likelihood of starvation, especially for CPU-bound workloads. This simulator is designed to demonstrate this reduction in starvation through comparative metrics and visualizations.

## Project Structure

The project is organized into the following directories and files:

* **`include/`:** Header files for the C++ simulator.
    * `process.h`:  Definition of the `Process` class, representing a simulated process.
    * `process_scheduler.h`:  Definition of the `ProcessScheduler` class, implementing the scheduling algorithms and metrics calculation.
    * `cli_parser.h`: Definition of the `CLIParser` class for handling command-line arguments.
* **`src/`:** Source files for the C++ simulator.
    * `main.cpp`:  Main entry point of the simulator application, handles CLI parsing, simulation execution, and output.
    * `process.cpp`: Implementation of the `Process` class.
    * `process_scheduler.cpp`: Implementation of the `ProcessScheduler` class, containing the FCFS and Round Robin scheduling logic and metrics calculation.
    * `cli_parser.cpp`: Implementation of the `CLIParser` class.
* **`build/`:**  Directory for build artifacts (executables, object files). Created by CMake.
    * `process_scheduler`: Executable file for the Process Scheduler Simulator.
    * `plot_results.py`: Python script for generating plots from simulation results.
* **`scripts/`:**  Directory for scripts (currently contains a copy of `plot_results.py` for convenience).
    * `plot_results.py`: Python script for generating plots from simulation results.
* **`README.md`:**  Project documentation (this file).
* **`CMakeLists.txt`:** CMake configuration file for building the C++ project.

## Build and Run Instructions

### Prerequisites

* **CMake:**  Required for building the C++ project.
* **C++ Compiler:**  A C++ compiler that supports C++11 or later (e.g., g++, clang++).
* **Python 3:** Required for running the plotting scripts.
* **Matplotlib:** Python library for plotting. Install using `pip install matplotlib`.

### Building the Simulator

1. **Navigate to the project root directory** in your terminal:
   ```bash
   cd /Users/masoom/Developer/Process Scheduler 2/Process-Scheduler-Simulator
   ```

2. **Create a `build` directory** and navigate into it:
   ```bash
   mkdir build
   cd build
   ```

3. **Run CMake** to configure the build:
   ```bash
   cmake ..
   ```

4. **Build the project** using Make or your preferred build tool:
   ```bash
   cmake --build .
   ```
   This will create the `process_scheduler` executable in the `build` directory.

### Running the Simulator and Plotting Results

To run the simulator and generate plots, use the following command from the project root directory:

```bash
cmake --build build && build/process_scheduler <number_of_processes> <time_quantum> <output_file_prefix> <output_format> && python3 build/plot_results.py build/<output_file_prefix>.<output_format> png
```

**Parameters:**

* `<number_of_processes>`:  The number of processes to simulate (e.g., 50).
* `<time_quantum>`: The time quantum for the Round Robin algorithm (e.g., 4).
* `<output_file_prefix>`:  The prefix for the output files (e.g., `simulation_results`).
* `<output_format>`: Output format for simulation results (`csv` or `json`).
* `png`: Output format for the generated plots (currently only `png` is supported in the command).

**Example Command:**

```bash
cmake --build build && build/process_scheduler 50 4 build/simulation_results csv && python3 build/plot_results.py build/simulation_results.csv png
```

This command will:

1. **Build the C++ simulator.**
2. **Run the simulator** with 50 processes, a time quantum of 4, outputting results to `build/simulation_results.csv`.
3. **Execute the Python plotting script** to generate Gantt charts and metrics comparison charts as PNG files, using `build/simulation_results.csv` as input.

The generated plots (`FCFS_gantt_chart.png`, `RoundRobin_gantt_chart.png`, `metrics_comparison_chart.png`) and the simulation results file (`build/simulation_results.csv` or `build/simulation_results.json`) will be located in the `build` directory.

## Performance Metrics and Analysis

The simulator calculates and outputs the following performance metrics for both FCFS and Round Robin algorithms:

* **CPU Utilization:**  Ideally, CPU utilization should be high, indicating that the CPU is kept busy as much as possible.
* **Average Waiting Time:** Lower average waiting time is generally better, as it means processes spend less time waiting in the ready queue. Round Robin typically aims to reduce average waiting time compared to FCFS, especially with many short processes.
* **Throughput:** Higher throughput is better, indicating that more processes are completed per unit of time.
* **Starvation Reduction:** This metric quantifies the percentage reduction in a custom "starvation metric" when using Round Robin compared to FCFS.  A positive value indicates that Round Robin is effective in reducing starvation. The Python analysis script highlights if the starvation reduction exceeds a target (e.g., 30%), demonstrating Round Robin's advantage in preventing starvation.

The generated metrics comparison chart visually presents these metrics for both algorithms, allowing for a direct comparison of their performance. The Gantt charts provide a visual timeline of process execution, illustrating how each algorithm schedules processes over time. By examining these outputs, you can analyze the trade-offs between FCFS and Round Robin in different scenarios.

## Testing and Validation

The simulator has been tested through:

* **Unit Testing (Informal):**  Individual components and functions (e.g., scheduling algorithm implementations, metric calculations) were tested in isolation to ensure correctness.
* **Integration Testing:**  The entire simulation pipeline (process generation, scheduling, metric calculation, output, plotting) was tested with various parameter configurations to verify end-to-end functionality.
* **Output Validation:**  Simulation outputs (metrics, Gantt chart data) were manually inspected and compared against expected values and theoretical behavior of FCFS and Round Robin algorithms to ensure accuracy.

## Future Enhancements

Potential future enhancements for this project include:

* **Implementation of more scheduling algorithms:**  Adding Priority Scheduling, Shortest Job First (SJF), Shortest Remaining Time First (SRTF), and Multilevel Queue Scheduling algorithms.
* **GUI Development:**  Creating a graphical user interface (GUI) for easier configuration, execution, and visualization of simulation results.
* **More sophisticated process generation:**  Allowing users to specify process arrival patterns and burst time distributions.
* **Context Switching Overhead Modeling:**  Adding a parameter to model and simulate context switching overhead in Round Robin for more realistic simulations.
* **Memory Management Simulation:**  Extending the simulator to include basic memory management simulation.
* **Real-time Scheduling Algorithm Implementation:**  Exploring and implementing real-time scheduling algorithms like Rate Monotonic (RM) and Earliest Deadline First (EDF).

## Conclusion

This Process Scheduler Simulator provides a comprehensive platform for understanding and comparing CPU scheduling algorithms. By simulating FCFS and Round Robin scheduling, calculating key performance metrics, and generating insightful visualizations, this project offers valuable insights into operating system principles and the trade-offs involved in algorithm selection.  The modular design and comprehensive documentation make this project a solid foundation for further exploration and expansion in the field of operating system simulation.
