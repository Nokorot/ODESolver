/*
 * main.h
 *
 *  Created on: 5 Feb 2019
 *      Author: noko
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "gnuplot/gnuplot_i.h"
#include "BAR.h"
#include "ODESolver.h"
#include "ErrorCalc.h"

using namespace arma;

typedef std::vector<double> stdvec;
typedef unsigned int uint;

void P1();
void P2();
void P3();
int main();

void setOutputPDF(Gnuplot* g, int w, int h, const std::string filename);

template<typename X, typename Y>
void plot_xy(Gnuplot* g, const X& x, const Y& y, const std::string title);

void plot_xY(Gnuplot* g, const rowvec& x, const mat& y);
void plot_xY(Gnuplot* g, const rowvec& x, const mat& y, const vector<string> titles);

void init_multiplot(Gnuplot* g, float width, float height);
void init_multiplot(Gnuplot* g, float width, float height, float* margins, float spacing);

void wait_for_key();

#endif /* MAIN_H_ */
