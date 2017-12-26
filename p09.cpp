#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>

int calc_short(const std::string & start, const std::vector<std::tuple<std::string, std::string, int>> & v) {
  auto cpy = v;
  cpy.erase(std::remove_if(cpy.begin(), cpy.end(), [&](auto & tp) {
	auto & [t,f,n] = tp;
	return t == start || f == start;
      }), cpy.end());
  int ret = 0;

  for(auto & [t, f, c] : v) {
    if(t == start) {
      int tmp = c + calc_short(f, cpy);
      if(ret == 0 || tmp < ret) ret = tmp;
    } else if(f == start) {
      int tmp = c + calc_short(t, cpy);
      if(ret == 0 || tmp < ret) ret = tmp;
    }
  }
  
  return ret;
}

int calc_long(const std::string & start, const std::vector<std::tuple<std::string, std::string, int>> & v) {
  auto cpy = v;
  cpy.erase(std::remove_if(cpy.begin(), cpy.end(), [&](auto & tp) {
	auto & [t,f,n] = tp;
	return t == start || f == start;
      }), cpy.end());
  int ret = 0;

  for(auto & [t, f, c] : v) {
    if(t == start) {
      int tmp = c + calc_long(f, cpy);
      if(tmp > ret) ret = tmp;
    } else if(f == start) {
      int tmp = c + calc_long(t, cpy);
      if(tmp > ret) ret = tmp;
    }
  }
  
  return ret;
}

int main() {
  int ans1 = 0;
  int ans2 = 0;

  std::vector<std::tuple<std::string, std::string, int>> v;
  
  {
    bool done = false;
    int num = 0;
    std::string tmp, f, t;
    while(!done) {
      char c;
      std::cin.get(c);
      if(!std::cin.good()) {
	c = '\n';
	done = true;
      }

      if(c >= '0' && c <= '9') {
	num *= 10;
	num += c - '0';
      }

      if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
	tmp.push_back(c);
      } else {
	if(!tmp.empty()) {
	  if(f.empty()) f = tmp;
	  else if(tmp != "to") t = tmp;
	  tmp.clear();
	}
      }

      if(c == '\n') {
	if(!t.empty()) {
	  v.emplace_back(f, t, num);
	}
	t.clear();
	f.clear();
	num = 0;
      }
    }
  }
  
  std::set<std::string> all;
  for(auto & [t,f,c] : v) {
    all.insert(t);
    all.insert(f);
  }
  
  for(auto & c : all) {
    auto tmp_short = calc_short(c, v);
    auto tmp_long  = calc_long(c, v);
    if(ans1 == 0 || tmp_short < ans1) ans1 = tmp_short;
    if(tmp_long > ans2) ans2 = tmp_long;
  }
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
