#include <iostream>
#include <vector>
#include <map>
#include <string>

std::map<std::string, int> ticker = {
  { "children",    3 },
  { "cats",        7 },
  { "samoyeds",    2 },
  { "pomeranians", 3 },
  { "akitas",      0 },
  { "vizslas",     0 },
  { "goldfish",    5 },
  { "trees",       3 },
  { "cars",        2 },
  { "perfumes",    1 }
};

int main() {
  int ans1 = 0;
  int ans2 = 0;

  struct sue {
    sue(int i, std::map<std::string, int> d) : idx{i}, data{std::move(d)} {}
    int idx;
    std::map<std::string, int> data;
  };

  std::vector<sue> sues;
  
  {
    bool done = false;
    bool innum = false;
    int num = 0;
    int idx;
    std::string s;
    std::map<std::string, int> m;
    
    while(!done) {
      char c;
      std::cin.get(c);
      if(!std::cin.good()) {
	done = true;
	c = '\n';
      }

      if(c >= '0' && c <= '9') {
	num *= 10;
	num += c - '0';
	innum = true;
      } else if(innum) {
	if(s == "Sue") {
	  idx = num;
	} else {
	  m.emplace(s, num);
	}
	num = 0;
	innum = false;
	s.clear();
      }

      if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
	s.push_back(c);
      }

      if(c == '\n') {
	if(!m.empty()) {
	  sues.emplace_back(idx, std::move(m));
	}

	m.clear();
	s.clear();
	num = 0;
	innum = false;
	idx = 0;
      }
      
    }
  }

  for(const auto & s : sues) {
    bool ok = true;
    for(const auto & i : s.data) {
      auto it = ticker.find(i.first);
      if(it == ticker.end() || it->second != i.second) {
	ok = false;
	break;
      }
    }
    if(ok) {
      ans1 = s.idx;
      break;
    }
  }

  for(const auto & s : sues) {
    bool ok = true;
    for(const auto & i : s.data) {
      auto it = ticker.find(i.first);
      if(it == ticker.end()) ok = false;
      else if(i.first == "cats" || i.first == "trees") ok = i.second > it->second;
      else if(i.first == "pomeranians" || i.first == "goldfish") ok = i.second < it->second;
      else ok = i.second == it->second;	

      if(!ok) break;
    }
    if(ok) {
      ans2 = s.idx;
      break;
    }
  }

  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
