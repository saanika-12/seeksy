#ifndef CSCAN_H
#define CSCAN_H

#include "DiskScheduler.h"

class CSCAN : public DiskScheduler
{
public:

    CSCAN(int head, int size, const std::vector<int>& requestList);

    std::string getName() const override;

    SchedulingResult run() override;
};

#endif