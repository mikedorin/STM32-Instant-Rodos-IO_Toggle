// SPDX-License-Identifier: GPL-2.0
/*
 * (C) Copyright 2019 Michael Dorin
 *
 */

#include "ThreadWithTimer.h"
extern void doBlinks();

void ThreadWithTimer::run() {
    int counter = 1;

    suspendUntilNextBeat();
    setPeriodicBeat(3 * SECONDS, 20 * SECONDS);
    suspendUntilNextBeat();
    while(true)
    {
        doBlinks();
        suspendUntilNextBeat();
    }
}

