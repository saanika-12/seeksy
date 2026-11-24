#include <iostream>
#include <vector>
#include <stdexcept>

#include "FCFS.h"
#include "SSTF.h"
#include "SCAN.h"
#include "CSCAN.h"
#include "LOOK.h"
#include "CLOOK.h"

using namespace std;

int main()
{
    int diskSize = 200;
    int headPosition = 50;

    vector<int> requests = {82, 170, 250, 140, 24, 16, 190};
try
{
    /* code */
}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}
try
{
    FCFS fcfs(headPosition, diskSize, requests);
    SSTF sstf(headPosition, diskSize, requests);
    SCAN scan(headPosition, diskSize, requests);
    CSCAN cscan(headPosition, diskSize, requests);
    LOOK look(headPosition, diskSize, requests);
    CLOOK clook(headPosition, diskSize, requests);

    cout << "SEEKY SCHEDULER TESTS" << endl;

    cout << "\nFCFS Movement: "
         << fcfs.run().totalHeadMovement << endl;

    cout << "SSTF Movement: "
         << sstf.run().totalHeadMovement << endl;

    cout << "SCAN Movement: "
         << scan.run().totalHeadMovement << endl;

    cout << "C-SCAN Movement: "
         << cscan.run().totalHeadMovement << endl;

    cout << "LOOK Movement: "
         << look.run().totalHeadMovement << endl;

    cout << "C-LOOK Movement: "
         << clook.run().totalHeadMovement << endl;
}
catch (const invalid_argument& error)
{
    cout << "\nValidation Successful!" << endl;
    cout << "Error: " << error.what() << endl;
}
    return 0;
}