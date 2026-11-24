#include "SCAN.h"
#include <algorithm>

// Constructor
SCAN::SCAN(int head, int size,
           const std::vector<int>& requestList)
    : DiskScheduler(head, size, requestList)
{
}

// Return algorithm name
std::string SCAN::getName() const
{
    return "SCAN";
}

// Execute SCAN scheduling
SchedulingResult SCAN::run()
{
    std::vector<int> left;
    std::vector<int> right;

    std::vector<int> servicedOrder;
    std::vector<int> headPath;

    int currentHead = headPosition;

    headPath.push_back(currentHead);

    // Separate requests on both sides of the head
    for (int i = 0; i < requests.size(); i++)
    {
        if (requests[i] < currentHead)
            left.push_back(requests[i]);
        else
            right.push_back(requests[i]);
    }

    // Sort requests
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    // Move towards higher track numbers first
    for (int i = 0; i < right.size(); i++)
    {
        servicedOrder.push_back(right[i]);
        headPath.push_back(right[i]);
    }

    // Reach the end of the disk
    if (!left.empty())
        headPath.push_back(diskSize - 1);

    // Reverse direction
    for (int i = left.size() - 1; i >= 0; i--)
    {
        servicedOrder.push_back(left[i]);
        headPath.push_back(left[i]);
    }

    return buildResult(servicedOrder, headPath);
}