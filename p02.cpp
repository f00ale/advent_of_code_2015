#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int ans1 = 0;
  int ans2 = 0;

  struct box {
    int l, w, h;
    box(int _l, int _w, int _h) : l(_l), w(_w), h(_h) {}
  };
  std::vector<box> boxes;
  
  {
    bool done = false;
    bool neg_seen = false;
    int iter = 0;
    bool hl = false, hw = false, hh = false;
    int l = 0, w = 0, h = 0;
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
	if(!hl) {
	  l = num;
	  hl = true;
	} else if(!hw) {
	  w = num;
	  hw = true;
	} else {
	  h = num;
	  hh = true;
	}

	num = 0;
	innum = false;
	
	if(c == '\n') {
	  if(hl && hw && hh) {
	    boxes.emplace_back(l,w,h);
	  }
	  hl = hw = hh = false;
	  l = w = h = 0;
	}
      }       
    }    
  }

  for(const auto & b : boxes) {
    auto s1 = b.l*b.w;
    auto s2 = b.l*b.h;
    auto s3 = b.w*b.h;
    ans1 += 2*s1 + 2*s2 + 2*s3 + std::min(s1, std::min(s2, s3));

    ans2 += 2*std::min(b.l+b.w, std::min(b.l+b.h, b.h+b.w)) + b.l*b.w*b.h;
  }
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
