
#include <iostream>

#include "MathTests\Vector1Test.h"
#include "ThreadTests\TaskSchedulerTest.h"

int main
( 
	int argc, 
	const char* argv[] 
)
{
	Vector1Test::Run();
	TaskSchedulerTest::Run();
	std::cin.get();
	return 0;
}