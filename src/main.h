/*
 * main.h
 *
 *  Created on: 5 Feb 2019
 *      Author: noko
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "../vendor/gnuplot_i.hpp"
#include <armadillo>

#include "BAR.h"
#include "ODESolver.h"

using namespace arma;

typedef std::vector<double> stdvec;

void P1();
int main();

template<typename X, typename Y>
void plot_xy(Gnuplot* g, const X &x, const Y y, const std::string title);
Gnuplot* plot(Solution sol, const char** titles);
void wait_for_key();


#endif /* MAIN_H_ */
