#include<map>
#include<random>
#include<algorithm>
#include<iostream>
#include<exception>
#include<string>
#include"card.h"
#include"combi.h"
using namespace std;

Hand::Hand(array<Card, 5> h) 
{ 
	hand = h;
	read_hand();
}

Hand::Hand(array<Card, 7> h) 
{
	int sz = cards.size();
	copy_n(h.begin(), 5, hand.begin());
	nCr c(7, 5);
	array<Card, 5> tmp;
	while(c.next()) {
		for(int i=0; i<5; i++) tmp[i] = h[c[i]-1];
		if(Hand(hand) < Hand(tmp)) hand = tmp;
	}
	read_hand();
}

float Hand::predict(array<Card, 52> dk)
{
	auto part = partition(dk.begin(), dk.end(), [](Card a) {return !a.show();});
	for(auto it = dk.begin(); it != part; it++) {
		if(find(cards.begin(), cards.end(), *it) != cards.end()) swap(*it, *--part);
	}
	int sz = part - dk.begin();
	nCr ncr(sz, 7 - cards.size());
	array<Card, 7> cd;
	long m = 0, n = 0;
	while(ncr.next()) {
		int i;
		for(i=0; i<ncr.size(); i++) cd[i] = dk[ncr[i] - 1];
		copy(cards.begin(), cards.end(), cd.begin() + i);
		Hand hd(cd);
		hd.show();
		m += hd.point();
		n++;
	}
	return float(m) / n;
}

bool Hand::is_flush() const
{
	for(int i=0; i<4; i++) if(hand[i].c != hand[i+1].c) return false;
	return true;
}

bool Hand::is_straight() const
{
	auto h = hand;
	sort(h.begin(), h.end());
	int serial = 0;
	for(int i=0; i<4; i++)	if(h[i].comp_n() == h[i+1].comp_n() - 1) serial++; 
	return serial == 4 ? true : (serial == 3 && h[3].n == 5 && h[4].n == 1); 
}

int Hand::count_same()
{//one pair 1, two pair 2, triple 3, fullhouse 6, four card 7,  return else 0
	map<int, int> m;
	for(auto& a : hand) m[a.n]++;
	int k = 0, l = 0;
	for(auto& a : m) {
		if(a.second == 2) k++;
		else if(a.second == 3) l = 3;
		else if(a.second == 4) l = 7;
		if(a.second > 1) for(auto& b : hand) if(b.n == a.first) b.family(true);
	}
	return k+l == 4 ? 6 : k+l;
}

int Hand::read_hand()
{
	point_ = count_same();
	if(is_flush()) point_ += 5;
	if(is_straight()) point_ += 4;
	if(point_ == 6) {//for sorting flush case 
		for(auto& a : hand) 
			if(count(hand.begin(), hand.end(), a.n) == 2) a.family(false);
	}
	auto it = partition(hand.begin(), hand.end(), [](const Card& a) {
			return a.family();});
	sort(hand.begin(), it, greater<Card>());
	sort(it, hand.end(), greater<Card>());
	return point_;
//	sort(hand.begin(), hand.end(), [](const Card& a, const Card& b) {
//			return (!a.family() && b.family()) || (a.family() && !b.family())
//				? a.family() && !b.family() : a > b; });
}

bool Hand::operator<(const Hand& r) const
{
	if(point() == r.point()) {
		if(hand == r.hand) return !(hand[0] > r.hand[0]);//compare card
		else return hand < r.hand;//compare array
	} else return point() < r.point();
}

void Hand::show()
{
	for(auto& a : hand) cout << a << ' ';
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


