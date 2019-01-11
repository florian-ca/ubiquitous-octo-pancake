#ifndef menu_h
#define menu_h

#include <string>
#include <vector>

using namespace std;

	vector<string> findPdfs();
	void showPdfsNames(vector<string> pdfs, vector<string> pdfsToParse);
	void addPdfToParse(int i_pdfName, vector<string> pdfs, vector<string> & pdfsToParse);
	string convertToPointString(string fileName,string extension);
	void launcht(vector<string> & pdfsToParse);
	void launchx(vector<string> & pdfsToParse);
	void enterPdfs(vector<string> & pdfs, vector<string> & pdfsToParse, string & message);
	void resetPdfsToParse(vector<string> & pdfsToParse);
	void menu();

#endif