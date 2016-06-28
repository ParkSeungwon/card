#pragma once
#include"hand.h"

enum Status { DIE, CALL, BET, BROKE, NOT_IN};

class Player : public Hand7
{
public:
	void operator+=(Card r); 
	void new_game() { m_=0; n_=0;}
	void show();
	std::vector<Card> face() const;
	float predict(std::array<Card, 52> deck) const;
	float predict(std::array<Card, 52> deck, std::vector<Card> hn) const;

	Status status() {return status_;}
	void status(Status s) {status_ = s;}

protected:
	Status status_;
	int n_ = 0, m_ = 0;
	int money_ = 2000, bet_money_ = 10;
};
