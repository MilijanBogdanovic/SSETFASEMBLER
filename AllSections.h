#ifndef ALLSECTIONS_H_
#define ALLSECTIONS_H_



#include <string>

using namespace std;

class ContentSection;


class AllSections {

public:

	struct SecElem {

		ContentSection* p;
		string SectionName;
		SecElem* next = 0;
	public:
		SecElem(ContentSection* cp, string cSectionName) {
			p = cp;
			SectionName = cSectionName;
		}

	};
	static SecElem* currentSection;
	SecElem *first, *last;
	AllSections() { first = last = 0; }
	~AllSections() {/*DOPISI DESTRUKTOR*/ }
	SecElem* AddNewSection(ContentSection* p1);
	void searchAllSections(string s);


};

#endif