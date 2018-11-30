#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char ** argv)
{
	int status;
	auto t1 = chrono::high_resolution_clock::now();
	for(int i=0;i<10000;i++)
	{
		for(int j=0;j<10000;j++)
		{
		}
	}
	auto t2 = chrono::high_resolution_clock::now();
	auto tch = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
	cout<<tch.count()<< "ms" <<endl;
		
}
