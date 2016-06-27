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

float Hand::predict(array<Card, 52> dk, vector<Card> hn)
{
	if(hn.size() < 4) return 1;//3 is better
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
		cd.read_final();//here read_final
		m += cd.point();
		cd.clear();
		n++;
	}
	return float(m) / n;
}

float Hand::predict(array<Card, 52> dk)
{
	vector<Card> t;
	for(auto& a : cards) t.push_back(a);
	return predict(dk, t);
}

bool Hand::is_flush() const
{//cal with 3~7th cards
	if(n_ < 7) return false;
	for(int i=2; i<6; i++) if(cards[i].c != cards[i+1].c) return false;
	return true;
}

bool Hand::is_straight() 
{//calculate with front 5 cards of sorted_cds
	if(n_ < 7) return false;
	sort(cards.begin() + 2, cards.end());
	int serial = 0;
	for(int i=2; i<6; i++)if(cards[i].comp_n() == cards[i+1].comp_n() - 1) serial++; 
	return serial == 4 ? true : (serial == 3 && cards[3].n == 5 && cards[4].n == 1); 
}

int Hand::count_same()
{//one pair 1, two pair 2, triple 3, fullhouse 6, four card 7,  return else 0
	map<int, int> m;
	for(int i=2; i<n_; i++) m[cards[i].n]++;
	int k = 0, l = 0;
	for(auto& a : m) {
		if(a.second == 2) k++;
		else if(a.second == 3) l = 3;
		else if(a.second == 4) l = 7;
		if(a.second > 1) for(int i=2; i<n_; i++) 
			cards[i].n == a.first ? cards[i].family(true) : cards[i].family(false);
	}
	if(k+l == 4) {//for sorting fullhouse case 
		for(int i=2; i<7; i++) {
			if(count(cards.begin() + 2, cards.begin() + n_, cards[i].n) == 2) 
				cards[i].family(false);
		}
	}
	auto it = partition(cards.begin() + 2, cards.begin() + n_, [](const Card& a) {
			return a.family();});
	sort(cards.begin() + 2, it, greater<Card>());
	sort(it, cards.begin() + n_, greater<Card>());

	return k+l == 4 ? 6 : k+l;
}

int Hand::read_hand()
{//calculate facial point & sort hand in point order, also deals with just 5
	point_ = 0;
	if(is_flush()) point_ += 5;//2
	if(is_straight()) point_ += 4;//3
	if(point_ == 0) point_ += count_same();
	return point_;
}

int Hand::read_final()
{
	for(auto& a : cards) a.show(true);
	auto tmp1 = *this;
	auto tmp2 = *this;
	tmp1.read_hand();
	nCr ncr(7, 5);
	while(ncr.next()) {
		for(int i=0; i<5; i++) tmp2.cards[i+2] = cards[ncr[i]-1];
		tmp2.read_hand();
		if(tmp1 < tmp2) tmp1 = tmp2;
	}
	*this = tmp1;
	return point_;
}

int Hand::open_cards()
{
	read_final();
	for(auto& a : cards) cout << a << ' '; cout << '\t';
	show_family();
	return point();
}
bool Hand::operator<(const Hand& r) const
{
	if(point() == r.point()) {//compare card below v
		array<Card, 5> lt, rt;
		for(int i=2; i<n_; i++) {
			lt[i-2] = this->cards[i];
			rt[i-2] = r.cards[i];
		}
		if(lt == rt) return !(lt[0] > rt[0]);
		else return lt < rt;//compare array
	} else return point() < r.point();
}

void Hand::show(int player)
{
	if(player == 0) {
		cards[0].show(true);
		cards[1].show(true);
	}
	for(int i=0; i<n_; i++) cout << cards[i] << ' ';
	if(player == 0) {
		cards[0].show(false);
		cards[1].show(false);
	}
	read_hand();
	show_family();
}

void Hand::show_family() {
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

vector<Card> Hand::face() const
{
	vector<Card> r;
	for(int i=2; i<n_; i++) r.push_back(cards[i]);
	return r;
}

