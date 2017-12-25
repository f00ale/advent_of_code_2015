#include <iostream>

int main() {
  int ans1 = 0;
  int ans2 = 0;

  {
    bool done = false;
    bool neg_seen = false;
    int iter = 0;
    while(!done) {
      char c;
      std::cin.get(c);
      if(!std::cin.good()) {
	done = true;
	c = '\n';
      }
      if(c == '(' || c == ')') {
	if(c == '(') ans1++;
	else if(c == ')') ans1--;
	iter++;
	if(ans1 < 0 && !neg_seen) {
	  ans2 = iter;
	  neg_seen = true;
	}
      }
    }
  }
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
