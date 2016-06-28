#include<map>
#include<algorithm>
#include<iostream>
#include"hand.h"
#include"combi.h"
using namespace std;

Hand5::Hand5(array<Card, 5> cd)
{ 
	cards = cd;
	sort(cards.begin(), cards.end());
	if(is_straight()) point_ += 4;
	if(is_flush()) point_ += 5;
	if(point_ == 0) count_same();
}

bool Hand5::is_flush() const
{//cal with 3~7th cards
	for(int i=0; i<4; i++) if(cards[i].c != cards[i+1].c) return false;
	return true;
}

bool Hand5::is_straight() const
{//calculate with front 5 cards of sorted_cds
	int serial = 0;
	for(int i=0; i<4; i++) if(cards[i].comp_n() == cards[i+1].comp_n() - 1) serial++; 
	return serial == 4 ? true : (serial == 3 && cards[3].n == 5 && cards[4].n == 1); 
}

int Hand5::count_same()
{//one pair 1, two pair 2, triple 3, fullhouse 6, four card 7,  return else 0
	map<int, int> m;//num, frequency
	for(int i=0; i<n_; i++) m[cards[i].n]++;
	int k = 0, l = 0;
	for(auto& a : m) {
		if(a.second == 2) k++;
		else if(a.second == 3) l = 3;
		else if(a.second == 4) l = 7;
		if(a.second > 1) 
			for(int i=0; i<n_; i++) 
				if(cards[i].n == a.first) cards[i].family(true);
	}
	if(k+l == 4) {//for sorting fullhouse case 
		for(auto& a : cards)
			if(count(cards.begin(), cards.end(), a.n) == 2) a.family(false);
	}
	auto it = partition(cards.begin(), cards.end(), [](const Card& a) {
			return a.family();});
	sort(cards.begin(), it, greater<Card>());
	sort(it, cards.begin(), greater<Card>());
	return k+l == 4 ? 6 : k+l;
}

bool Hand5::operator<(const Hand5& r) const
{
	if(point() == r.point()) {//compare card below v
		if(cards == r.cards) return !(cards[0] > r.cards[0]);
		else return cards < r.cards;//compare array
	} else return point() < r.point();
}

void Hand5::show()
{
	for(int i=0; i<n_; i++) cout << cards[i] << ' ';
	switch(point()) {
		case 1: cout << "one pair"; break;
		case 2: cout << "two pair"; break;
		case 3: cout << "triple"; break;
		case 4: cout << "straight"; break;
		case 5: cout << "flush"; break;
		case 6: cout << "full house"; break;
		case 7: cout << "four card"; break;
		case 9: cout << "straight flush"; break;
	}
	cout << endl;
}

Hand7::Hand7(array<Card, 7> cd)// : Hand5(construct(cd))
{
	nCr ncr(7, 5);
	array<Card, 5> tmp, big;
	int sv[5];
	for(int i=0; i<5; i++) big[i] = cd[i];
	while(ncr.next()) {
		for(int i=0; i<5; i++) tmp[i] = cd[ncr[i]-1];
		if(Hand5(big) < Hand5(tmp)) {
			big = tmp;
			for(int i=0; i<5; i++) sv[i] = ncr[i] - 1;
		}
	}
	static_cast<Hand5&>(*this) = Hand5(big);//&
	for(int i=0, j=0, k=0; i<7; i++) {
		if(i == sv[j]) j++; 
		else rest[k++] = cd[i];
	}
}

void Hand7::show()
{
	cout << rest[0] << ' ' << rest[1] << " + ";
	Hand5::show();
}
