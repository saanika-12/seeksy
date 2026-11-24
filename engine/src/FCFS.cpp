#include "FCFS.h"

// Constructor
FCFS::FCFS(int head, int size,
           const std::vector<int>& requestList)
    : DiskScheduler(head, size, requestList)
{
}

// Return algorithm name
std::string FCFS::getName() const
{
    return "FCFS";
}

// Execute FCFS scheduling
SchedulingResult FCFS::run()
{
    std::vector<int> servicedOrder = requests;
    std::vector<int> headPath;

    headPath.push_back(headPosition);

    for (int i = 0; i < requests.size(); i++)
    {
        headPath.push_back(requests[i]);
    }

    return buildResult(servicedOrder, headPath);
}