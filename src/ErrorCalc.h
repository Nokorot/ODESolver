/*
 * ErrorCalc.h
 *
 *  Created on: 13 Feb 2019
 *      Author: noko
 */

#ifndef ERRORCALC_H_
#define ERRORCALC_H_

using namespace arma;

// Linear interpolation
rowvec lineIterp(const rowvec& x, const rowvec& v, const rowvec& xq);

double ErrorCalc(rowvec Tref, mat Yref, rowvec Tq, mat Yq);


#endif /* ERRORCALC_H_ */
