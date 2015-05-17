/*
 * timer.h
 *
 *  Created on: Nov 8, 2014
 *      Author: jcyescas
 */

#ifndef DEVICES_TIMER_H_
#define DEVICES_TIMER_H_
#include "../threads/thread.h"
void timer_init(void);

int timer_get_timestamp();

void timer_msleep(int milliseconds);

#endif /* TIMER_H_ */
