#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>
#include <deque>

int main() {
  int ans1 = 0;
  int ans2 = 0;

  std::vector<std::tuple<std::string, std::string>> v;
  std::string data;
  std::set<std::string> newstrings;
  
  {
    bool done = false;
    std::string first, second;
    bool firstdone = false;
    while(!done) {
      char c;
      std::cin.get(c);
      if(!std::cin.good()) {
	done = true;
	c = '\n';
      }

      if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
	if(firstdone) second.push_back(c);
	else first.push_back(c);
      } else {
	if(!first.empty()) firstdone = true;
      }

      if(c == '\n') {
	if(firstdone) {
	  if(second.empty()) {
	    data = first;
	  } else {
	    v.emplace_back(first, second);
	  }
	}
	first.clear();
	second.clear();
	firstdone = false;
      }
      
    }
  }

  for(const auto & [f,s] : v) {
    std::string::size_type pos = 0;
    while((pos = data.find(f, pos)) != std::string::npos) {
      auto cpy = data;
      cpy.replace(pos, f.length(), s);
      newstrings.emplace(std::move(cpy));
      pos++;
    }
  }
  ans1 = newstrings.size();

  while(data != "e") {
    bool ok = false;
    for(const auto & [f,s] : v) {
      std::string::size_type pos = 0;
      while((pos = data.find(s, pos)) != std::string::npos) {
	data.replace(pos, s.length(), f);
	ans2++;
	pos++;
	ok = true;
      }
    }
    if(!ok) break;
  }

  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
