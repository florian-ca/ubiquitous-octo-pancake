#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <locale>

using namespace std;

int main(int argc, char ** argv)
{

	int status;
	pid_t pid= fork();
	if(pid>0)
	{
		wait(&status);
		ifstream fichierout(argv[argc-1]);
		ofstream fichierin("fileParsed.txt");
	    if(fichierout && fichierin)
	    {
			int line=0;
	    	string s;
	    	bool abstract=false;
	    	fichierin<<"preamble:"<<argv[argc-2]<<endl; // ajout du nom du fichier original
	    	while(getline(fichierout,s))
	    	{

	    		std::locale loc("C");
	    		if(line==0) // 1er ligne = ligne du titre
	    		{

	    			fichierin<<"Titre: "<<s;
	    		}
	    		// si les deux premiers mot commencent par une majuscule i.e ligne de l'auteur
	    		if(line==1 && !std::islower(s.at(0),loc) && !std::islower(s.at(s.find(" ",0)+1),loc) ) 
	    		{

	    			int a=s.find(" ",0);
	    			cout << a<<endl;

	    			fichierin<<endl<<"Auteur: "<<s<<endl;
	    		}

	    		// si l'un des deux premier mot de la ligne commence pas par une majuscule i.e pas la ligne de l'auteur mais 2nde ligne du titre
	    		
	    		else if (line==1 && (std::islower(s.at(0),loc) || std::islower(s.at(s.find(" ",0)+1),loc)) ) 
	    		{

	    			fichierin<<" "<<s<<endl;
	    			string S="";
	    			while(S=="")  // récupére la porchaine ligne non vide i.e l'auteur
	    			{
	    				getline(fichierout,S);	 
	    			}
	    			cout << S<<endl;
	    			fichierin<<"Auteur: "<<S<<endl;
	    		
	    		}

	    		// sinon on cherche l'abstract ou la bibliography / references
	    		else 
	    		{


		    		size_t abstend = s.find("Abstract");
		    		if(abstend!=string::npos && abstract==false)
		    		{
		    			abstract=true;
			    		fichierin<<"Resumé de l'article:"<<s.substr(0,abstend);
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

			    	cout << "ICI ???"<<endl;
			    	size_t refend = s.find("References");
			    	if (refend!=string::npos)
			    	{
			    		string S;
			    		fichierin<<endl<<"Bibliography:"<<endl<<s.substr(0,refend);
			    		while(getline(fichierout,S))
			    		{
			    			fichierin <<" "<<S<<endl;
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