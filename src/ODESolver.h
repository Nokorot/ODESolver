/*
 * ODESolver.h
 *
 *  Created on: 5 Feb 2019
 *      Author: noko
 */

#ifndef ODESOLVER_H_
#define ODESOLVER_H_

using namespace std;
using namespace arma;

static const int EULER_METHOD = 0;
static const int HEUN_METHOD = 1;
static const int RK4_METHOD = 2;

static const int INIT_VALUE_PROBLEM = 0xf + 0;
static const int BOUNDERY_VALUE_PROBLEM = 0xf + 1;

typedef vec (*EvalFunc)(double, const vec, const void *);

class Solution
{
public:
	const rowvec *T;
	const mat *Y;

	inline Solution(rowvec *t, mat *y)
		: T(t), Y(y) {};
	inline ~Solution()
	{ delete T; delete Y; };
};

class ODESolver
{
private:
	// Eval function describing the differential equation. Assuming a system of
	// first order equations, this function represents the left-hand side of
	// the equation.
	EvalFunc f;
	// Parameters to be passed to the eval function.
	void *Pars;

	// Numerical method to use
	int method = RK4_METHOD;

	// Calculate the next step, for initial value problem, according to the
	// chosen numerical method.
	vec ODEstep(double tn, vec yn, double h);

public:

	// Specifies the equation by eval function and what kind of equation it is
	ODESolver(EvalFunc f);
	//ODESolver(EvalFunc f, int EQ_TYPE);

	// Specifies associated parameters
	ODESolver(EvalFunc f, void* Pars);
	//ODESolver(EvalFunc f, void* Pars, int EQ_TYPE);

	//----------------------------------------------------------------------------------
	///\brief Solves the initial value problem given by the evalFunctuon and
	///  the parameter initial values. Assuming an equatuon of the form:
	///         d_t Y(t) = f(t, Y)
	///
	/// \param
	///			t0 --> Initial time
	///			y0 --> Initial values
	///			tf --> final time
	///			h  --> time step size
	///
	/// \return <-- A solution object containing, containing a reference to the
	///	discrete time vector and the discrete function value matrix
	//----------------------------------------------------------------------------------
	Solution solve_init(double t0, vec y0, double tf, double h);

	//----------------------------------------------------------------------------------
	///\brief Solves the 1D boundary value problem given by the evalFunctuon and
	///  the parameter initial values. Assuming an equation of the form:
	///  		d_xx Y(x) = f(x)
	///
	/// \param
	///			t0 --> Initial time
	///			y0 --> Initial values
	///			tf --> final time
	///			h  --> time step size
	///
	/// \return <-- A solution object containing, containing a reference to the
	///	discrete time vector and the discrete function value matrix
	//----------------------------------------------------------------------------------
	Solution solve_bv(double (*f)(const double x, const void*), double t0, double tf, double v0, double vf, double h);


	// TODO: EvalFunc highOrder(int order);


	// get and set eval function
	inline EvalFunc getEvalFunc() const { return f; }
	inline void setEvalFunc(EvalFunc f) { this->f = f; }

	// get and set numerical method
	inline int getMethod() const { return method; }
	inline void setMethod(int method = RK4_METHOD) { this->method = method; }

	// get and set associated parameters
	inline void* getParameters() const { return Pars; }
	inline void setParameters(void* parameters) { Pars = parameters; }
};

#endif /* ODESOLVER_H_ */
