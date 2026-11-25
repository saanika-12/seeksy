FROM python:3.11-slim

# Install the C++ compiler
RUN apt-get update && apt-get install -y g++ \
    && rm -rf /var/lib/apt/lists/*

# Set the project directory
WORKDIR /app

# Copy the project files
COPY . .

# Install Python dependencies
RUN pip install --no-cache-dir -r requirements.txt

# Compile the C++ scheduling API for Linux
RUN g++ -std=c++11 \
    -I engine/include \
    engine/src/api_main.cpp \
    engine/src/DiskScheduler.cpp \
    engine/src/FCFS.cpp \
    engine/src/SSTF.cpp \
    engine/src/SCAN.cpp \
    engine/src/CSCAN.cpp \
    engine/src/LOOK.cpp \
    engine/src/CLOOK.cpp \
    engine/src/WorkloadAnalyzer.cpp \
    -o engine/seeksy_api

# Start the Flask application
CMD ["gunicorn", "--bind", "0.0.0.0:10000", "backend.app:app"]