# Dispatcher-Worker Model with Linux Pthreads

## Overview
This project implements a **dispatcher/worker model** in Linux using **POSIX threads** (`pthread`). The dispatcher reads and processes a command file, assigning tasks to worker threads via a shared job queue. Workers execute tasks concurrently, following the **first-come, first-served** principle.

## Features
✅ **Multi-threading with pthreads**  
✅ **Synchronization using `pthread_mutex` and `pthread_cond_wait`**  
✅ **File-based counter management (`countXX.txt`)**  
✅ **Worker logging (`worker_threadXX.log`)**  
✅ **Dispatcher logging (`dispatcher.log`)**  
✅ **Performance statistics (`stats.log`)**  

## Usage
### **Compilation**
To compile the project, run:
```sh
make
```
This will generate an executable named `dispatcher_worker`.

### **Execution**
```sh
./dispatcher_worker cmdfile.txt num_threads num_counters log_enabled
```
#### **Arguments**
- `cmdfile.txt` – Command file with dispatcher and worker instructions.
- `num_threads` – Number of worker threads (max 4096).
- `num_counters` – Number of counter files (max 100).
- `log_enabled` – 1 (enable logs) or 0 (disable logs).

### **Example Run**
```sh
./dispatcher_worker test.txt 4 10 1
```
This will:
- Use `test.txt` as the command input file.
- Create **4 worker threads**.
- Initialize **10 counter files (`count00.txt` - `count09.txt`)**.
- Enable **logging**.

## **Command File Syntax**
Each line in `cmdfile.txt` can be:
1. **Dispatcher commands** (executed serially):
   ```
   dispatcher msleep X  # Sleeps X milliseconds
   dispatcher wait      # Waits for all worker jobs to finish
   ```
2. **Worker commands** (executed in parallel by workers):
   ```
   worker msleep 500; increment 5; decrement 3;
   worker repeat 3; increment 2; msleep 100;
   ```
   - `msleep X` – Sleeps for X milliseconds.
   - `increment X` – Increments counter `countXX.txt`.
   - `decrement X` – Decrements counter `countXX.txt`.
   - `repeat X` – Repeats the following commands X times.

## **Implementation Details**
### **Dispatcher (`dispatcher.c`)**
- Parses command-line arguments.
- Initializes counters.
- Creates worker threads.
- Reads the command file and enqueues jobs.
- Waits for workers to complete execution.

### **Worker Threads (`worker_threads.c`)**
- Continuously fetch jobs from the queue.
- Execute commands sequentially (`msleep`, `increment`, `decrement`, `repeat`).
- Log execution details to `worker_threadXX.log`.

### **Synchronization**
- **Mutex locks (`pthread_mutex_t`)** ensure safe access to shared resources.
- **Condition variables (`pthread_cond_wait`)** prevent busy-waiting.

## **Logging & Statistics**
- **Dispatcher logs** (`dispatcher.log`) track command file parsing.
- **Worker logs** (`worker_threadXX.log`) record execution times.
- **Statistics file** (`stats.log`) includes:
  ```
  total running time: X milliseconds
  sum of jobs turnaround time: Y milliseconds
  min job turnaround time: Z milliseconds
  average job turnaround time: W milliseconds
  max job turnaround time: V milliseconds
  ```

## **Makefile Commands**
```sh
make        # Compile the project
make clean  # Remove compiled files
```


