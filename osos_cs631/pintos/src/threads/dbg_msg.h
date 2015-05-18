/*
 * dbg_msg.h
 *
 *  Created on: May 17, 2015
 *      Author: kaijiezhou
 */

#ifndef SRC_THREADS_DBG_MSG_H_
#define SRC_THREADS_DBG_MSG_H_
#define tsk1 1 //wait a thread
#define tsk2 2 //nobusy waiting timer
#define tsk3 4 //UART
#define tsk4 8 //priority
#define tsk5 16//shell
#define miscoff 32
#define allTsks tsk1+tsk2+tsk3+tsk4
#define output (32)

#endif /* SRC_THREADS_DBG_MSG_H_ */
