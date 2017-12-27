#include <iostream>
#include <sstream>
#include <string>

int main() {
  int ans1 = 0;
  int ans2 = 0;
  std::string input;
  {
    bool done = false;
    while(!done) {
      char c;
      std::cin.get(c);
      if(!std::cin.good()) {
	done = true;
	c = '\n';
      }
      if(c >= '0' && c <= '9') input.push_back(c);
    }
  }

  //std::cout << input << std::endl;
  for(int iter = 0; iter < 50; iter++) {
    if(iter == 40) ans1 = input.length();
    std::string::size_type p = 0;
    std::ostringstream os;
    while(p < input.size()) {
      decltype(p) i = 0;
      while(p+i < input.size() && input[p] == input[p+i]) i++;
      os << i << input[p];
      p+=i;
    }
    input = os.str();
    //std::cout << input << std::endl;
  }
  ans2 = input.length();
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
