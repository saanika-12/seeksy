#ifndef SCAN_H
#define SCAN_H

#include "DiskScheduler.h"

class SCAN : public DiskScheduler
{
public:

    SCAN(int head, int size, const std::vector<int>& requestList);

    std::string getName() const override;

    SchedulingResult run() override;
};

#endif