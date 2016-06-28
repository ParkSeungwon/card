#pragma once
#include"card.h"

class Hand5
{
public:
	Hand5(std::array<Card, 5> cards);
	
	bool operator<(const Hand5& r) const;
	void show();
	
	int point() const {return point_;}
	void point(int p) {point_ = p;}

protected:
	Hand5() {}
	int point_, n_ = 5;
	std::array<Card, 5> cards;

	bool is_straight() const;
	bool is_flush() const;
	int count_same();

private:
};

class Hand7 : public Hand5
{
public:
	Hand7(std::array<Card, 7> cards);
	void show();

protected:
	Hand7() {}
	Card rest[2];
};


