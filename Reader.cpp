#include <iostream>
#include "SharedObject.h"
using namespace std;

int main(void){
	Shared<int[3]> sharedObject("share"); //only four threads share the memory
	cout << "I am a reader" << endl;
	auto temp = sharedObject.get();
	//values from last post:
	//first time the shared object is called will be by thread 0
	//the initial values are arbritary other than lastId not being 0
	int lastId = 4, lastDelay = 4, lastnumberPosted = 4;
	while(true){
		//suspends the execution of other threads until 500000 microseconds, then check to see if object has changed
		usleep(500000);
		if(*temp[0] != lastId || *temp[1] != lastnumberPosted){
			cout << *temp[0] << " " << *temp[1] << " " << *temp[2] << endl;
			//only chooses entries that are new
			lastId = *temp[0];
			lastnumberPosted = *temp[1];
			lastDelay = *temp[2];
		}
	}
}
