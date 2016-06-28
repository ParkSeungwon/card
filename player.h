#pragma once
#include"hand.h"

enum Status { DIE, CALL, BET, BROKE, NOT_IN};

class Player : public Hand7
{
public:
	Player() {n_ = 0;}//player can have various number of cards. Base was always 5.
	void operator+=(Card r); 
	void new_game() { m_=0; n_=0;}
	void show() const;
	int open_cards();
	std::pair<float, int> predict(const Deck& deck) const;
	std::pair<float, int> predict(const Deck& deck, const Player& other) const;

protected:
	int m_ = 0;

private:
	std::pair<float, int> predict(std::array<Card, 52> deck, std::vector<Card> hn) const;
	std::vector<Card> face() const;
};

class Gambler : public Player
{
public:
	Status status() {return status_;}
	void status(Status s) {status_ = s;}

protected:
	int money_ = 2000, bet_money_ = 10;
	Status status_;
};
