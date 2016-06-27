#include<map>
#include<random>
#include<algorithm>
#include<iostream>
#include<exception>
#include<string>
#include"card.h"
#include"combi.h"
#include"hand.h"
using namespace std;

Hand::Hand(array<Card, 5> h) 
{
	copy_n(h.begin(), 5, opened_cds.begin());
	read_hand();
}

Hand::Hand(array<Card, 7> h)
{
	array<Card, 5> tmp, rs;
	copy_n(h.begin(), 5, rs.begin());
	nCr ncr(7, 5);
	while(ncr.next()) {
		for(int i=0; i<5; i++) tmp[i] = h[ncr[i]-1];
		if(Hand(rs) < Hand(tmp)) rs = tmp;
	}
	*this = Hand(rs);	
}

float Hand::predict(array<Card, 52> dk)
{
	return predict(dk, cards);
}

void Hand::operator+=(Card cd) {
	cards.push_back(cd); 
	if(cd.show()) opened_cds.push_back(cd);
}

float Hand::predict(array<Card, 52> dk, vector<Card> hn)
{
	if(hn.size() < 3) return 1;
	if(hn.size() == 7)  return read_final();
	auto part = partition(dk.begin(), dk.end(), [](Card a) {return !a.show();});
	part = remove_if(dk.begin(), part, [&](Card a) {
			return find(cards.begin(), cards.end(), a) != cards.end();});
	int sz = part - dk.begin();
	nCr ncr(sz, 7 - hn.size());
	Hand cd;
	int m = 0, n = 0;
	while(ncr.next()) {
		int i;
		for(i=0; i<ncr.size(); i++) {
			dk[ncr[i]-1].show(true);
			cd += dk[ncr[i] - 1];
		}
		for(auto& a : hn) {
			a.show(true);
			cd += a;
		}
		cd.read_final();
		m += cd.point();
		cd.clear();
		n++;
	}
	return float(m) / n;
}

void Hand::clear()
{
	cards.clear();
	sorted_cds.clear();
	opened_cds.clear();
}

bool Hand::is_flush() const
{
	if(sorted_cds.size() < 5) return false;
	for(int i=0; i<4; i++) if(sorted_cds[i].c != sorted_cds[i+1].c) return false;
	return true;
}

bool Hand::is_straight() const
{
	if(sorted_cds.size() < 5) return false;
	auto h = sorted_cds;
	//sort(h.begin(), h.end());
	int serial = 0;
	for(int i=0; i<4; i++)	if(h[i].comp_n() == h[i+1].comp_n() - 1) serial++; 
	return serial == 4 ? true : (serial == 3 && h[3].n == 5 && h[4].n == 1); 
}

int Hand::count_same()
{//one pair 1, two pair 2, triple 3, fullhouse 6, four card 7,  return else 0
	map<int, int> m;
	for(auto& a : sorted_cds) m[a.n]++;
	int k = 0, l = 0;
	for(auto& a : m) {
		if(a.second == 2) k++;
		else if(a.second == 3) l = 3;
		else if(a.second == 4) l = 7;
		if(a.second > 1) for(auto& b : sorted_cds) 
			b.n == a.first ? b.family(true) : b.family(false);
	}
	if(k+l == 4) {//for sorting fullhouse case 
		for(auto& a : sorted_cds) 
			if(count(sorted_cds.begin(), sorted_cds.end(), a.n) == 2) a.family(false);
	}
	auto it = partition(sorted_cds.begin(), sorted_cds.end(), [](const Card& a) {
			return a.family();});
	sort(sorted_cds.begin(), it, greater<Card>());
	sort(it, sorted_cds.end(), greater<Card>());

	return k+l == 4 ? 6 : k+l;
}

int Hand::read_hand()
{//calculate facial point & sort hand in point order
	sorted_cds.clear();
	for(int i=0; i<5 && i<opened_cds.size(); i++) sorted_cds.push_back(opened_cds[i]);
	point_ = 0;
	sort(sorted_cds.begin(), sorted_cds.end());//1
	if(is_flush()) point_ += 5;//2
	if(is_straight()) point_ += 4;//3
	if(point_ == 0) point_ += count_same();
}

int Hand::read_final()
{
	for(auto& a : cards) a.show(true);
	opened_cds = cards;
	read_hand();
	Hand tmp;
	nCr ncr(7, 5);
	while(ncr.next()) {
		for(int i=0; i<5; i++) tmp += opened_cds[ncr[i]-1];
		tmp.read_hand();
		if(*this < tmp) *this = tmp;
		tmp.sorted_cds.clear();
	}
	//sorted_cds = opened_cds;
//	for(auto& a : cards) cout << a << ' ';
//	cout << endl;
//	for(auto& a : sorted_cds) cout << a << ' ';
//	cout << endl;
	return point_;
//	sort(hand.begin(), hand.end(), [](const Card& a, const Card& b) {
//			return (!a.family() && b.family()) || (a.family() && !b.family())
//				? a.family() && !b.family() : a > b; });
}

bool Hand::operator<(const Hand& r) const
{
	if(point() == r.point()) {//compare card below v
		if(sorted_cds == r.sorted_cds) return !(sorted_cds[0] > r.sorted_cds[0]);
		else return sorted_cds < r.sorted_cds;//compare array
	} else return point() < r.point();
}

void Hand::show(int player)
{
	if(player == 0) for(auto& a : cards) a.show(true);
	for(auto& a : cards) cout << a << ' ';
	read_hand();
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


