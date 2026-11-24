#include "CSCAN.h"
#include <algorithm>

// Constructor
CSCAN::CSCAN(int head, int size,
             const std::vector<int>& requestList)
    : DiskScheduler(head, size, requestList)
{
}

// Return algorithm name
std::string CSCAN::getName() const
{
    return "C-SCAN";
}

// Execute C-SCAN scheduling
SchedulingResult CSCAN::run()
{
    std::vector<int> left;
    std::vector<int> right;

    std::vector<int> servicedOrder;
    std::vector<int> headPath;

    int currentHead = headPosition;

    headPath.push_back(currentHead);

    // Divide requests into left and right groups
    for (int i = 0; i < requests.size(); i++)
    {
        if (requests[i] < currentHead)
            left.push_back(requests[i]);
        else
            right.push_back(requests[i]);
    }

    // Sort both groups
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    // Service requests towards the higher tracks
    for (int i = 0; i < right.size(); i++)
    {
        servicedOrder.push_back(right[i]);
        headPath.push_back(right[i]);
    }

    // Move to the end of the disk
    if (!left.empty())
    {
        headPath.push_back(diskSize - 1);

        // Return to the beginning
        headPath.push_back(0);
    }

    // Continue servicing from the beginning
    for (int i = 0; i < left.size(); i++)
    {
        servicedOrder.push_back(left[i]);
        headPath.push_back(left[i]);
    }

    return buildResult(servicedOrder, headPath);
}