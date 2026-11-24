#ifndef DISK_SCHEDULER_H
#define DISK_SCHEDULER_H

#include <string>
#include <vector>

// Holds everything an algorithm reports back after it runs.
struct SchedulingResult {
    std::string algorithmName;        // e.g. "FCFS"
    std::vector<int> servicedOrder;   // requests, in the order they were served
    std::vector<int> headPath;        // every track the head stops at (starts with the initial head)
    int totalHeadMovement;            // sum of all distances the head moved
    double averageHeadMovement;       // totalHeadMovement / number of requests
};

// The base class. Every algorithm (FCFS, SSTF, ...) will inherit from this.
class DiskScheduler {
protected:
    int headPosition;                 // where the head starts
    int diskSize;                     // number of tracks (tracks go from 0 to diskSize - 1)
    std::vector<int> requests;        // the track requests to serve

public:
    DiskScheduler(int head, int size, const std::vector<int>& requestList);
    virtual ~DiskScheduler() {}

    // Each algorithm must write its own version of these two.
    virtual std::string getName() const = 0;
    virtual SchedulingResult run() = 0;

protected:
    // Shared helpers that every algorithm can use.
    int distance(int trackA, int trackB) const;
    SchedulingResult buildResult(const std::vector<int>& servicedOrder,
                                 const std::vector<int>& headPath) const;
};

#endif