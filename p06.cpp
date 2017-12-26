#include <iostream>
#include <string>
#include <vector>

bool grid1[1000][1000];
int grid2[1000][1000];

int main() {
  int ans1 = 0;
  int64_t ans2 = 0;
  enum class Action { on, off, toggle };
  struct instruction {
    Action a;
    int x0, y0, x1, y1;
    instruction(Action _a, int _x0, int _y0, int _x1, int _y1) :
      a{_a}, x0{_x0}, y0{_y0}, x1{_x1}, y1{_y1} {}
  };
  
  std::vector<instruction> instructions;
  
  {
    bool done = false;
    std::string str, mode;
    std::vector<int> nums;
    int num = 0;
    bool innum = false;
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
      } else {
	if(innum) {
	  nums.push_back(num);
	}
	innum = false;
	num = 0;
      }
      
      if(c >= 'a' && c <= 'z') {
	str.push_back(c);
      } else {
	if(str == "on" || str == "off" || str == "toggle") {
	  mode = str;
	}
	str.clear();
      }

      if(c == '\n') {
	if(nums.size() == 4) {
	  Action a = [](const auto & s) {
	    if(s == "on") return Action::on;
	    else if(s == "off") return Action::off;
	    else return Action::toggle;
	  }(mode);
	  instructions.emplace_back(a, nums[0], nums[1], nums[2], nums[3]);
	}

	nums.clear();
	mode.clear();	
      }
    }       
  }

  for(int x = 0; x < 1000; x++) {
    for(int y = 0; y < 1000; y++) {
      grid1[x][y] = false;
      grid2[x][y] = 0;
    }
  }

  for(auto & i : instructions) {
    for(int x = i.x0; x <= i.x1; x++) {
      for(int y = i.y0; y <= i.y1; y++) {
	switch(i.a) {
	case Action::on:
	  grid1[x][y] = true;
	  grid2[x][y]++;
	  break;
	case Action::off:
	  grid1[x][y] = false;
	  if(grid2[x][y] > 0)
	    grid2[x][y]--;
	  break;
	case Action::toggle:
	  grid1[x][y] = !grid1[x][y];
	  grid2[x][y]+=2;
	  break;
	}
      }
    }
  }

  for(int x = 0; x < 1000; x++) {
    for(int y = 0; y < 1000; y++) {
      if(grid1[x][y]) ans1++;
      ans2 += grid2[x][y];
    }
  }
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
