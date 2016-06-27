#pragma once
#include<string>
#include<array>
#include<vector>
#include<iostream>
#include<exception>

class Hand
{
public:
	Hand() {}
	void operator+=(Card r) {cards[n_++] = r;} 
	bool operator<(const Hand& r) const;
	void clear() {n_= 0;}
	void show(int zero_if_player_is_human);
	int point() const {return point_;}
	void point(int p) {point_ = p;}
	float predict(std::array<Card, 52> deck);
	float predict(std::array<Card, 52> deck, std::vector<Card> hn);
	std::vector<Card> face() const;
	int read_final();
	int read_hand();
	int open_cards();
	void show_family();

protected:
	int point_;
	int n_;
	std::array<Card, 7> cards;

private:
	bool is_straight() ;
	bool is_flush() const;
	int count_same();
};


