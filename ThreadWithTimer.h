
// SPDX-License-Identifier: GPL-2.0
/*
 * (C) Copyright 2019 Michael Dorin
 *
 */

#ifndef RODOS_KIPU2_THREADWITHTIMER_H
#define RODOS_KIPU2_THREADWITHTIMER_H

#include "stm32f4_discovery.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "Thread.h"
#include "InstantRodos.h"


class ThreadWithTimer:public Thread
{
    void run();
};


#endif //RODOS_KIPU2_THREADWITHTIMER_H
