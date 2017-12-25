#include <iostream>
#include <tuple>
#include <map>

int main() {
  int ans1 = 0;
  int ans2 = 0;

  std::map<std::tuple<int, int>, int> m1, m2;
  
  {
    bool done = false;
    bool neg_seen = false;
    int iter = 0;
    int x = 0, y = 0;
    int xo = 0, yo = 0;
    int xe = 0, ye = 0;
    bool odd = false;
    m1[{y,x}]++;
    m2[{y,x}]++;
    while(!done) {
      char c;
      std::cin.get(c);
      if(!std::cin.good()) {
	done = true;
	c = '\n';
      }
      bool visit = true;
      switch(c) {
      case '^': y++; if(odd) yo++; else ye++; break;
      case 'v': y--; if(odd) yo--; else ye--; break;
      case '<': x--; if(odd) xo--; else xe--; break;
      case '>': x++; if(odd) xo++; else xe++; break;
      default : visit = false; break;
      }
      if(visit) {
	m1[{y,x}]++;
	if(odd) m2[{yo,xo}]++;
	else m2[{ye,xe}]++;
	odd = !odd;
      }
    }
  }

  ans1 = m1.size();
  ans2 = m2.size();
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
