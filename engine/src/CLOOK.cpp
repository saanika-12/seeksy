#include "CLOOK.h"
#include <algorithm>

// Constructor
CLOOK::CLOOK(int head, int size,
             const std::vector<int>& requestList)
    : DiskScheduler(head, size, requestList)
{
}

// Return algorithm name
std::string CLOOK::getName() const
{
    return "C-LOOK";
}

// Execute C-LOOK scheduling
SchedulingResult CLOOK::run()
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

    // Service requests on the right side
    for (int i = 0; i < right.size(); i++)
    {
        servicedOrder.push_back(right[i]);
        headPath.push_back(right[i]);
    }

    // Jump to the lowest pending request
    if (!left.empty() && !right.empty())
    {
        headPath.push_back(left[0]);
    }

    // Service remaining requests
    for (int i = 0; i < left.size(); i++)
    {
        servicedOrder.push_back(left[i]);
        headPath.push_back(left[i]);
    }

    return buildResult(servicedOrder, headPath);
}