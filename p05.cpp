#include <iostream>
#include <vector>

int main() {
  int ans1 = 0;
  int ans2 = 0;

  std::vector<std::string> strs;
  
  {
    bool done = false;
    std::string tmp;
    while(!done) {
      char c;
      std::cin.get(c);
      if(!std::cin.good()) {
	done = true;
	c = '\n';
      }
      if(c >= 'a' && c <= 'z') tmp.push_back(c);
      if(c == '\n') {
	if(!tmp.empty()) {
	  strs.push_back(tmp);
	  tmp.clear();
	}
      }
    }
  }

  auto isnice1 = [](const std::string & s) -> bool {
    std::string::size_type p = 0;
    for(int i = 0; i < 3; i++) {
      p = s.find_first_of("aeiou", p);
      if(p == std::string::npos) return false;
      p++;
    }

    bool found = false;
    for(p = 0; !found && p < s.size()-1; p++) {
      if(s[p] == s[p+1]) found = true;
    }
    if(!found) return false;
    
    if(s.find("ab") != std::string::npos) return false;
    if(s.find("cd") != std::string::npos) return false;
    if(s.find("pq") != std::string::npos) return false;
    if(s.find("xy") != std::string::npos) return false;
    
    return true;
  };

  for(const auto & s : strs) {
    if(isnice1(s)) ans1++;
  }

  auto isnice2 = [](const std::string & s) -> bool {
    bool found = false;
    for(auto i = 0; i < s.size()-2; i++) {
      if(s[i] == s[i+2]) found = true;
    }
    if(!found) return false;    
    found = false;
    for(auto i = 0; i < s.size()-1; i++) {
      for(auto j = i+2; j < s.size()-1; j++) {
	if(s[i] == s[j] && s[i+1] == s[j+1]) found = true;
      }
    }
    return found;
  };
  
  for(const auto & s : strs) {
    if(isnice2(s)) ans2++;
  }
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
