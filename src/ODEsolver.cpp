
#include "ODESolver.h"

vec ODEstep(double tn, vec yn, float h, EvalFunc f, int Method, void *Pars) {
    vec F1, F2, F3, F4, Y1, Y2, Y3;
    switch(Method){
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

Solution ODEsolver(double t0, vec y0, float tf, float h, EvalFunc f, int Method, void *Pars) {
	int N = (int) ((tf-t0)/h);
	if (tf > t0+N*h) ++N;

	mat *Y = new mat(y0.n_elem, N+1);
	rowvec *T = new rowvec(N+1);

	Y->col(0) = y0; T->at(0) = t0;
    for( int i = 0; i < N; i++) {
        Y->col(i+1) = ODEstep(T->at(i), Y->col(i), h, f, Method, Pars);
        T->at(i+1) = T->at(i)+h;
    }

    if (tf < t0+N*h)
    	T->at(N) = tf;

    return Solution(T, Y);
}
