#ifndef DEVICES_SERIAL_H
#define DEVICES_SERIAL_H

#include <stdint.h>
#include "../threads/thread.h"

void serial_init(void);
void serial_putc (char);
void serial_flush (void);
void serial_notify (void);

void test_serial();
void setBufferPointer(int v);
static char buffer[100];
static int bufferPointer;
char* getBuffer();
//static struct semaphore shellSema;



#endif /* devices/serial.h */
