#ifndef FCFS_H
#define FCFS_H

#include "DiskScheduler.h"

class FCFS : public DiskScheduler
{
public:

    FCFS(int head, int size, const std::vector<int>& requestList);

    std::string getName() const override;

    SchedulingResult run() override;
};

#endif