#include <iostream>
#include <vector>
#include <stdexcept>

#include "FCFS.h"
#include "SSTF.h"
#include "SCAN.h"
#include "CSCAN.h"
#include "LOOK.h"
#include "CLOOK.h"
#include "WorkloadAnalyzer.h"

using namespace std;

// Prints an integer array in JSON format.
void printArray(vector<int> values)
{
    cout << "[";

    for (int i = 0; i < values.size(); i++)
    {
        cout << values[i];

        if (i < values.size() - 1)
            cout << ",";
    }

    cout << "]";
}

// Prints one algorithm's result.
void printResult(SchedulingResult result)
{
    cout << "{";

    cout << "\"algorithm\":\"" << result.algorithmName << "\",";
    cout << "\"serviceOrder\":";
    printArray(result.servicedOrder);

    cout << ",\"headPath\":";
    printArray(result.headPath);

    cout << ",\"totalMovement\":"
         << result.totalHeadMovement;

    cout << ",\"averageMovement\":"
         << result.averageHeadMovement;

    cout << "}";
}

int main()
{
    try
    {
        int diskSize;
        int headPosition;
        int requestCount;

        // Receive input from Flask.
        cin >> diskSize >> headPosition >> requestCount;

        if (!cin || requestCount < 0)
            throw invalid_argument("Invalid input format.");

        vector<int> requests;

        for (int i = 0; i < requestCount; i++)
        {
            int track;
            cin >> track;

            if (!cin)
                throw invalid_argument("Missing track request.");

            requests.push_back(track);
        }

        // Create all six scheduling algorithms.
        FCFS fcfs(headPosition, diskSize, requests);
        SSTF sstf(headPosition, diskSize, requests);
        SCAN scan(headPosition, diskSize, requests);
        CSCAN cscan(headPosition, diskSize, requests);
        LOOK look(headPosition, diskSize, requests);
        CLOOK clook(headPosition, diskSize, requests);

        // Run the algorithms.
        SchedulingResult results[6] =
        {
            fcfs.run(),
            sstf.run(),
            scan.run(),
            cscan.run(),
            look.run(),
            clook.run()
        };

        // Analyse the workload.
        WorkloadAnalyzer analyzer;

        WorkloadAnalysis analysis =
            analyzer.analyze(requests, headPosition, diskSize);

        // Return JSON output.
        cout << "{";

        cout << "\"results\":[";

        for (int i = 0; i < 6; i++)
        {
            printResult(results[i]);

            if (i < 5)
                cout << ",";
        }

        cout << "],";

        cout << "\"analysis\":{";

        cout << "\"workloadType\":\""
             << analysis.workloadType << "\",";

        cout << "\"recommendedAlgorithm\":\""
             << analysis.recommendedAlgorithm << "\",";

        cout << "\"explanation\":\""
             << analysis.explanation << "\"";

        cout << "}";

        cout << "}";

    }
    catch (const invalid_argument& error)
    {
        cerr << error.what() << endl;
        return 1;
    }

    return 0;
}