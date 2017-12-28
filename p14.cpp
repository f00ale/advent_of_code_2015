#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>

int main() {
  int ans1 = 0;
  int ans2 = 0;

  std::vector<std::tuple<std::string, int, int, int, int, int>> data;
  
  {
    int num = 0;
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
      } else {
	if(innum) {
	  nums.push_back(num);
	}
	num = 0;
	innum = false;
      }

      if(c == '\n') {
	if(!name.empty() && nums.size() == 3) {
	  data.emplace_back(name, nums[0], nums[1], nums[2], 0, 0);	  
	}
	name.clear();
	nums.clear();
      }
      
    }
  }

  constexpr int T = 2503;
  for(int t = 0; t < T; t++) {
    for(auto & [n, sp, mt, sl, dist, point] : data) {
      if(t % (mt+sl) < mt) dist += sp;
      if(dist > ans1) ans1 = dist;
    }

    for(auto & [n, sp, mt, sl, dist, point] : data) {
      if(dist == ans1) {
	point++;
	if(point > ans2) ans2 = point;
      }
    }
  }
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
