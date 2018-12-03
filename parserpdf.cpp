#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;

int main(int argc, char ** argv)
{

	int status;
	pid_t pid= fork();
	if(pid>0)
	{
		wait(&status);
		ifstream fichierout(argv[argc-1]);
		ofstream fichierin("paperstest.txt");
	    if(fichierout && fichierin)
	    {
			int line=0;
	    	string s;
	    	bool abstract=false;

	    	while(getline(fichierout,s))
	    	{
	    		if(line==0)
	    		{
	    			fichierin<<"Titre: "<<s<<endl;
	    		}
	    		else if(line==1)
	    		{
	    			fichierin<<"Auteur: "<<s<<endl;
	    		}
	    		else
	    		{
		    		size_t abstend = s.find("Abstract");
		    		if(abstend!=string::npos && abstract==false)
		    		{
		    			abstract=true;
			    		fichierin<<"Resumer de l'article:"<<s.substr(0,abstend);
			    		while(getline(fichierout,s))
			    		{
			    			if(s.compare("")==0)
			    			{
			    				break;
			    			}
			    			else
			    			{
			    				fichierin<<" "<<s;
			    			}			    			
			    		}			    		
			    	}
	    		}
	    		line++;
	    	}
	    }
	    else
	    {
	    	  cerr <<"erreur d ouverture"<< endl;
	    }	      
	}
	else if(pid==0)
	{
		execvp(argv[1],&argv[1]);
	}		
}
