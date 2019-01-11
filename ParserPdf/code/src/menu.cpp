#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <dirent.h>
#include <sys/wait.h>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "menu.h"
#include "parser.h"

using namespace std;

vector<string> findPdfs()
{
    vector<string> pdfs;
    DIR * rep = opendir("./Papers_pdf");

    if (rep != NULL)
    {
        struct dirent * ent;
         
        while ((ent = readdir(rep)) != NULL)
        {
            pdfs.push_back(ent->d_name);
        }

        pdfs.erase(std::remove_if(pdfs.begin(), pdfs.end(),[](const string& fileName)
        {
           return fileName.compare(".")==0 || fileName.compare("..")==0 || fileName.substr(fileName.size()-4,fileName.size()-1).compare(".pdf")!=0 ;
        }), pdfs.end());

        closedir(rep);
    }
    return pdfs;
}
 
void showPdfsNamesOnTerminal(vector<string> pdfs, vector<string> pdfsToParse)
{
    if(!pdfs.empty())
    {
        for(int i = 0 ; i< pdfs.size();i++)
        {
            cout<< i << "|";
            for(int j = 0; j< pdfsToParse.size();j++)
            {
                if(pdfs[i].compare(pdfsToParse[j])==0)
                {
                    cout << "X";
                    break;
                }
            }
            cout << "|" << pdfs[i] << endl;
            cout <<"----------------------------- ---- --- --  --   - "<<endl;
        }
    }
    else
    {
        cout<<"Il n'y a aucun pdf dans le dossier Papers_Pdf"<<endl;
    } 
}

void addPdfToParse(int i_pdfName, vector<string> pdfs, vector<string> & pdfsToParse)
{
    if(i_pdfName<pdfs.size())
    {
        for(int i=0; i<pdfsToParse.size();i++)
        {
            if(pdfs[i_pdfName].compare(pdfsToParse[i])==0)
            {
                pdfsToParse.erase(pdfsToParse.begin()+i);
                return;
            }
        }
        pdfsToParse.push_back(pdfs[i_pdfName]);
    }
    else
    {
        cout << "La chaine de caractére entrer ne correspond a aucun fichier"<<endl;
    }
}

string convertToPointString(string fileName,string extension)
{
    string newFileName;
    newFileName=fileName.substr(0,fileName.size()-4);
    newFileName+=extension;
    return newFileName;
}

void launcht(vector<string> & pdfsToParse)
{
    int status;
    for(int i =0; i<pdfsToParse.size();i++)
    {
        int pidson= fork();
        if(pidson==0)//child
        {
            ofstream draftFile;
            draftFile.open("draft",ios::trunc);
            draftFile << "Error : File could not be opened"<<endl;
            draftFile.close();
            execlp("pdftotext","pdftotext",("Papers_pdf/"+pdfsToParse[i]).c_str(),"draft",NULL);
        }
        else
        {
             wait(&status);
             parser("draft","Papers_Result/"+convertToPointString(pdfsToParse[i],".txt"),"-t");
        }
    }
}

void launchx(vector<string> & pdfsToParse)
{
    int status;
    for(int i =0; i<pdfsToParse.size();i++)
    {
        int pidson= fork();
        if(pidson==0)//child
        {
            ofstream draftFile;
            draftFile.open("draft",ios::trunc);
            draftFile << "Error : File could not be opened"<<endl;
            draftFile.close();
            execlp("pdftotext","pdftotext",("Papers_pdf/"+pdfsToParse[i]).c_str(),"draft",NULL);
        }
        else
        {
             wait(&status);
             parser("draft","Papers_Result/"+convertToPointString(pdfsToParse[i],".xml"),"-x");
        }
    }
}

void resetPdfsToParse(vector<string> & pdfsToParse)
{
    pdfsToParse.clear();
}

void enterPdfs(vector<string> & pdfs, vector<string> & pdfsToParse, string & message)
{
    string in = "";
    cout<<"\n'help' permet de voir les commandes"<<endl<<"-:";
    cin>>in;
    cout<<endl;

    if(in.compare("launcht")==0)
    {
        launcht(pdfsToParse);
        resetPdfsToParse(pdfsToParse);
    }
    else if(in.compare("launchx")==0)
    {
        launchx(pdfsToParse);
        resetPdfsToParse(pdfsToParse);
    }
    else if (in.compare("launchxt")==0)
    {
        launcht(pdfsToParse);
        launchx(pdfsToParse);
        resetPdfsToParse(pdfsToParse);

    }
    else if (in.compare("refresh")==0)
    {
        pdfs = findPdfs();
    }
    else if (in.compare("help")==0)
    {
        message=string("Selectionnez ou Deselectionnez un fichier en entrant le numero qui lui est joint, un fichier selectionné apparait avec un X.\n")+
        "launcht : Parse les fichiers selectionnés au format .txt .\n"+
        "launchx : Parse les fichiers selectionnés au format .xml .\n"+
        "launchxt : Parse les fichiers selectionnez au format .txt et .xml .\n"+
        "refresh : Recharge les fichiers du fichier Papers_pdf.\n"+
        "end, quit, q: Permet de quitter le Parser\n";
    }
    else if(in.compare("end")==0 || in.compare("q")==0 || in.compare("quit")==0)
    {
        exit(0);
    }
    else
    {
        try 
        {               
            addPdfToParse(stoi(in),pdfs,pdfsToParse);
        }
        catch (std::logic_error & e)
        {}             
    }
}

void menu()
{   
    string message="";
    vector<string> pdfs;
    vector<string> pdfsToParse;
    pdfs = findPdfs();
    while(true)
    {
        system("clear");
        cout<<message<<endl;
        message="";
        showPdfsNamesOnTerminal(pdfs,pdfsToParse);
        enterPdfs(pdfs,pdfsToParse,message);
    }		
}