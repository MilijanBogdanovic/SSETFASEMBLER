#include "AllSections.h"
#include "ContentSection.h"
#include "SymTable.h"
#include "GlobalSymbolsTable.h"
#include "AllSections.h"
#include "EQU.h"
#include "InjectorFunctions.h"


AllSections::SecElem* AllSections::AddNewSection(ContentSection *p1) {

	if (first == 0) {

		first = last =new SecElem(p1, p1->name);


	}
	else {
		last->next = new SecElem(p1, p1->name);
		last = last->next;

	}
	return last;
}
void AllSections::searchAllSections(string s) {

	SecElem* temp = first;
	while (temp) {

		if (temp->SectionName == s) {
			currentSection = temp;
			return;
		}
		temp = temp->next;
	}
	ContentSection* cs = new ContentSection(s);
	currentSection = AddNewSection(cs);

}


AllSections::SecElem* AllSections::currentSection = 0;