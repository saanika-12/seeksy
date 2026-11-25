# Seeksy — Adaptive Disk Scheduling Simulator

🌸 **A visual disk scheduling simulator with workload analysis and algorithm recommendations.**

[Live Demo](https://seeksy.onrender.com) · [GitHub Repository](https://github.com/saanika-12/seeksy)

---

## About the Project

Seeksy is a disk scheduling simulator developed using C++, Python, Flask, HTML, CSS, and JavaScript.

It demonstrates how different disk scheduling algorithms process disk I/O requests and compares their performance using total and average head movement.

The project also includes a rule-based workload analyzer that examines the given disk request pattern and recommends a suitable scheduling algorithm.

Seeksy combines operating system concepts with an interactive interface to make disk scheduling easier to understand and visualize.

## Features

- Implements six disk scheduling algorithms
- Calculates total and average head movement
- Displays the order in which requests are serviced
- Provides workload analysis and algorithm recommendations
- Visualizes disk-head movement through animation
- Compares algorithm performance using charts
- Interactive disk configuration and request inputs
- Responsive interface with a Botanical Noir design

## Algorithms Implemented

| Algorithm | Description |
|---|---|
| FCFS | Services requests in the order they arrive |
| SSTF | Selects the request closest to the current head position |
| SCAN | Moves the head in one direction, then reverses |
| C-SCAN | Services requests in one direction and returns to the beginning |
| LOOK | Similar to SCAN, but reverses at the last pending request |
| C-LOOK | Similar to C-SCAN, but jumps between pending request extremes |

## Technology Stack

### Core Engine
- C++
- Object-Oriented Programming
- Disk scheduling algorithms

### Backend
- Python
- Flask
- REST-style API communication

### Frontend
- HTML
- CSS
- JavaScript
- Chart.js

### Deployment
- Docker
- Render
- GitHub

## How It Works

1. The user enters the disk size, initial head position, and disk requests.
2. The frontend sends the input to the Flask backend.
3. Flask passes the input to the C++ scheduling engine.
4. The engine executes the scheduling algorithms.
5. The backend returns the results to the frontend.
6. Seeksy displays the service order, head movement, performance comparison, and workload recommendation.

## Workload Analyzer

Seeksy includes a rule-based workload analyzer that examines characteristics of the disk request pattern and recommends an algorithm.

**Note:** The current analyzer uses rule-based logic. It is not a trained machine learning model.

## Sample Input

```text
Disk Size: 200
Initial Head Position: 50

Requests:
82, 170, 43, 140, 24, 16, 190
```

## Project Interface

Visit the live application to explore the interface and test the scheduling algorithms.

🔗 **[Open Seeksy](https://seeksy.onrender.com)**

## Learning Objectives

This project demonstrates:

- Operating system disk scheduling concepts
- C++ implementation of algorithms
- Object-oriented programming
- Communication between a frontend and backend
- Calling a compiled C++ program from Python
- API-based application architecture
- Data visualization and performance comparison
- Deployment of a full-stack application

## Future Improvements

- More workload patterns and test cases
- Additional disk scheduling strategies
- Improved workload analysis
- Enhanced performance visualization
- More detailed algorithm explanations

## Author

Developed as an academic project to explore disk scheduling, operating system concepts, and full-stack application development.

---

**Seeksy — Seek. Analyze. Optimize.**
