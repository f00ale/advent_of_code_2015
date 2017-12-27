#include <iostream>
#include <string>

int main() {
  std::string ans1;
  std::string ans2;
  std::string input;
  
  {
    bool done = false;
    while(!done) {
      char c;
      std::cin.get(c);
      if(!std::cin.good()) {
	c = '\n';
	done = true;
      }

      if(c >= 'a' && c <= 'z') {
	input.push_back(c);
      }
    }
  }

  auto calcnext = [](std::string & s) {
    auto it = s.rbegin();
    bool done = true;
    do {
      done = true;
      (*it)++;
      if(*it > 'z') {
	done = false;
	*it = 'a';
	it++;
      }
    } while(!done);
  };

  auto isok = [](const std::string & s) {
    if(s.find_first_of("iol") != std::string::npos) return false;
    bool ok = false;
    for(int i = 0; !ok && i < s.size()-2; i++) {
      if(((s[i]+1) == s[i+1]) && ((s[i]+2) == s[i+2])) {
	ok = true;
      }
    }
    if(!ok) return false;
    ok = false;
    for(int i = 0; !ok && i < s.size()-3; i++) {
      if(s[i] == s[i+1]) {
	for(int j = i+2; !ok && j < s.size()-1; j++) {
	  if(s[j] == s[j+1]) {
	    ok = true;
	  }
	}
      }
    }
    return ok;
  };

  do {
    calcnext(input);
  } while(!isok(input));
  ans1 = input;
  do {
    calcnext(input);
  } while(!isok(input));
  ans2 = input;
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
