#include<string>
#include<array>
#include<vector>
#include<iostream>
#include<exception>

enum class Unicode {
	SPADE = 0x2660, HEART = 0x2665, DIAMOND = 0x2666, CLUB = 0x2663, 
	CARDBACK = 0x1f0a0, JOKER = 0x2605
};

class Card
{
public:
	int n;
	char c;
	bool operator<(const Card& r) const { return comp_n() < r.comp_n(); }
	bool operator>(const Card& r) const;
	bool operator==(const Card& r) const { return comp_n() == r.comp_n(); }
	bool operator==(int r) const { return n == r; }
	char comp_c() const { return c == 'C' ? 'E' : c ; }
	int comp_n() const { return n == 1 ? 14 : n ; }
	friend std::ostream& operator<<(std::ostream& l, const Card& r);
	static std::string utf8chr(int cp);
	//getter, setter
	bool show() const {return show_;}
	void show(bool s) {show_ = s;}
	void family(bool f) {family_ = f;}
	bool family() const { return family_;}

protected:
	static constexpr const char* glyph[4]  {"♠ ", "♣ ", "♥ ", "♦ "};
	static constexpr const char g[4] {'C', 'H', 'D', 'S'};
	bool family_ = false;
	bool show_ = true;

private:
};

class Deck
{
public:
	Deck();
	std::array<Card, 52> deck;
	void shuffle_deck();
	Card distribute_card(bool open);
	Card operator[](int n) {return deck[n];}

protected:
	int top;
private:
	class No_card_exception : public std::exception {
		virtual const char* what() const throw() { return "No more card!!"; }
	};
	
};


