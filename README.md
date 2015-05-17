# CS631_Project04
CS631_final project

Task 1: void wait(tid_t):
  We maintain a wait list which contains elements that represent a thread waiting for another thread. When wait() is called, a new elem will be created and add to wait list, and current thread will be blocked. Each time a thread is killed, it'll walk the list and unblock those threads that waiting for it.
  In this way, a thread can wait untill another thread finish. 


Task 2: no busy wait timer_msleep():





						by Team01:
							Yuanyuan Zhang
							Kaijie Zhou
							Wentao Du
