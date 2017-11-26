#include <iostream>
#include "SharedObject.h"
#include "Semaphore.h"
int main(void)
{
	
	Shared<int[3]> sharedObject("share"); //get access to the shared resources 
	std::cout << "I am a reader" << std::endl;
	Semaphore dataReady("dataReady");
	auto memory = sharedObject.get();//pointer to the object
	while(true)
	{
	
		//Wait until there is something for the Reader to read
		linker.Wait();
		std::cout << *memory[0] << " " << *memory[1] << " " << *memory[2] << std::endl;
	}
}
