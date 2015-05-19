# CS631_Project04
CS631_final project

Task 1: void wait(tid_t):<br/>
  We maintain a wait list which contains elements that represent a thread waiting for another thread. When wait() is called, a new elem will be created and add to wait list, and current thread will be blocked. Each time a thread is killed, it'll walk the list and unblock those threads that waiting for it.
  In this way, a thread can wait untill another thread finish. 


Task 2: no busy wait timer_msleep():<br/>
In this task, we also maintained a new list called timeWaitList, which contains timer_wait_node, a struct that record start time, delay time and a semaphore of a thread. Each time a thread called msleep, a new node will be created and added to the timeWaitList. The semaphore, which connect the node and current thread, will be initialized as value=0. The, the thread will try to sema_down(), which will cause it block. In every thread tick, we walk through the timeWaitList, and check if there is any node that need to be waked up(startTime+delay<=currentTime). We wake these nodes up by sema_up(node->sema), which makes sema_down() in thread continue to run. In this way, we implements a none busy wait timer_msleep.

Task 3: UART:<br/>
UART is the most critical part. We cannot input without it. To enable user input, we just register a new interrupt--UART Interrupt and set uart_irq_handler as its handler. The IRQ num of this interrupt is 57 which is the IRQ for input. In its handler, we just use a buffer to store user input and print each char right after inputing. When enter key is pushed(ASCII:13), we'll add a '\0' on the tail of buffer and awake the thread that waitting for the input (shell thread in most cases). After that, the buffer will be initialed, and begin another loop. 

Task 4: Priority:<br/>
In this task, we simply modified thread_get_next_thread_to_run. Instead of poping the first element from ready list, We walk through the whole list to find the element with highest priority, and return this element as the next thread to run.s

Task 5: Shell:<br/>
In this task, we built a shell program, and let it run right after kernel boot. This shell is a while loop. It'll recieve user input until a '\n' is typed. Then, it'll compare the input string and decide which program to run.<br/>
The command information is follow:<br/>
1. ts [-a]: Show informations of running threads. <br/>
	[-a] option will let it show all existing threads.<br/>
2. run <func_name> [priority] [thread_name] : run function <func_name> as a thread, and wait until it complete.<br/>
	[priority] option: a integer that specify the priority of the created<br/> thread. Default: 31,<br/>
	[thread_name] option: a string that specify the name of the created thread. Default: No Name.<br/>
3. bg <func_name> [priority] [thread_name]: run function <func_name> as a new thread, and let it run in back ground.<br/>
	[priority] option: a integer that specify the priority of the created thread. Default: 31,<br/>
	[thread_name] option: a string that specify the name of the created thread. Default: No Name.<br/>
4. priority <-on/off> : A command that enable(-on) or disable(-off) the priority scheduling<br/>
5. help : Show help information.<br/>
<br/>------------Functions discription----------------<br/>
1. p_test: Start 4 different threads with different priorities (Task1 is the lowest priority, while Task4 is the highest).<br/>
	To test whether priority is functional, we just need to turn on the priority, run it, and then turn off, run it.<br/>
2. bg_test: Start two threads in the background. One is busy sleeping for 10s, the other is nonbusy sleeping for 10s. <br/>
	After running, use ts -a to check all threads. The busy sleeping should be in READY status, and the other should be blocked.<br/>
3. wait_test: Start two thread : Hello and CV. Hello start first, and just sleep for a while. CV start later than Hello and waiting for Hello to terminate.<br/>
	If wait is functional, CV need to terminate after Hello.<br/>  





						by Team01:
							Yuanyuan Zhang
							Kaijie Zhou
							Wentao Du
