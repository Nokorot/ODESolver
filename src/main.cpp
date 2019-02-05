
#include "pre-comp.h"

#include "main.h"

int main() {
  P1();
}

void P1() {
  BAR_Pars setupA{
    // m1,m2,m3   a, sigma, K, alpha
        2, 2, 2, .3,   1.1, 1,     2
  };

  double t0=0, tf=500, h = 0.1;
  Col<double> w0("0.1, 0.02, 0.01, 0.01");

  Solution sol = ODEsolver(t0, w0, tf, h, &BAR, 0, &setupA);

  // Problem a
  Gnuplot g1("lines lw 5");
  plot_xy(&g1, *sol.T, sol.Y->row(0), "x1" );
  plot_xy(&g1, *sol.T, sol.Y->row(1), "x2" );
  plot_xy(&g1, *sol.T, sol.Y->row(2), "x3" );
  plot_xy(&g1, *sol.T, sol.Y->row(3), "y" );

  wait_for_key();

  // Problem b
  rowvec x = sol.Y->row(1) + sol.Y->row(1) + sol.Y->row(2);
  //plot_xy(&g1, *sol.T, x);
}

template<typename X, typename Y>
void plot_xy(Gnuplot* g, const X &x, const Y y, const std::string title) {
  g->plot_xy(
    conv_to< stdvec >::from( x ),
    conv_to< stdvec >::from( y ),
    title );
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
