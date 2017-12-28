#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>
#include <numeric>

int main() {
  int ans1 = 0;
  int ans2 = 0;

  std::vector<std::tuple<std::string, std::string, int>> scores;
  
  {
    std::string tmp, lg, n1, n2;
    int num = 0;
    bool done = false;
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
      }
      
      if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
	tmp.push_back(c);
      } else {
	if(!tmp.empty()) {
	  if(tmp[0] >= 'A' && tmp[0] <= 'Z') {
	    if(n1.empty()) {
	      n1 = tmp;
	    } else {
	      n2 = tmp;
	    }
	  } else if(tmp == "lose" || tmp == "gain") {
	    lg = tmp;
	  }
	}
	tmp.clear();
      }
      
      if(c == '\n') {
	if(!n1.empty() && !n2.empty() && !lg.empty()) {
	  int m = (lg == "lose" ? -1 : 1);
	  scores.emplace_back(n1, n2, m*num);
	}
	n1.clear();
	n2.clear();
	lg.clear();
	num = 0;
      }
      
    }
  }

  std::vector<std::string> names;

  {
    std::set<std::string> a;
    for(auto & [p1, p2, s] : scores) {
      a.insert(p1);
      a.insert(p2);
    }
    names.reserve(a.size());
    for(auto & n : a) names.push_back(n);
  }

  std::vector<std::vector<int>> arr;
  for(int i = 0; i < names.size(); i++) {
    arr.emplace_back(names.size());    
  }

  for(auto & [t, f, s] : scores) {
    auto tit = std::find(std::begin(names), std::end(names), t);
    auto fit = std::find(std::begin(names), std::end(names), f);
    arr[std::distance(std::begin(names), tit)][std::distance(std::begin(names), fit)] = s;
  }
  
  std::vector<int> idx(names.size());
  std::iota(idx.begin(), idx.end(), 0);

  for(int prob = 0; prob < 2; prob++) {
    int ans = 0;
    do {
      int tmp = 0;
      for(int i = 0; i < idx.size(); i++) {
	auto i1 = idx[i];
	auto i2 = idx[(i+1)%idx.size()];
	auto a = arr[i1][i2];
	auto b = arr[i2][i1];
	tmp += a + b;
      }
      if(tmp > ans) ans = tmp;
    } while(std::next_permutation(std::begin(idx), std::end(idx)));

    if(prob == 0) ans1 = ans;
    else ans2 = ans;
    
    std::sort(std::begin(idx), std::end(idx));
    idx.push_back(idx.size());
    for(auto & r : arr) r.push_back(0);
    arr.emplace_back(idx.size());
    std::fill(std::begin(arr.back()), std::end(arr.back()), 0);
  }
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
