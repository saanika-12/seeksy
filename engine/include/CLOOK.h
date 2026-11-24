#ifndef CLOOK_H
#define CLOOK_H

#include "DiskScheduler.h"

class CLOOK : public DiskScheduler
{
public:

    CLOOK(int head, int size, const std::vector<int>& requestList);

    std::string getName() const override;

    SchedulingResult run() override;
};

#endif