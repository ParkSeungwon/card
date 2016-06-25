#pragma once
#include <exception>

class NRexception : public std::exception
{
public:
	virtual const char* what() const throw() {
		return "Combination : N, R should be positive integer!!";
	}
};

class Combination
{
public:
	Combination(int n, int r);
	virtual	~Combination() { delete [] ar;}
	int& operator[](unsigned i) {return ar[i];}
	bool next();
	int size() {return r;}
	static long factorial(int n);

protected:
	int* ar;
	int n, r;
};

class nCr : public Combination
{
public: 
	nCr(int n, int r);
	bool next();
	long count() const;
};

class nTr : public Combination
{
public:
	nTr(int n, int r);
	bool next();
	long count() const;
};

class nHr : public nTr
{
public:
	nHr(int n, int r) : nTr(n,r) {}
	bool next();
	long count() const;
};

class nPr : public Combination
{
public:
	nPr(int n, int r);
	virtual ~nPr() {delete [] on;}
	bool next();
	void rewind();
	long count() const;

private:
	bool* on;
	void inc_ar(int i);
};
