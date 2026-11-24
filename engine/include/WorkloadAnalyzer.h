#ifndef WORKLOAD_ANALYZER_H
#define WORKLOAD_ANALYZER_H

#include <string>
#include <vector>

struct WorkloadAnalysis
{
    std::string workloadType;
    std::string recommendedAlgorithm;
    std::string explanation;
};

class WorkloadAnalyzer
{
public:

    WorkloadAnalysis analyze(
        const std::vector<int>& requests,
        int headPosition,
        int diskSize
    );
};

#endif