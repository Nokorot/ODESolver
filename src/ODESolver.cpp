
#include "pch.h"
#include "ODESolver.h"


vec ODESolver::ODEstep(double tn, vec yn, double h)
{
	vec F1, F2, F3, F4, Y1, Y2, Y3;
	switch(method){
	case EULER_METHOD:
		return yn + h*f(tn, yn, Pars);
	case HEUN_METHOD:
		// vec F1, Y1;
		F1 = f(tn, yn, Pars);
		Y1 = yn + h*F1;
		return yn + (h/2)*(F1+f(tn+h, Y1, Pars));
	case RK4_METHOD:
		// vec F2, F3, F4, Y2, Y3;
		F1 = f(tn, yn, Pars);
		Y1 = yn + (h/2)*F1;
		F2 = f(tn+h/2, Y1, Pars);
		Y2 = yn + (h/2)*F2;
		F3 = f(tn+h/2, Y2, Pars);
		Y3 = yn + h*F3;
		F4 = f(tn+h, Y3, Pars);
		return yn + (h/6)*(F1 + 2*F2+2*F3+F4);
	default:
		printf("Method not implemented");
		return NULL;
	}
}

ODESolver::ODESolver(EvalFunc evalf)
	: f(evalf), Pars(NULL) {}

ODESolver::ODESolver(EvalFunc evalf, void* pars)
	: f(evalf), Pars(pars) {}

Solution ODESolver::solve_init(double t0, vec y0, double tf, double h)
{
	int N = (int) ((tf-t0)/h);
	if (tf > t0+N*h) ++N;

	mat *Y = new mat(y0.n_elem, N+1);
	rowvec *T = new rowvec(N+1);

	Y->col(0) = y0; T->at(0) = t0;
    for( int i = 0; i < N; i++) {
        Y->col(i+1) = ODEstep(T->at(i), Y->col(i), h);
        T->at(i+1) = T->at(i)+h;
    }

    if (tf < t0+N*h)
    	T->at(N) = tf;

    return Solution(T, Y);
}
