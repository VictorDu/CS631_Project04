
#include <debug.h>
#include <random.h>
#include <stdbool.h>
#include "stdio.h"
#include <stdint.h>
#include <string.h>

#include "../devices/gpio.h"
#include "../devices/framebuffer.h"
#include "../devices/serial.h"
#include "../devices/timer.h"
#include "../devices/video.h"
#include "interrupt.h"
#include "init.h"
#include "palloc.h"
#include "malloc.h"
#include "synch.h"
#include "thread.h"
#include "vaddr.h"
#include "dbg_msg.h"

/* -ul: Maximum number of pages to put into palloc's user pool. */
static size_t user_page_limit = SIZE_MAX;

/* Tasks for the Threads. */
static struct semaphore task_sem;

static void hello_test(void *);

struct wait_node {
  struct lock mutex;
  struct condition cv;
  bool done;
};

static struct wait_node sync_node;

static void t_wait(struct wait_node *wn);
static void t_exit(struct wait_node *wn);
static void cv_test(void *);

static tid_t waitTidForTest1;
/*
 * kernel.c
 *
 *  Created on: Oct 22, 2014
 *      Author: jcyescas
 */

static void test_swi_interrupt() {
  unsigned short green = 0x7E0;
  SetForeColour(green);
  generate_swi_interrupt(); // Function defined in interrupts.s
}

static void task1(void *aux){
  int i;
  for(i = 0;i<100;i++){
    printf("%d\n",1);
  }
}
static void task2(void *aux){
  int i;
  for(i = 0;i<100;i++){
    printf("%d\n",2);
  }
}
static void task3(void *aux){
  int i;
  for(i = 0;i<100;i++){
    printf("%d\n",3);
  }
}
static void task4(void *aux){
  int i;
  for(i = 0;i<100;i++){
    printf("%d\n",4);
  }
}
static void task5(void *aux){
  int i;
  for(i = 0;i<100;i++){
    printf("%d\n",5);
  }
}

/* Initializes the Operating System. The interruptions have to be disabled at entrance.
*
*  - Sets interruptions
*  - Sets the periodic timer
*  - Set the thread functionality
*/
void init() {

  /* Initializes ourselves as a thread so we can use locks,
    then enable console locking. */
  thread_init();

  /* Initializes the frame buffer and console. */
  framebuffer_init();
  serial_init();
  video_init();

  printf("\nOsOs Kernel Initializing");

  /* Initialize memory system. */
  palloc_init (user_page_limit);
  malloc_init ();

  /* Initializes the Interrupt System. */
  interrupts_init();
  timer_init();

  thread_start();
  timer_msleep(5000000);
  if(output&tsk2) printf("\ndbg: <init> -------back from first sleeping!\n");

  /* Starts preemptive thread scheduling by enabling interrupts. */
  //thread_start();

  printf("\nFinish booting.");

  /* Initialize the task_sem to coordinate the main thread with workers */

  sema_init(&task_sem, 0);

  thread_create("Hello Test", PRI_MAX, &hello_test, NULL);

/*  lock_init(&sync_node.mutex);
  cond_init(&sync_node.cv);
  sync_node.done = false;*/

  thread_create("CV Test", PRI_MAX, &cv_test, NULL);
  //sema_down(&task_sem);
  int count = 10;
  while(count > 0){
    timer_msleep(5000000);
    printf("\n main thread \n");
    count--;
  }
  thread_create("Task1", 41, &task1, NULL);
  thread_create("Task2", 42, &task2, NULL);
  thread_create("Task3", 43, &task3, NULL);
  thread_create("Task4", 44, &task4, NULL);
  thread_create("Task5", 45, &task5, NULL);

  //t_wait(&sync_node);

  printf("\nAll done.");
  thread_exit ();
}

static void hello_test(void *aux) {
  printf("\n-------------------------------\n");
  printf("<hello_test>Hello from OsOS\n");
  printf("\n");
  waitTidForTest1=thread_current()->tid;
  if(output&tsk2)  printf("dbg: <hello_test> I'm sleeping....\n");
  timer_msleep(5000000);
  if(output&tsk2)  printf("dbg: <hello_test> I'm awake........\n");
  printf("\n<hello_test> hello_test Done! should be the first----------------------\n");

  //sema_up(&task_sem);
}

static void t_wait(struct wait_node *wn)
{
  lock_acquire(&wn->mutex);
  while (!wn->done) {
    cond_wait(&wn->cv, &wn->mutex);
  }
  lock_release(&wn->mutex);
}

static void t_exit(struct wait_node *wn)
{
  lock_acquire(&wn->mutex);
  wn->done = true;
  cond_signal(&wn->cv,&wn->mutex);
  lock_release(&wn->mutex);
}

static void cv_test(void *aux) {
  printf("\n-----------------------------------\n");
  printf("\n<cv_test> Hello from CV Test\n");
  if(output&tsk1)printf("\ndbg: <cv_test> I'm waiting for a thread........");
  wait(waitTidForTest1);
  if(output&tsk1)printf("\ndbg: <cv_test> finish waiting!");
  printf("\n<cv_test> CV_test done!! should be the second----------------------\n");
  //t_exit(&sync_node);
}




