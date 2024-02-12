#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	this->NrColumns = nrCols;
	this->NrLines = nrLines;

	row = new int[0];
	column = new int[nrCols + 1];
	value = new TElem[0];

	//columns vector
	for (int i = 0;i <= n;i++)
		column[i] = 0;

	//initial length
	len = 0;
}

int Matrix::check_poz(int i, int j)const
{
	for (int k = column[j]; k < column[j + 1]; k++) {
		if (row[k] == i)
			return k;
	}
	return -1;
}

void Matrix::valid_poz(int i, int j) const {
	if (i < 0 || i >= n)
		throw exception();
	if (j < 0 || j >= m)
		throw exception();
}


int Matrix::nrLines() const {
	return NrLines;
}
//Tetha(1)


int Matrix::nrColumns() const {
	return NrColumns;
}
//Tetha(1)


TElem Matrix::element(int i, int j) const {
	int poz;
	valid_poz(i, j);
	poz = check_poz(i, j);
	if (poz != -1)
		return value[poz];
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation
	return NULL_TELEM;
}


