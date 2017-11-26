#include <iostream>
#include "SharedObject.h"
#include <thread>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
using namespace std;

Shared<int[3]> sharedObject("share", true); //set to true meaning this is the owner.
bool running = true;

void threadFunction(int threadId, int delay){
	Shared<int[3]> shr("share");
	auto temp = shr.get();//get access to that shared memory
	int numberCalled = 0;
	while(running){
		//write to it
		*temp[0] = threadId;
		*temp[1] = numberCalled;
		*temp[2] = delay;
		numberCalled++;
		sleep(delay);
	}
	//displaying that these threads are ending:
	cout << "Ending thread: " << threadId << endl;
}

int main(void) {
	cout << "I am a Writer" << endl;
	char choice;
	int threadId = 0;
	//the maximum amount of time waiting out of all threads
	int maxDelay = 0;

	while (true) {
		cout << "Would you like to create a writer thread? (y/n)" << endl;
		cin >> choice;

		if (choice == 'n') {
			cout << "Will now end program once all threads have ended." << endl;
			running = false;
			//wait for longer than needed to ensure all threads close
			sleep(maxDelay + 1);
			break;
		}

		int delay;
		cout << "Enter delay time for the new thread. Please enter an Integer: " << endl;
		cin >> delay;
		if (delay > maxDelay) {

			maxDelay = delay;
		}
		thread t1(threadFunction, threadId, delay);
		threadId++;
		t1.detach();
	}
	cout << "Program ending now" << endl;
}