#ifndef SSTF_H
#define SSTF_H

#include "DiskScheduler.h"

class SSTF : public DiskScheduler
{
public:

    SSTF(int head, int size, const std::vector<int>& requestList);

    std::string getName() const override;

    SchedulingResult run() override;
};

#endif