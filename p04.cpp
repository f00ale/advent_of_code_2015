#include <iostream>
#include <sstream>
#include <iomanip>

#include "md5_util.h"


int main() {
  int ans1 = 0;
  int ans2 = 0;

  std::string key;

  {
    bool done = false;
    while(!done) {
      char c;
      std::cin.get(c);
      if(!std::cin.good()) {
	done = true;
	c = '\n';
      }
      if(c >= 'a' && c <= 'z') key.push_back(c);
    }
  }

  while(1) {
    std::ostringstream os;
    ans1++;
    os << key << ans1;
    auto str = os.str();
    auto hash = md5::md5(str.data(), str.length());
    if((hash[0] & 0x00f0ffff) == 0) break;
  }
  
  while(1) {
    std::ostringstream os;
    ans2++;
    os << key << ans2;
    auto str = os.str();
    auto hash = md5::md5(str.data(), str.length());
    if((hash[0] & 0x00ffffff) == 0) break;
  }
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
