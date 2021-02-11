#include "SymTable.h"
#include "ContentSection.h"
#include "GlobalSymbolsTable.h"
#include "AllSections.h"
#include "EQU.h"
#include "InjectorFunctions.h"

SymTable::SymTable(){

}


int SymTable::PutSecSymbol(string pch) {
	if (first == 0) { first = last = new SymTableElem(pch, -1,AllSections::currentSection->SectionName); }
	else {
		last->next = new SymTableElem(pch, -1,AllSections::currentSection->SectionName);
		last = last->next;
	}

	return last->number;
}
int SymTable::PutUNDSymbol(string pch) {
	if (first == 0) { first = last = new SymTableElem(pch, 0,"UND"); }
	else {
		last->next = new SymTableElem(pch, 0, "UND");
		last = last->next;
	}

	return last->number;

}
int SymTable::PutUNDSection() {
	if (first == 0) { first = last = new SymTableElem("UND", 0, "UND"); }
	else {
		last->next = new SymTableElem("UND", 0, "UND");
		last = last->next;
	}

	return last->number;
}
SymTable::~SymTable()
{


}


int SymTable::PutABSSection() {
	if (first == 0) { first = last = new SymTableElem("ABS", 0, "ABS"); }
	else {
		last->next = new SymTableElem("ABS", 0, "ABS");
		last = last->next;
	}

	return last->number;
}
void SymTable::UpdateSymbol(string line) {
	SymTableElem* temp = first;
	while (temp) {

		if (temp->symbol==line) {
			temp->offset = AllSections::currentSection->p->LC;
			temp->sectionName = AllSections::currentSection->SectionName;
			temp->razresen = true;
			return;
		}
		temp = temp->next;
	}

	if (first == 0) { first = last = new SymTableElem(line, AllSections::currentSection->p->LC,AllSections::currentSection->SectionName ); }
	else {
		last->next = new SymTableElem(line, AllSections::currentSection->p->LC,AllSections::currentSection->SectionName);
		last = last->next;
		last->razresen = true;
	}

}


void SymTable::PutSymbol(string line,ContElem* p,int i) {
	
	if (first == 0) { first = last = new SymTableElem(line, -1,""); }
	else {
		last->next = new SymTableElem(line,-1,"");
		last = last->next;
	}
	last->addFlink(p, i);
	ContentSection* pom = AllSections::currentSection->p;
	

	if (pom->relSecf == 0) {
		pom->relSecf = pom->relSecl = new
			RelocElem(pom->LC, p->pcRel == 1 ? "R_386_PC32" : "R_386_32", pom->SymPosition, line,p,i,AllSections::currentSection->SectionName);


	}
	else {
		pom->relSecl->next = new
			RelocElem(pom->LC, p->pcRel == 1 ? "R_386_PC32" : "R_386_32", pom->SymPosition, line,p,i,AllSections::currentSection->SectionName);
		pom->relSecl = pom->relSecl->next;
		
	}

	
}


string SymTable::SearchAndMark(string s, ContElem* p,int i) {
	stringstream sstream;
	string val;
	SymTableElem* temp = first;
	
	while (temp) {

		if (temp->symbol == s) {
			if (temp->razresen){
				int result = temp->offset;

				sstream << bitset<16>(result);
				val = sstream.str();
				char *ret = &val[0];
				addReloc(s, p, i);
				return ret;
			}
			else {
				temp->addFlink(p, i);
				sstream << bitset<16>(0);
				val = sstream.str();
				char *ret = &val[0];
				addReloc(s, p, i);
				return ret;

			}

		}
		temp = temp->next;
	}
	PutSymbol(s, p, i);
	sstream << bitset<16>(0);
	val = sstream.str();
	char *ret = &val[0];
	return ret;
	

}


