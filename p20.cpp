#include <iostream>
#include <vector>

int main() {
  int ans1 = 0;
  int ans2 = 0;

  int input = 0;
  
  {
    bool done = false;
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
      } else if(innum) {
	input = num;
	innum = false;
      }
    }
  }

  std::vector<int> v1(input/10), v2(input/10);

  for(int i = 1; i < v1.size(); i++) {
    for(int j = i, k = 0; j < v1.size(); j += i, k++) {
      v1[j] += 10*i;
      if(k < 50) v2[j] += 11*i;
    }
  }

  while(v1[++ans1] < input); 
  while(v2[++ans2] < input); 
    
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
