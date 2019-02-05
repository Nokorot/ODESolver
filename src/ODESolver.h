/*
 * ODESolver.h
 *
 *  Created on: 5 Feb 2019
 *      Author: noko
 */

#ifndef ODESOLVER_H_
#define ODESOLVER_H_

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

static const int EULER_METHOD = 0;
static const int HEUN_METHOD = 1;
static const int RK4_METHOD = 2;

typedef vec (*EvalFunc)(double, const vec, const void *);

class Solution {
public:
	const rowvec *T;
	const mat *Y;

	inline Solution(rowvec *t, mat *y)
		: T(t), Y(y) {};
	inline ~Solution()
	{ delete T; delete Y; };
};

vec ODEstep(double tn, vec yn, float h, EvalFunc f, int Method, void *Pars);

Solution ODEsolver(double t0, vec y0, float tf, float h, EvalFunc f, int Method, void *Pars);


#endif /* ODESOLVER_H_ */
