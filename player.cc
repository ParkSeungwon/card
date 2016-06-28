#include<algorithm>
#include"combi.h"
#include"player.h"
using namespace std;

void Player::operator+=(Card a)
{
	if(!a.show()) rest[m_++] = a;
	else cards[n_++] = a;
	point_ = 0;
	if(n_ == 5) {
		sort(cards.begin(), cards.end()); 
		if(is_straight()) point_ += 4;
		if(is_flush()) point_ += 5;
	}
	if(point_ == 0 && n_ > 1) point_ = count_same();
}
	
float Player::predict(const Deck& dk, const Player& other) const
{
	auto hn = other.face();
	return predict(dk.deck, hn);
}

float Player::predict(array<Card, 52> dk, vector<Card> hn) const
{
	if(hn.size() < 4) return 1;//3 is better
	array<Card, 7> cd;
	if(hn.size() == 7)  {
		for(int i=0; i<7; i++) cd[i] = hn[i];
		return Hand7(cd).point();
	}
	auto part = partition(dk.begin(), dk.end(), [](Card a) {return !a.show();});
	part = remove_if(dk.begin(), part, [&](Card a) {
			return find(cards.begin(), cards.end(), a) != cards.end();});
	int sz = part - dk.begin();
	nCr ncr(sz, 7 - hn.size());
	int m = 0, n = 0;
	while(ncr.next()) {
		int i;
		for(i=0; i<ncr.size(); i++) cd[i] = dk[ncr[i] - 1];
		for(int j=0; i<7; i++, j++) cd[i] = hn[j];
		m += Hand7(cd).point();
		n++;
	}
	return float(m) / n;
}

float Player::predict(const Deck& dk) const
{
	vector<Card> t;
	for(int i=0; i<n_; i++) t.push_back(cards[i]);
	t.push_back(rest[0]);
	t.push_back(rest[1]);
	return predict(dk.deck, t);
}

vector<Card> Player::face() const
{
	vector<Card> r;
	for(int i=0; i<n_; i++) r.push_back(cards[i]);
	return r;
}

void Player::show()
{
	cout << Card::utf8chr(0x1f0a0);
	cout << "  ";
	cout << Card::utf8chr(0x1f0a0);
	cout << "  ";
	Hand5::show();
}

