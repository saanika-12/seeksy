#include "LOOK.h"
#include <algorithm>

// Constructor
LOOK::LOOK(int head, int size,
           const std::vector<int>& requestList)
    : DiskScheduler(head, size, requestList)
{
}

// Return algorithm name
std::string LOOK::getName() const
{
    return "LOOK";
}

// Execute LOOK scheduling
SchedulingResult LOOK::run()
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

    // Service requests on the right side first
    for (int i = 0; i < right.size(); i++)
    {
        servicedOrder.push_back(right[i]);
        headPath.push_back(right[i]);
    }

    // Reverse direction and service left-side requests
    for (int i = left.size() - 1; i >= 0; i--)
    {
        servicedOrder.push_back(left[i]);
        headPath.push_back(left[i]);
    }

    return buildResult(servicedOrder, headPath);
}