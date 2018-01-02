#include <iostream>
#include <vector>
#include <numeric>

void findqe(auto it, const auto end, int64_t rest, int64_t & ans, int & minant, int ant = 0, int64_t qe = 1) {
  if(rest == 0) {
    if((ans == 0 || qe < ans) && ant <= minant) {
      minant = ant;
      ans = qe;
    }
  } else if(it != end && rest > 0 && ant <= minant) {
    findqe(it+1, end, rest, ans, minant, ant, qe);
    findqe(it+1, end, rest-*it, ans, minant, ant+1, *it * qe);
  }
}

int main() {
  int64_t ans1 = 0;
  int64_t ans2 = 0;

  std::vector<int64_t> v;
  
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
	v.push_back(num);
	num = 0;
	innum = false;
      }
    }
  }

  auto sum = accumulate(begin(v), end(v), 0ll);
  for(int i = 0; i < 2; i++) {
    auto target = sum / (i == 0 ? 3 : 4);
    int num_in_ans = v.size();
    findqe(begin(v), end(v), target, i == 0 ? ans1 : ans2, num_in_ans);
  }
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
