#include <iostream>
#include <vector>

int iterate(auto it, auto end, int rest, int & mincnt, int & minant, int ant = 0) {
  if(rest == 0) {
    if(minant == 0 || ant < minant) {
      minant = ant;
      mincnt = 1;
    } else if(minant == ant) {
      mincnt++;
    }
    return 1;
  }
  if(rest < 0 || it == end) return 0;
  
  return
    iterate(it+1, end, rest, mincnt, minant, ant) +
    iterate(it+1, end, rest-*it, mincnt, minant, ant+1);  
}

int main() {
  int ans1 = 0;
  int ans2 = 0;

  std::vector<int> v;
  
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
	v.emplace_back(num);
	num = 0;
	innum = false;
      }
    }
  }

  int tmp = 0;
  ans1 = iterate(v.begin(), v.end(), 150, ans2, tmp);
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
