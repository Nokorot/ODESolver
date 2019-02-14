
#include "pch.h"
#include "ErrorCalc.h"
#include <cmath>

rowvec lineIterp(const rowvec& x, const rowvec& v, const rowvec& xq)
{
	if (v.n_elem != x.n_elem)
	{
		std::cerr << "Length of x and v differ." << endl;
		return NULL;
	}
	rowvec res(xq.n_elem);

	uint i = 0;
	for (uint j = 0; j < xq.n_elem; ++j)
	{
		while (i < x.n_elem-1 && x(i) < xq(j))
			++i;
		if (x(i) <= xq(j))
			res(j) = v(i);
		else
			res(j) = (  v(i-1)*(x(i)-xq(j)) + v(i)*(xq(j)-x(i-1))  )
					/ (x(i)-x(i-1));
	}
	return res;
}

mat lineIterp(const rowvec& x, const mat& v, const rowvec& qx)
{
	mat res(v.n_rows, qx.n_elem);
	for (uint i = 0; i < v.n_rows; ++i)
	{
		res.row(i) = lineIterp(x, (rowvec) v.row(i), qx);
	}
	return res;
}

double max(rowvec vec)
{
	double m = vec(0);
	for (uint i=0; i < vec.n_elem; ++i)
		if (m < vec(i))
			m = vec(i);
	return m;
}

double ErrorCalc(rowvec Tref, mat Yref, rowvec Tq, mat Yq)
{
	if (Yref.n_rows != Yq.n_rows)
	{
		std::cerr << "Number of rows in Yref and Yq differ." << endl;
		return 0;
	}

	mat EA = Yq - lineIterp(Tref, Yref, Tq);

	double m = 0, s;
	for (uint j = 0; j < EA.n_cols; ++j)
	{
		s = 0;
		for (uint i = 0; i < EA.n_rows; ++i)
		{
			s += EA(i, j) * EA(i, j);
		}
		if (s > m)
			m = s;
	}

	return std::sqrt(m);
}
