#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <tuple>

int main() {
  int ans1 = 0;
  int ans2 = 0;

  std::map<std::string, int> m;
  
  {
    bool done = false;
    int num = 0;
    std::string tmp;
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
      if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
	tmp.push_back(c);
      }
      if(c == '\n') {
	if(!tmp.empty()) 
	  m[tmp] = num;

	tmp.clear();
	num = 0;
      }
    }
  }

  int bossStrength = m["HitPoints"];
  int bossArmor    = m["Armor"];
  int bossDamage   = m["Damage"];
  
  std::vector<std::tuple<int,int,int>> weapons = {
    {   8, 4, 0 },
    {  10, 5, 0 },
    {  25, 6, 0 },
    {  40, 7, 0 },
    {  74, 8, 0 }
  };
  
  std::vector<std::tuple<int,int,int>> armor = {
    {   0, 0, 0 },
    {  13, 0, 1 },
    {  31, 0, 2 },
    {  53, 0, 3 },
    {  75, 0, 4 },
    { 102, 0, 5 }
  };
  
  std::vector<std::tuple<int,int,int>> rings = {
    {   0, 0, 0 },
    {   0, 0, 0 },
    {  25, 1, 0 },
    {  50, 2, 0 },
    { 100, 3, 0 },
    {  20, 0, 1 },
    {  40, 0, 2 },
    {  80, 0, 3 }
  };

  for(auto [ wc, wd, wa ] : weapons) {
    for(auto [ ac, ad, aa ] : armor) {
      for(auto it1 = std::cbegin(rings); it1 != std::cend(rings); it1++) {
	auto [ r1c, r1d, r1a ] = *it1;
	for(auto it2 = it1+1; it2 != std::cend(rings); it2++) {
	  auto [ r2c, r2d, r2a ] = *it2;
	  auto c = wc+ac+r1c+r2c;
	  auto d = wd+ad+r1d+r2d;
	  auto a = wa+aa+r1a+r2a;

	  int ph = 100;
	  int bh = bossStrength;
	  while(ph > 0 && bh > 0) {
	    bh -= d - bossArmor;
	    if(bh <= 0) break;
	    ph -= bossDamage - a;
	  }
	  
	  if(bh <= 0) {
	    if(!ans1 || c < ans1) ans1 = c;
	  } else {
	    if(c > ans2) ans2 = c;
	  }	  
	}
      }
    }
  }
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
