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



void parserpdf(string source,string destination,string optionString)
{
	bool option; // if true = text ; if false = xml



	if (optionString.compare("-t")==0)
	{
		option=true;

	}
	else if (optionString.compare("-x")==0)
	{
		option=false;
	}

	
	ofstream fichierin(destination,ios::trunc);
	
	ifstream fichierout(source);
		

	    if(fichierout && fichierin)
	    {
			int line=0;
	    	string s;
	    	bool abstract=false;
	    	if (option) fichierin<<"preamble:"<< source <<endl; // ajout du nom du fichier original
	    	else fichierin<<"<Article>"<<endl<<"<preamble>"<< source <<"</preamble>"<<endl;
	    	while(getline(fichierout,s))
	    	{
	    		cout <<  "getline"<<endl;
	    		std::locale loc("C");
	    		if(line==0) // 1er ligne = ligne du titre
	    		{

	    			if (option) fichierin<<"Titre: "<<s;
	    			else fichierin<<"<Titre>"<<s<<"</Titre>";
	    		}
	    		// si les deux premiers mot commencent par une majuscule i.e ligne de l'auteur
	    		if(line==1 && !std::islower(s.at(0),loc) && !std::islower(s.at(s.find(" ",0)+1),loc) ) 
	    		{

	    			int a=s.find(" ",0);
	    			cout << a<<endl;

	    			if (option) fichierin<<endl<<"Auteur: "<<s<<endl;
	    			else fichierin<<endl<<"<Auteur>"<<s<<"</Auteur>"<<endl;
	    		}

	    		// si l'un des deux premier mot de la ligne commence pas par une majuscule i.e pas la ligne de l'auteur mais 2nde ligne du titre
	    		else if (line==1 && (std::islower(s.at(0),loc) || std::islower(s.at(s.find(" ",0)+1),loc)) ) 
	    		{

	    			if (option) fichierin<<" "<<s<<endl;
	    			else fichierin<<"<Titre2>"<<s<<"</Titre2>"<<endl;
	    			string S="";
	    			while(S=="")  // récupére la porchaine ligne non vide i.e l'auteur
	    			{
	    				getline(fichierout,S);	 
	    			}
	    			
	    			if (option) fichierin<<"Auteur: "<<S<<endl;	
	    			else  fichierin<<endl<<"<Auteur>"<<S<<"</Auteur>"<<endl;		
	    		}

	    		// sinon on cherche l'abstract ou la bibliography / references
	    		else 
	    		{
		    		size_t abstend = s.find("Abstract");
		    		if(abstend!=string::npos && abstract==false)
		    		{
		    			abstract=true;
		    			if (option) fichierin<<"Resumé de l'article:"<<s.substr(0,abstend);
			    		else fichierin<<"<Abstract>"<<s.substr(0,abstend);
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
			    		if (!option) fichierin<<"</Abstract>"<<endl;	    		
			    	}
			    	
			    	
			    	size_t introend =s.find("Introduction");
			    	if (introend!=string::npos)
			    	{
				    	if (!option) fichierin << "<Introduction>"<<s.substr(0,introend);
				    	string stockPreviousLine="Introduction",ligneIntro;
				    	while(getline(fichierout,ligneIntro))
				    	{
				    		
				    		cout << "ici"<<stockPreviousLine.back()<<"." <<endl;
				    		if ( ligneIntro.compare("")==0 && (stockPreviousLine.back()=='.' || stockPreviousLine.size()<2) ) // si la ligne est vide et que la ligne précédente se termine par un point
				    		{
				    			cout<<"la"<<endl;
				    			break;
				    		}
				    		else 
				    		{
				    			fichierin<<ligneIntro<<endl;
				    			stockPreviousLine=ligneIntro;
				    		}
				    	}
				    	if (!option) fichierin<<"</Introduction>"<<endl;
					}

			    	size_t refend = s.find("References");
			    	if (refend!=string::npos)
			    	{
			    		string S;
			    		if (option) fichierin<<endl<<"Bibliography:"<<endl<<s.substr(0,refend);
			    		else fichierin<<endl<<"<Bibliography>"<<endl<<s.substr(0,refend);

			    		while(getline(fichierout,S))
			    		{

			    			if (S.size()>=2 ) fichierin <<" "<<S<<endl;
			    		}
			    		if(!option) fichierin<<"</Bibliography>";
			    	}

	    		}
	    		line++;
	    	}
	    	if (!option) fichierin<<endl<<"</Article>"<<endl;
	   
	    }
	    else
	    {
	    	  cerr <<"erreur d ouverture"<< endl;
	    }	      
}


int main()
{
	parserpdf("alex.txt","alex.xml","-x");
}
