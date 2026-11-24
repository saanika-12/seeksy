#include "DiskScheduler.h"
#include <cstdlib>

// Constructor
DiskScheduler::DiskScheduler(int head, int size,
                             const std::vector<int>& requestList)
{
    headPosition = head;
    diskSize = size;
    requests = requestList;
}

// Calculate distance between two tracks
int DiskScheduler::distance(int trackA, int trackB) const
{
    return std::abs(trackA - trackB);
}

// Prepare the scheduling result
SchedulingResult DiskScheduler::buildResult(
    const std::vector<int>& servicedOrder,
    const std::vector<int>& headPath) const
{
    SchedulingResult result;

    result.algorithmName = getName();
    result.servicedOrder = servicedOrder;
    result.headPath = headPath;

    result.totalHeadMovement = 0;

    // Calculate total head movement
    for (int i = 1; i < headPath.size(); i++)
    {
        result.totalHeadMovement +=
            distance(headPath[i], headPath[i - 1]);
    }

    // Calculate average head movement
    if (!servicedOrder.empty())
    {
        result.averageHeadMovement =
            (double)result.totalHeadMovement / servicedOrder.size();
    }
    else
    {
        result.averageHeadMovement = 0;
    }

    return result;
}