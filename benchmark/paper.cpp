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
	pid_t pid= fork();
	if(pid>0)
	{
		wait(&status);
		auto t2 = chrono::high_resolution_clock::now();
		auto tch = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
		cout<<tch.count()<< "ms" <<endl;
	}
	else if(pid==0)
	{
		execvp(argv[1],&argv[1]);
	}		
}
