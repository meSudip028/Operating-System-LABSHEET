# Operating System Lab Sheet

A collection of **Operating System laboratory programs implemented in C**, covering CPU scheduling, process management, deadlocks, disk scheduling, memory management, synchronization, system calls, IPC, and other core OS concepts.

This repository is primarily created for **BSc CSIT Operating System practicals**, learning, revision, and experimentation with OS concepts through C programs.

---

## 📚 Topics Covered

| #  | Topic                                                             | What it means                                               |
| -- | ----------------------------------------------------------------- | ----------------------------------------------------------- |
| 1  | [CPU Scheduling](#1-cpu-scheduling)                               | How the operating system decides which process gets the CPU |
| 2  | [Process Management](#2-process-management)                       | How processes are created, executed, and managed            |
| 3  | [Deadlock](#3-deadlock)                                           | A situation where processes wait forever for resources      |
| 4  | [Disk Scheduling](#4-disk-scheduling)                             | How the OS decides the order of disk I/O requests           |
| 5  | [Memory Management](#5-memory-management)                         | How the OS allocates and manages main memory                |
| 6  | [Process Synchronization](#6-process-synchronization)             | How processes/threads safely share resources                |
| 7  | [Inter-Process Communication](#7-inter-process-communication-ipc) | How processes communicate and exchange data                 |
| 8  | [System Calls](#8-system-calls)                                   | How programs request services from the operating system     |
| 9  | [Menu Driven OS Programs](#9-menu-driven-os-programs)             | Interactive programs demonstrating multiple OS operations   |
| 10 | [Lab Screenshots](#10-lab-screenshots)                            | Output screenshots and practical evidence                   |

---

# 1. CPU Scheduling

📁 **Folder:** `CPU Scheduling/`

### What is CPU Scheduling?

CPU scheduling is the process used by an operating system to **select which ready process should get the CPU next**.

When multiple processes are waiting to execute, the scheduler chooses one according to a scheduling algorithm.

### Important Terms

* **Arrival Time (AT):** Time at which a process enters the ready queue.

* **Burst Time (BT):** Amount of CPU time required by a process.

* **Completion Time (CT):** Time at which a process finishes.

* **Turnaround Time (TAT):** Total time taken by a process from arrival to completion.

  `TAT = CT - AT`

* **Waiting Time (WT):** Time spent waiting in the ready queue.

  `WT = TAT - BT`

### Algorithms in this repository

#### FCFS — First Come First Serve

The process that arrives first gets the CPU first.

**Example:**

```text
P1 → P2 → P3
```

Simple, but a long process can make shorter processes wait for a long time.

#### SJF — Shortest Job First

The process with the **shortest burst time** is selected first.

```text
Shortest BT → CPU
```

It can provide low average waiting time, but long processes may suffer starvation.

#### SRTF — Shortest Remaining Time First

SRTF is the **preemptive version of SJF**.

If a new process arrives with a shorter remaining burst time, the currently running process can be interrupted.

#### Priority Scheduling

The CPU is assigned according to process priority.

A higher-priority process is selected before a lower-priority process.

#### Round Robin

Each process receives a fixed amount of CPU time called a **time quantum**.

Example:

```text
P1 → P2 → P3 → P1 → P2 → ...
```

It is commonly associated with time-sharing systems.

---

# 2. Process Management

📁 **Folder:** `Process-Management/`

### What is a Process?

A **process is a program that is currently executing**.

For example:

```text
Program → becomes → Process
```

A process has information such as:

* Process ID
* Program counter
* CPU registers
* Memory
* State
* Open files

### Programs in this folder

#### `getpid.c`

Demonstrates obtaining the **Process ID (PID)** of a process.

#### `childprocessusefork.c`

Demonstrates creation of a child process using the `fork()` system call.

Conceptually:

```text
Parent Process
      |
    fork()
      |
 ┌────┴────┐
Parent    Child
```

#### `mulchildprocess.c`

Demonstrates creation of multiple child processes.

#### `wait.c`

Demonstrates the use of `wait()` to allow a parent process to wait for a child process to finish.

### Important idea

A process can create another process.

```text
Parent
  |
 fork()
  |
Child
```

---

# 3. Deadlock

📁 **Folder:** `Deadlock/`

### What is Deadlock?

A **deadlock** occurs when a group of processes are permanently waiting for resources held by each other.

Example:

```text
P1 holds R1 → waits for R2
P2 holds R2 → waits for R1
```

Neither process can continue.

### Four Necessary Conditions

Deadlock can occur when all four conditions exist:

1. **Mutual Exclusion** — A resource can be used by only one process at a time.
2. **Hold and Wait** — A process holds one resource while waiting for another.
3. **No Preemption** — A resource cannot be forcibly taken from a process.
4. **Circular Wait** — Processes form a circular chain of waiting.

### `BAfordeadlock.c`

This program demonstrates the **Banker's Algorithm**, which is used for deadlock avoidance.

The basic idea is:

> Before allocating resources, check whether the system will remain in a safe state.

---

# 4. Disk Scheduling

📁 **Folder:** `Disk-Scheduling/`

### What is Disk Scheduling?

When many processes request disk operations, the operating system must decide **which disk request should be serviced first**.

The goal is generally to reduce disk head movement and improve performance.

### Important Term

**Seek Time:** Time required for the disk head to move to the required track.

### Algorithms in this repository

#### FCFS

Requests are served in the order they arrive.

```text
Request 1 → Request 2 → Request 3
```

Simple but may result in large head movement.

#### SSTF — Shortest Seek Time First

The request closest to the current head position is served first.

#### SCAN

The disk head moves in one direction, servicing requests along the way, then reverses direction.

It is often compared to an **elevator**.

```text
← ← ←
       |
       |
→ → → →
```

#### C-SCAN — Circular SCAN

The head moves in one direction only.

After reaching the end, it returns to the beginning and continues servicing requests.

#### LOOK

Similar to SCAN, but the head goes only as far as the **last pending request** instead of going all the way to the physical end.

#### C-LOOK

Similar to C-SCAN, but instead of moving to the physical end, the head moves only to the last request before jumping back to the first request.

---

# 5. Memory Management

📁 **Folder:** `Memory-Management/`

### What is Memory Management?

Memory management is the responsibility of the operating system to **allocate, track, and deallocate main memory for processes**.

The OS must efficiently decide:

> Where should a process be placed in memory?

### Memory Allocation Algorithms

#### First Fit

Allocate the **first available memory block** that is large enough.

```text
Blocks:
100 | 500 | 200 | 300

Process = 180

First suitable block → 500
```

#### Best Fit

Allocate the **smallest available block** that can accommodate the process.

The goal is to reduce the leftover space in that particular allocation.

#### Worst Fit

Allocate the **largest available block**.

The idea is to leave the remaining space large enough for future allocations.

---

## Page Replacement

When a page fault occurs and there is no free frame, the OS must decide **which page should be removed from memory**.

### FIFO — First In First Out

The page that entered memory first is removed first.

```text
Oldest page → Removed
```

### LRU — Least Recently Used

The page that has not been used for the longest time is removed.

### Optimal Page Replacement

The page that will **not be used for the longest time in the future** is replaced.

It gives the theoretical minimum number of page faults, but it requires knowledge of future references, so it is mainly used as a benchmark.

---

# 6. Process Synchronization

📁 **Folder:** `Synchronization/`

### What is Process Synchronization?

Process synchronization is the coordination of processes or threads so that they can safely access **shared resources**.

Without synchronization, multiple processes accessing the same data can produce incorrect results.

### Critical Section

A **critical section** is the part of a program where shared data or resources are accessed.

Example:

```text
Process A ──┐
            ├── Shared Resource
Process B ──┘
```

Only the appropriate process should access the critical section at the required time.

### Problems demonstrated

#### Dining Philosophers Problem

Demonstrates synchronization problems involving multiple processes competing for shared resources.

#### Producer-Consumer Problem

A producer creates data and puts it into a shared buffer.

A consumer removes data from the buffer.

```text
Producer → Buffer → Consumer
```

The buffer must be synchronized so that:

* Producer does not insert into a full buffer.
* Consumer does not remove from an empty buffer.
* Shared data is accessed safely.

#### Reader-Writer Problem

Multiple readers may read shared data simultaneously, but writing generally requires exclusive access.

```text
Readers → Shared Data
Writer  → Shared Data
```

#### POSIX Threads

POSIX provides APIs for creating and managing threads on Unix-like operating systems.

---

# 7. Inter-Process Communication (IPC)

📁 **Folder:** `IPC/`

### What is IPC?

**Inter-Process Communication (IPC)** refers to mechanisms that allow separate processes to **communicate and exchange data**.

Processes normally have separate address spaces, so the operating system provides mechanisms for communication.

Examples of IPC mechanisms include:

* Pipes
* Message queues
* Shared memory
* Signals
* Sockets

The `ipc.c` program demonstrates IPC concepts using C/system facilities.

---

# 8. System Calls

📁 **Folder:** `System-Calls/`

### What is a System Call?

A system call is a mechanism through which a user-level program **requests a service from the operating system kernel**.

Conceptually:

```text
User Program
     ↓
System Call
     ↓
Operating System Kernel
     ↓
Hardware / OS Service
```

### `chmod.c`

Demonstrates changing file permissions using `chmod()`.

Example permissions:

```text
Read    → r
Write   → w
Execute → x
```

### `dirent.c`

Demonstrates working with directories using directory-related system/library interfaces.

---

# 9. Menu Driven OS Programs

📁 **Folder:** `Menu-Driven-OS/`

### What is a Menu-Driven Program?

A menu-driven program provides the user with multiple choices and performs an operation based on the selected option.

Example:

```text
1. FCFS
2. SJF
3. Round Robin
4. Exit
```

The program demonstrates how multiple OS-related operations can be organized into an interactive interface.

---

# 10. Lab Screenshots

📁 **Folder:** `Screenshots/`

This folder contains screenshots of the laboratory programs and their outputs.

The screenshots are included as practical evidence and for reference while reviewing the programs.

---

# 🛠️ Technologies Used

* **Language:** C
* **Operating System:** macOS / Unix-like environment
* **Compiler:** GCC / Clang
* **Version Control:** Git
* **Repository Hosting:** GitHub

---

# ▶️ How to Run the Programs

Clone the repository:

```bash
git clone https://github.com/meSudip028/Operating-System-LABSHEET.git
```

Move into the repository:

```bash
cd Operating-System-LABSHEET
```

Compile a C program:

```bash
gcc "CPU Scheduling/fcfs.c" -o fcfs
```

Run it:

```bash
./fcfs
```

For another program, replace the source file and executable name:

```bash
gcc "Memory-Management/ffbfwf.c" -o ff
./ff
```

> **Note:** Some programs may use Unix/macOS-specific system calls or libraries and may behave differently on Windows.

---

# 📂 Repository Structure

```text
Operating-System-LABSHEET/
│
├── CPU Scheduling/
│   ├── fcfs.c
│   ├── prioritysa.c
│   ├── rr.c
│   ├── sjf.c
│   └── srtf.c
│
├── Deadlock/
│   └── BAfordeadlock.c
│
├── Disk-Scheduling/
│   ├── c-look.c
│   ├── c-scan.c
│   ├── fcfsdsa.c
│   ├── lookdsa.c
│   ├── scandsa.c
│   └── sstfdsa.c
│
├── Memory-Management/
│   ├── ffbfwf.c
│   ├── fifopra.c
│   ├── lrupra.c
│   └── optpra.c
│
├── Menu-Driven-OS/
│   └── menudrivenos.c
│
├── Process-Management/
│   ├── childprocessusefork.c
│   ├── getpid.c
│   ├── mulchildprocess.c
│   └── wait.c
│
├── Screenshots/
│   └── lab*.png
│
├── Synchronization/
│   ├── dpproblem.c
│   ├── pcproblem.c
│   ├── posix.c
│   └── rwproblem.c
│
├── System-Calls/
│   ├── chmod.c
│   └── dirent.c
│
├── IPC/
│   └── ipc.c
│
└── README.md
```

---

# 🎯 Learning Goals

This laboratory repository helps demonstrate the practical implementation of fundamental Operating System concepts:

* CPU scheduling
* Process creation and management
* Deadlock avoidance
* Disk scheduling
* Memory allocation
* Page replacement
* Process synchronization
* Inter-process communication
* System calls
* POSIX programming

The main goal is not only to run the programs, but to understand **how operating system concepts work at the programming level**.

---

# 👨‍💻 Author

**Sudip Bhattarai**

BSc CSIT Student

GitHub: **[@meSudip028](https://github.com/meSudip028)**

---

## ⭐ If this repository helped you

Feel free to explore the programs, experiment with them, and modify them to understand how different Operating System algorithms behave.
