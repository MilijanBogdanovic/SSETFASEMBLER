#ifndef ASSEMBLY_H_
#define ASSEMBLY_H_

#include "Assembly.h"
#include <vector>
#include "EQU.h"
#include <math.h>
#include <iostream>
#include "ContentSection.h"
#include "SymTable.h"
#include "GlobalSymbolsTable.h"
#include "AllSections.h"
#include "InjectorFunctions.h"
using namespace std;


 GlobalSymbolsTable* gst=new GlobalSymbolsTable();
 SymTable* ST=new SymTable();
 int kraj = 0;

map<string, string> hm = createHASH_MAP();
map<string, char> equMap;
AllSections* allsec=new AllSections();
std::vector<EQU*> lista;

ifstream inFile;
ofstream outFile;

string ENDIANBUFF(string test) {
	for (int i = 0; i < 8; i++) {
		char temp;
		temp = test[i];
		test[i] = test[i + 8];
		test[i + 8] = temp;
	}
	string ret = test;
	return ret;
}

int Binary16toI(string binary) {
	int res = 0;
	for (int i = 0; i < 16; i++) {
		if (binary[i] == '1') {
			res += pow(2, 15 - i);
		}
	}

	return res;
}
int Binary8toInt(string binary) {
	int res = 0;
	for (int i = 0; i < 8; i++) {
		if (binary[i] == '1') {
			res += pow(2, 7 - i);
		}
	}

	return res;
}
string HEXUP(string s) {
	string temp;
	string res;
	string ret;
	int i = 0;
	int duzina = s.length();
	if (!empty(s)) {
		if (s.length() == 16) {
			temp = ENDIANBUFF(s);
			i = Binary16toI(temp);
		}
		else if (s.length() == 8) {
			i = Binary8toInt(s);
		}
		stringstream ss;
		
		if (duzina == 8 && i < 16) {
			ret += "0";
		}
		if ((duzina==16) && (i>255) && (i<4095)) {
			ret +="0";
		}
		if ((duzina == 16) && (i > 16) && (i < 256)) {
			ret += "00";
		}
		if ((duzina == 16) && (i < 16)) {
			ret += "000";
		}
		ss << hex << i;
		res = ss.str();
		ret += res;
		return ret;
	}
	return "";
}

int emptys(string s) {
	return (s == "");
}


int main(int argc,char *argv[]) {
	
	inFile.open("C:\\Users\\Milijan\\Desktop\\demo.txt");
	outFile.open("C:\\Users\\Milijan\\Desktop\\demo2.txt");
	if (!inFile) {
		cerr << "unable to open file";
		exit(2);
	}
	for (std::string line; kraj==0;) {
		std::getline(inFile, line);
		test_regex(line);
	}
	ST->PutUNDSection();
	ST->PutABSSection();
	BackPatchReloc();
	BackPatchCode();
	BackPatch32();
	BackPatchPCRel();
	EQUPROCESSING();
	backPatchEQUFinal();

	/*outFile.open("C:\\Users\\Milijan\\Desktop\\demo2.txt"); //RELOKATIVNO?
	outFile << ST;*/
	SymTableElem* temp = ST->first;
	outFile << "SYMBOL TABLE" << endl;
	//outFile << "simbol " << " "<<"l/g " << "sekcija prip "<< "ofset " << "rednibroj " << endl;
	while (temp) {

		outFile << temp->symbol << " " << temp->locality << " " << temp->sectionName<<" "<<temp->offset << " "<<
			temp->number <<" " << endl;
		temp = temp->next;
	}
	AllSections::SecElem* temp2 = allsec->first;
	outFile << endl;
	outFile << endl;
	while (temp2) {
		outFile << temp2->SectionName <<" SEKCIJA"<< endl;
		ContElem* telem= temp2->p->first;
		while (telem) {
			outFile << HEXUP(telem->content[0]) << " ";
			outFile << HEXUP(telem->content[1]) << " ";
			outFile << HEXUP(telem->content[2]) << " ";
			outFile << HEXUP(telem->content[3]) << " ";
			outFile <<HEXUP(telem->content[4]) << endl;
			telem = telem->next;
		}
		outFile << endl;
		outFile << endl;
		RelocElem* rtelem = temp2->p->relSecf;
		outFile << "RELOC SEKCIJA " <<temp2->SectionName<< endl;
		while (rtelem) {
			outFile << rtelem->offset << " "
				<< rtelem->type << " "
				<< rtelem->value << " " <<rtelem->locality<<" "<< rtelem->symbol<<endl;
			rtelem = rtelem->next;
		}

		temp2 = temp2->next;
		outFile << endl;
	}
	outFile.close();


	
	//outFile.close()?
	

}
#endif
	


