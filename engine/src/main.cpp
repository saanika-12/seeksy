#include <iostream>
#include <vector>

#include "FCFS.h"
#include "SSTF.h"
#include "SCAN.h"
#include "CSCAN.h"
#include "LOOK.h"
#include "CLOOK.h"
#include "WorkloadAnalyzer.h"

using namespace std;

// Display scheduling results
void displayResult(SchedulingResult result)
{
    cout << "\nAlgorithm: " << result.algorithmName << endl;

    cout << "Service Order: ";

    for (int i = 0; i < result.servicedOrder.size(); i++)
    {
        cout << result.servicedOrder[i] << " ";
    }

    cout << "\nTotal Head Movement: "
         << result.totalHeadMovement << endl;

    cout << "Average Head Movement: "
         << result.averageHeadMovement << endl;

    cout << "-----------------------------" << endl;
}

int main()
{
    int diskSize = 200;
    int headPosition = 50;

    vector<int> requests = {82, 170, 43, 140, 24, 16, 190};

    cout << "================================" << endl;
    cout << "       SEEKSY DISK SCHEDULER    " << endl;
    cout << "================================" << endl;

    // Create algorithm objects
    FCFS fcfs(headPosition, diskSize, requests);
    SSTF sstf(headPosition, diskSize, requests);
    SCAN scan(headPosition, diskSize, requests);
    CSCAN cscan(headPosition, diskSize, requests);
    LOOK look(headPosition, diskSize, requests);
    CLOOK clook(headPosition, diskSize, requests);

    // Run all algorithms
    displayResult(fcfs.run());
    displayResult(sstf.run());
    displayResult(scan.run());
    displayResult(cscan.run());
    displayResult(look.run());
    displayResult(clook.run());

    // Analyse workload
    WorkloadAnalyzer analyzer;

    WorkloadAnalysis analysis =
        analyzer.analyze(requests, headPosition, diskSize);

    cout << "\n========== ADAPTIVE ANALYSIS ==========" << endl;

    cout << "Workload Type: "
         << analysis.workloadType << endl;

    cout << "Recommended Algorithm: "
         << analysis.recommendedAlgorithm << endl;

    cout << "Explanation: "
         << analysis.explanation << endl;

    cout << "======================================" << endl;

    return 0;
}