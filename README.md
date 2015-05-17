# CS631_Project04
CS631_final project

Task 1: void wait(tid_t):<br/>
  We maintain a wait list which contains elements that represent a thread waiting for another thread. When wait() is called, a new elem will be created and add to wait list, and current thread will be blocked. Each time a thread is killed, it'll walk the list and unblock those threads that waiting for it.
  In this way, a thread can wait untill another thread finish. 


Task 2: no busy wait timer_msleep():<br/>
In this task, we also maintained a new list called timeWaitList, which contains timer_wait_node, a struct that record start time, delay time and a semaphore of a thread. Each time a thread called msleep, a new node will be created and added to the timeWaitList. The semaphore, which connect the node and current thread, will be initialized as value=0. The, the thread will try to sema_down(), which will cause it block. In every thread tick, we walk through the timeWaitList, and check if there is any node that need to be waked up(startTime+delay<=currentTime). We wake these nodes up by sema_up(node->sema), which makes sema_down() in thread continue to run. In this way, we implements a none busy wait timer_msleep.

Task 3: UART:<br/>

Task 4: priority:<br/>
In this task, we simply modified thread_get_next_thread_to_run. Instead of poping the first element from ready list, We walk through the whole list to find the element with highest priority, and return this element as the next thread to run.s





						by Team01:
							Yuanyuan Zhang
							Kaijie Zhou
							Wentao Du
