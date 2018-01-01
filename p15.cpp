#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>

std::tuple<int,int> iterate(auto it, auto end, int rest, const std::tuple<int,int,int,int,int> & tp) {
  auto [tc, td, tf, tt, tcal] = tp;
  int ret1 = 0, ret2 = 0;
  const auto & [n, c, f, d, t, cal] = *it;
  it++;
  if(it != end) {
    for(int i = 0; i <= rest; i++) {
      auto [r1,r2] = iterate(it, end, rest-i, {tc+i*c, td+i*d, tf+i*f, tt+i*t, tcal+i*cal});
      if(r1 > ret1) ret1 = r1;
      if(r2 > ret2) ret2 = r2;
    }
  } else {
    tc += rest*c;
    td += rest*d;
    tf += rest*f;
    tt += rest*t;
    tcal += rest*cal;
    if(tc > 0 && td > 0 && tf > 0 && tt > 0) {
      ret1 = tc*td*tf*tt;
      if(tcal == 500) ret2 = ret1;
    }
  }
  return {ret1,ret2};
};
  

int main() {
  int ans1 = 0;
  int ans2 = 0;

  std::vector<std::tuple<std::string, int, int, int, int, int>> data;
  
  {
    int num = 0;
    bool neg = false;
    bool innum = false;
    std::string tmp, name;
    std::vector<int> nums;
    bool done = false;
    while(!done) {
      char c;
      std::cin.get(c);
      if(!std::cin.good()) {
	done = true;
	c = '\n';
      }

      if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
	tmp.push_back(c);
      } else {
	if(!tmp.empty()) {
	  if(tmp[0] >= 'A' && tmp[0] <= 'Z') {
	    name = tmp;
	  }
	  tmp.clear();
	}
      }

      if(c >= '0' && c <= '9') {
	num *= 10;
	num += c - '0';
	innum = true;
      } else if(!innum && c == '-') {
	neg = true;
	innum = true;
      } else {
	if(innum) {
	  nums.push_back((neg?-1:1)*num);
	}
	num = 0;
	innum = false;
	neg = false;
      }

      if(c == '\n') {
	if(!name.empty() && nums.size() == 5) {
	  data.emplace_back(name, nums[0], nums[1], nums[2], nums[3], nums[4]);	  
	}
	name.clear();
	nums.clear();
      }
      
    }
  }

  std::tie(ans1,ans2) = iterate(data.begin(), data.end(), 100, {0,0,0,0,0});
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
