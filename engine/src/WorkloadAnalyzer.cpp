#include "WorkloadAnalyzer.h"
#include <cstdlib>

// Analyse the disk workload
WorkloadAnalysis WorkloadAnalyzer::analyze(
    const std::vector<int>& requests,
    int headPosition,
    int diskSize)
{
    WorkloadAnalysis result;

    // Handle empty requests
    if (requests.empty())
    {
        result.workloadType = "No Requests";
        result.recommendedAlgorithm = "FCFS";
        result.explanation = "There are no requests to process.";

        return result;
    }

    int leftCount = 0;
    int rightCount = 0;
    int totalDistance = 0;

    // Examine every request
    for (int i = 0; i < requests.size(); i++)
    {
        if (requests[i] < headPosition)
            leftCount++;
        else
            rightCount++;

        totalDistance += abs(requests[i] - headPosition);
    }

    // Calculate average distance from the head
    double averageDistance =
        (double)totalDistance / requests.size();

    // Rule 1: Small workloads
    if (requests.size() <= 5)
    {
        result.workloadType = "Small Workload";
        result.recommendedAlgorithm = "FCFS";

        result.explanation =
            "FCFS is suitable for a small number of requests "
            "because it processes them in arrival order.";
    }

    // Rule 2: Requests exist on only one side
    else if (leftCount == 0 || rightCount == 0)
    {
        result.workloadType = "One-Sided Workload";
        result.recommendedAlgorithm = "LOOK";

        result.explanation =
            "LOOK is suitable because all requests are "
            "located on the same side of the current head.";
    }

    // Rule 3: Requests are close to the current head
    else if (averageDistance <= diskSize * 0.20)
    {
        result.workloadType = "Nearby Workload";
        result.recommendedAlgorithm = "SSTF";

        result.explanation =
            "SSTF is recommended because the requests "
            "are generally close to the current head position.";
    }

    // Rule 4: Requests are distributed on both sides
    else if (abs(leftCount - rightCount) <= 2)
    {
        result.workloadType = "Balanced Workload";
        result.recommendedAlgorithm = "C-SCAN";

        result.explanation =
            "C-SCAN is recommended because requests are "
            "distributed across both sides of the disk.";
    }

    // Rule 5: General distributed workload
    else
    {
        result.workloadType = "Uneven Workload";
        result.recommendedAlgorithm = "SSTF";

        result.explanation =
            "SSTF is recommended to prioritise the closest "
            "pending request.";
    }

    return result;
}