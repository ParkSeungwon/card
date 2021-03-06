#include "combi.h"
#include <set>
#include<cmath>

Combination::Combination(int n, int r)
{
	if(n < 1 || r < 0) throw NRexception();
	ar = new int[r];
	this->n = n;
	this->r = r;
}

long Combination::factorial(int n) 
{
	if(n < 1) throw NRexception();
	return n == 1 ? n : n * factorial(n-1);
}

long nPr::count() const
{
	return factorial(n)/factorial(n-r);
}

long nCr::count() const
{
	return r == 0 ? 1 : nPr(n,r).count()/factorial(r);
}

long nTr::count() const
{
	return pow(n, r);
}

long nHr::count() const
{
	return nCr(n+r-1, r).count(); 
	//return factorial(n+r-1)/factorial(n-1)/factorial(r);
}

nCr::nCr(int n, int r) : Combination(n, r)
{
	if(r == 0) return;
	for(int i=0; i<r-1; i++) ar[i] = i + 1;
	ar[r-1] = r-1;
}
 
nTr::nTr(int n, int r) : Combination(n, r)
{
	for(int i=0; i<r-1; i++) ar[i] = 1;
	ar[r-1] = 0;
}

bool nCr::next()
{
	if(r == 0) return false;
	ar[r-1]++;
	int i = r-1;
	while(ar[i] == n-r+2+i) {
		if(--i == -1) return false;
		ar[i]++;
	}
	while(i < r-1) ar[i+1] = ar[i++] + 1;
	return true;
}

bool nTr::next()
{
	ar[r-1]++;
	int i = r-1;
	while(ar[i] == n+1) {
		ar[i] = 1;
		if(--i == -1) return false;
		ar[i]++;
	}
	return true;
}

bool nHr::next()
{
	ar[r-1]++;
	int i = r-1;
	while(ar[i] == n+1) {
		if(--i == -1) return false;
		ar[i]++;
	}
	while(i < r-1) ar[i+1] = ar[i++];
	return true;
}

nPr::nPr(int n, int r) : Combination(n, r)
{
	on = new bool[n+2];
	for(int i=0; i<n+2; i++) on[i] = false;
	for(int i=0; i<r; i++) {
		ar[i] = i + 1;
		on[i] = true;
	}
	ar[r-1] = 0;
}
	
void nPr::rewind()
{
	for(int i=0; i<r; i++) {
		ar[i] = i + 1;
		on[i] = true;
	}
	ar[r-1] = 0;
}

bool nPr::next()
{	
	inc_ar(r-1);

	int i = r-1;
	while(ar[i] == n+1) {
		if(--i == -1) return false;
		inc_ar(i);
	}
	while(i < r-1) {
		ar[++i] = 0;
		inc_ar(i);
	}
	return true;
}

void nPr::inc_ar(int i)
{
	on[ar[i]] = false;
	while(on[++ar[i]]);
	if(ar[i] != n+1) on[ar[i]] = true;
}

