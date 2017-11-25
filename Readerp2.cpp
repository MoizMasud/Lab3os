#include <iostream>
#include "SharedObject.h"
#include "Semaphore.h"
int main(void)
{
	//get access to shared object
	Shared<int[3]> sharedObject("share");
	std::cout << "I am a reader" << std::endl;
	//Get the pointer to the shared objects value
	Semaphore linker("linker");
	auto me = sharedObject.get();
	while(true)
	{
		//Semaphore.wait() right here
		//Wait until there is something for the Reader to read
		linker.Wait();
		//Print the shared memory object
		std::cout << *me[0] << " " << *me[1] << " " << *me[2] << std::endl;
	}
}
