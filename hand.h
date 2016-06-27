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
//	int drop_card(int n);
	void operator+=(Card r); 
	bool operator<(const Hand& r) const;
	static std::array<Card, 5> eval(std::array<Card, 5> cd);
	void clear(); 
	void show(int player_is_human);
	int point() const {return point_;}
	void point(int p) {point_ = p;}
	float predict(std::array<Card, 52> deck);
	float predict(std::array<Card, 52> deck, std::vector<Card> hn);
	std::vector<Card> face() const {return opened_cds;}
	int read_final();
	int read_hand();

protected:
	Hand(std::array<Card, 5> h);
	Hand(std::array<Card, 7> h);

	int point_;
	std::vector<Card> cards, opened_cds, sorted_cds;

private:
	
	bool is_straight() const;
	bool is_flush() const;
	int count_same();
};


