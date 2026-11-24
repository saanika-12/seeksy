#include "SSTF.h"

// Constructor
SSTF::SSTF(int head, int size,
           const std::vector<int>& requestList)
    : DiskScheduler(head, size, requestList)
{
}

// Return algorithm name
std::string SSTF::getName() const
{
    return "SSTF";
}

// Execute SSTF scheduling
SchedulingResult SSTF::run()
{
    std::vector<int> remainingRequests = requests;
    std::vector<int> servicedOrder;
    std::vector<int> headPath;

    int currentHead = headPosition;

    headPath.push_back(currentHead);

    while (!remainingRequests.empty())
    {
        int closestIndex = 0;
        int shortestDistance = distance(
            currentHead, remainingRequests[0]);

        // Find the closest request
        for (int i = 1; i < remainingRequests.size(); i++)
        {
            int currentDistance = distance(
                currentHead, remainingRequests[i]);

            if (currentDistance < shortestDistance)
            {
                shortestDistance = currentDistance;
                closestIndex = i;
            }
        }

        // Service the closest request
        int selectedRequest = remainingRequests[closestIndex];

        servicedOrder.push_back(selectedRequest);
        headPath.push_back(selectedRequest);

        currentHead = selectedRequest;

        // Remove the completed request
        remainingRequests.erase(
            remainingRequests.begin() + closestIndex);
    }

    return buildResult(servicedOrder, headPath);
}