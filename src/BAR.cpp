#include "BAR.h"

vec BAR(double t, const vec w, const void *Pars) {
	BAR_Pars pars = *((BAR_Pars *) Pars);
	float m1 = pars.m1, m2 = pars.m2, m3 = pars.m3;
	float a = pars.a, sigma = pars.sigma, K = pars.K, alpha = pars.alpha;

	double x1 = w(0), x2 = w(2), x3=w(2), y=w(3);
	double x = x1+x2+x3;

	vec f(4);
	f(0) = (alpha/x)*(x1+x2/2)*(x1+x2/2) -alpha*x1*x/K - m1*x1*y/(a+x);
	f(1) = (2*alpha/x)*(x1+x2/2)*(x3+x2/2) -alpha*x2*x/K- m2*x2*y/(a+x);
	f(2) = (alpha/x)*(x3+x2/2)*(x3+x2/2) - alpha*x3*x/K - m3*x3*y/(a+x);
	f(3) = y *((m1*x1 +m2*x2 + m3*x3)/(a+x) - sigma);

	return f;
}
