#ifndef LOOK_H
#define LOOK_H

#include "DiskScheduler.h"

class LOOK : public DiskScheduler
{
public:

    LOOK(int head, int size, const std::vector<int>& requestList);

    std::string getName() const override;

    SchedulingResult run() override;
};

#endif