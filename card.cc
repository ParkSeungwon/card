#include<map>
#include<random>
#include<algorithm>
#include<iostream>
#include<exception>
#include<string>
#include"card.h"
#include"combi.h"
using namespace std;


bool Card::operator>(const Card& r)const
{//In hand array compare, this should not be used before < compare.
	return comp_n()==r.comp_n() ? comp_c()>r.comp_c() : comp_n()>r.comp_n();
}

ostream& operator<<(ostream& l, const Card& r)
{
//	if(!r.show()) return l << Card::utf8chr(static_cast<int>(Unicode::CARDBACK));
	Unicode u;
	switch(r.c) {
		case 'C': u = Unicode::CLUB; break;
		case 'H': u = Unicode::HEART; break;
		case 'D': u = Unicode::DIAMOND; break;
		case 'S': u = Unicode::SPADE;
	}

	l << Card::utf8chr(static_cast<int>(u));
	l << ' ';
	//l << r.glyph[i];
	char ch;
	switch(r.n) {
		case 1: ch = 'A'; break;
		case 11: ch = 'J'; break;
		case 12: ch = 'Q'; break;
		case 13: ch = 'K'; break;
		default: ch = r.n;
	}
	ch > 1 && ch < 11 ? l << +ch : l << ch;
	return l;
}

string Card::utf8chr(int cp)
{
	char c[5]={ 0x00,0x00,0x00,0x00,0x00 };
	if     (cp<=0x7F) { c[0] = cp;  }
	else if(cp<=0x7FF) { c[0] = (cp>>6)+192; c[1] = (cp&63)+128; }
	else if(0xd800<=cp && cp<=0xdfff) {} //invalid block of utf8
	else if(cp<=0xFFFF) { c[0] = (cp>>12)+224; c[1]= ((cp>>6)&63)+128; c[2]=(cp&63)+128; }
	else if(cp<=0x10FFFF) { c[0] = (cp>>18)+240; c[1] = ((cp>>12)&63)+128; c[2] = ((cp>>6)&63)+128; c[3]=(cp&63)+128; }
	return string(c);
}

