/*
 * BAR.h
 *
 *	 Biological Arms Race Vector Field
 *
 *  Created on: 5 Feb 2019
 *      Author: noko
 */

#ifndef BAR_H_
#define BAR_H_

#include <armadillo>

using namespace arma;

typedef struct {
	float m1, m2, m3;
	float a, sigma, K, alpha;
} BAR_Pars;

vec BAR(double t, const vec w, const void *Pars);


#endif /* BAR_H_ */
