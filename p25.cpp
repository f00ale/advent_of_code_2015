#include <iostream>
#include <iomanip>
/*
int getnum(int row, int col) {
  int ret = 1;
  int r = 1, c = 1, sr = 1;
  while((r != row || c != col)) {
    c++;
    r--;
    if(r < 1) {
      sr++;
      r = sr;
      c = 1;
    }
    ret++;
  }
  
  return ret;
}

*/

int64_t calccode(int row, int col) {
  int64_t code = 20151125;
  int r = 1, c = 1;
  while(r != row || c != col) {
    c++;
    r--;
    if(r < 1) {
      r = c;
      c = 1;
    }
    code = (code * 252533) % 33554393;
  }
  return code;
}

int main() {
  int64_t ans1 = 0;

  int row = 0;
  int col = 0;

  {
    bool done = false;
    int num = 0;
    bool innum = false;
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
	innum = true;
      } else if(innum) {
	if(!row) row = num;
	else col = num;
	num = 0;
	innum = false;
      }
    }
  }

  ans1 = calccode(row, col);
  
  std::cout << ans1 << std::endl;
}

