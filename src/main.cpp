
#include "pch.h"
#include "main.h"

double F(const double t, const void *Pars)
{
	return .5-t;
}

int main()
{
	P1();
	P2();
	P3();
}

void P1()
{
	BAR_Pars setupA
	{
	// m1,m2,m3   a, sigma, K, alpha
		2, 2, 2, .3,   1.1, 1,     2
	};
	ODESolver solver(&BAR, &setupA);
	solver.setMethod(EULER_METHOD);

	double t0=0, tf=500, h = 0.1;
	colvec w0("0.1, 0.02, 0.01, 0.01");

	Solution sol = solver.solve_init(t0, w0, tf, h);

	// Problem a
	Gnuplot g1("lines lw 3");
	setOutputPDF(&g1, 7, 5, "fig1A.pdf");

	vector<string> titles
	{
		"x1", "x2", "x3", "y"
	};
	plot_xY(&g1, *sol.T, *sol.Y, titles);

	// Problem b
	Gnuplot g2("lines lw 3");
	setOutputPDF(&g2, 7, 5, "fig1B.pdf");
	g2.set_title("Pray vs Predator");
	rowvec x = sol.Y->row(0) + sol.Y->row(1) + sol.Y->row(2);
	plot_xy(&g2, rowvec(sol.Y->row(3)), mat(x), "");
}

void P2()
{
	BAR_Pars setupB
	{
	    //   m1,  m2,  m3   a, sigma, K, alpha
	       2.25, 2.5, 2.5, .4,   1.1, 1,   1.2
	};

	ODESolver solver(&BAR, &setupB);
	solver.setMethod(EULER_METHOD);

	double t0=0, tf=500;
	Col<double> w0("0.001, 0.002, 0.1, 0.1");

	// Problem a
	Gnuplot g1("lines lw 3");
	setOutputPDF(&g1, 20, 5, "fig2A.pdf");
	g1.cmd("set multiplot layout 1,4 rowsfirst");

	rowvec x;
	char title[25];

	double h[]{0.05, 0.1, 0.2, 0.4};
	for (int i=0; i<4; ++i)
	{
		Solution sol = solver.solve_init(t0, w0, tf, h[i]);
		x = sol.Y->row(0) + sol.Y->row(1) + sol.Y->row(2);
		sprintf(title, "{/:Bold=24 h=%.2f}", h[i]);

		g1.reset_plot();
		g1.set_title(title);
		//g1.set_xrange(-0.2, 1.2);
		g1.set_yrange(0, .5);
		g1.set_xlabel("{/:Bold #prey}");
		g1.set_ylabel("{/:Bold #predators }");
		plot_xy(&g1, x, sol.Y->row(3), "");
	}

	// Problem b
	Gnuplot g2("lines lw 3");
	setOutputPDF(&g2, 20, 5, "fig2B.pdf");
	g2.cmd("set multiplot layout 1,4 rowsfirst");
	solver.setMethod(RK4_METHOD);
	for (int i=0; i<4; ++i)
	{
		Solution sol = solver.solve_init(t0, w0, tf, h[i]);
		x = sol.Y->row(0) + sol.Y->row(1) + sol.Y->row(2);

		g2.reset_plot();
		sprintf(title, "{/:Bold=24 h=%.2f}", h[i]);
		g2.set_title(title);
		//g1.set_xrange(-0.2, 1.2);
		g2.set_yrange(0, .5);
		g2.set_xlabel("{/:Bold #prey}");
		g2.set_ylabel("{/:Bold #predators }");
		plot_xy(&g2, x, sol.Y->row(3), "");
	}
	g2.cmd("unset multiplot");

	// Problem c
	Gnuplot g3("lines lw 3");
	setOutputPDF(&g3, 10, 5, "fig2C.pdf");
	g3.cmd("set multiplot layout 1,2 rowsfirst");

	tf = 100;
	Solution sol = solver.solve_init(t0, w0, tf, 0.1);
	x = sol.Y->row(0) + sol.Y->row(1) + sol.Y->row(2);

	g3.reset_plot();
	g3.set_title("{/:Bold=24 Tf = 100, x vs y }");
	g3.set_xlabel("{/:Bold #predators }");
	g3.set_ylabel("{/:Bold #prey}");
	plot_xy(&g3, x, sol.Y->row(3), "");

	tf = 1000;
	Solution sol2 = solver.solve_init(t0, w0, tf, 0.1);
	g3.set_title("{/:Bold=24 Tf = 100, per time }");
	g3.set_xlabel("{/:Bold time }");
	g3.set_legend("left");
	vector<string> titles {
		"x1", "x2", "x3", "y"
	};
	plot_xY(&g3, *sol2.T, *sol2.Y, titles);

	g3.cmd("unset multiplot");
}

void P3()
{
	// problem a
	BAR_Pars setupB
	{
	//    m1,  m2,  m3   a, sigma, K, alpha
		2.25, 2.5, 2.5, .4,   1.1, 1,   1.2
	};
	ODESolver solver(&BAR, &setupB);
	solver.setMethod(RK4_METHOD);

	Col<double> w0("0.001, 0.002, 0.1, 0.1");
	Solution refSol = solver.solve_init(0, w0, 500, 0.01);


	// problem b
	rowvec H{ 0.05, 0.1, 0.2, 0.4, 0.6, 0.8 };
	rowvec E1(H.n_elem);
	solver.setMethod(EULER_METHOD);
	for (int i = 0; i < H.n_elem; ++i)
	{
		Solution qSol = solver.solve_init(0, w0, 500, H[i]);

		E1[i] = ErrorCalc(*refSol.T, *refSol.Y, *qSol.T, *qSol.Y);
	}

	Gnuplot g1("lines lw 3");

	plot_xy(&g1, H, E1, "");


	solver.setMethod(RK4_METHOD);
	rowvec E2(H.n_elem);
	for (int i = 0; i < H.n_elem; ++i)
	{
		Solution qSol = solver.solve_init(0, w0, 500, H[i]);

		E2[i] = ErrorCalc(*refSol.T, *refSol.Y, *qSol.T, *qSol.Y);
	}

	setOutputPDF(&g1, 7, 5, "fig3B.pdf");

	plot_xy(&g1, H, E2, "");

	// problem c
	Gnuplot g2("lines lw 3");

	plot_xy(&g2, log(H), log(E1), "");

	setOutputPDF(&g2, 7, 5, "fig3C.pdf");

	plot_xy(&g2, log(H), log(E2), "");
}

void setOutputPDF(Gnuplot* g, int w, int h, const std::string filename) {
	char str[100];
	sprintf(str, "set terminal pdfcairo size %d,%d", w , h);
	g->cmd(std::string(str));
	sprintf(str,"set term pdfcairo enhanced font \"Helvetica,20\"");
	g->cmd(std::string(str));
	sprintf(str, "set output '%s'", filename.c_str());
	g->cmd(std::string(str));
}

template<typename X, typename Y>
void plot_xy(Gnuplot* g, const X& xx, const Y& yy, const std::string title) {
	stdvec x = conv_to< stdvec >::from( xx );
	stdvec y = conv_to< stdvec >::from( yy );

	g->plot_xy(x ,y, title);
}

void init_multiplot(Gnuplot* g, float width, float height) {
	init_multiplot(g, width, height, 0, -1);
}

void init_multiplot(Gnuplot* g, float width, float height, float* margins, float spacing) {
	std::ostringstream cmdstr;

	cmdstr << "set multiplot ";
	cmdstr << "layout " << width << "," << height << " rowsfirst ";
	cmdstr << "margins ";
	if (margins)
	{
		cmdstr	 << margins[0] << ", " << margins[1] << ", "
				 << margins[2] << ", " << margins[3];
	}
	if (spacing >= 0)
		cmdstr << " spacing " << spacing;

	g->cmd(cmdstr.str());
}

void plot_xY(Gnuplot* g, const rowvec& x, const mat& y) {
	vector<string> titles;
	for (uint i=0; i<y.n_rows; ++i)
		titles.push_back("");
	plot_xY(g, x, y, titles);
}

void plot_xY(Gnuplot* g, const rowvec& x, const mat& y, const vector<string> titles) {
	std::ofstream tmp;
	std::string name = g->create_tmpfile(tmp);

	if (x.n_cols != y.n_cols)
	{
		throw GnuplotException("Length of the std::vectors differs");
	}

	for (uint j = 0; j < y.n_cols; ++j)
	{
		tmp << x[j];
		for(uint i = 0; i < y.n_rows; ++i)
		{
			tmp << " " << y(i,j);
		}
		tmp << std::endl;
	}

    tmp.flush();
    tmp.close();

    std::ostringstream cmdstr;

    cmdstr << "plot ";

    for (uint i=0; i < y.n_rows; ++i)
    {

    	cmdstr << "\"" << name <<  "\" using " << to_string(1) << ":" << to_string(2+i);

    	if (titles[i] == "")
			cmdstr << " notitle ";
		else
			cmdstr << " title \"" << titles[i] << "\" ";


		if(g->get_smooth() == "")
			cmdstr << " with " << g->get_pstyle();
		else
			cmdstr << " smooth " << g->get_smooth();

		if(i+1 == y.n_cols)
			cmdstr << std::endl;
		else
			cmdstr << ", ";
    }

    g->cmd(cmdstr.str());
}

void wait_for_key ()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
  cout << endl << "Press any key to continue..." << endl;

  FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
  _getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
  cout << endl << "Press ENTER to continue..." << endl;

  std::cin.clear();
  std::cin.ignore(std::cin.rdbuf()->in_avail());
  std::cin.get();
#endif
  return;
}
