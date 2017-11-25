#include <iostream>
#include "SharedObject.h"
#include <thread>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include "Semaphore.h"

Shared<int[3]> sharedObject("share", true);
bool running = true;
//creating semaphores
//protect access to data within the shared object
Semaphore protect("protect", 1, true);
//linker is used for communication between the Reader and Writer. Writter tells the reader okay I'm done, you can read now.
Semaphore DataModified("DataModified", 0, true);

void T1Function(int threadId, int delay)
{
	Shared<int[3]> shr("share");
	auto memory = shr.get();
	int numberCalled = 0; //number of times the thread is called.
	while(running)
	{
		protect.Wait();//getting access to protected area.
		*memory[0] = threadId;
		*memory[1] = numberCalled;
		*memory[2] = delay;
		numberCalled++;
		protect.Signal(); //leaving the critical area, data has been modified.
		DataModified.Signal();
		sleep(delay);

	}
	//displaying that these threads are ending:
	std::cout << "Ending thread: " << threadId << std::endl;

}

int main(void)
{
	std::cout << "I am a Writer" << std::endl;

	char decision;
	int threadId = 0;
	std::vector<std::thread> storer;
	//the maximum amount of time waiting out of all threads
	int maxDelay = 0;

	while(true)
	{
		std::cout<<"Would you like to create a writer thread? (y/n)"<< std::endl;
		std::cin >> decision;

		if(decision == 'n')
		{
			std::cout << "Will now end program. Waiting for threads to stop before ending program..." << std::endl;
			running = false;//all threads stop running.
			sleep(maxDelay + 1);//to ensure all threads close correctly, we wait for 1 sec longer then the max delay time of some thread waiting.
			break;
		}

		int delay;
		std::cout << "What is the delay time for the new thread. Please enter an Integer: " << std::endl;
		std::cin >> delay;
		if(delay > maxDelay)
		{
			maxDelay = delay;
		}
		std::thread t1(T1Function,threadId,delay);
		threadId++;
		//Detach allows the thread to have its own continuous execution.
		//The thread exits once it is done with it's function
		t1.detach();
	}
	std::cout<< "Program ending now..." << std::endl;
}
