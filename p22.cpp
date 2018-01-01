#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <deque>

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
  int bossDamage   = m["Damage"];

  struct state {
    bool playerturn;
    int playerHealth;
    int mana;
    int manaspent;
    int shieldtimer;
    int poisontimer;
    int rechargetimer;
    int bossHealth;
    state(int ph, int m, int bh)
      : playerturn(true)
      , playerHealth(ph)
      , mana(m)
      , manaspent(0)
      , shieldtimer(0)
      , poisontimer(0)
      , rechargetimer(0)
      , bossHealth(bh)
    {}
  };

  for(int i = 0; i < 2; i++) {
    std::deque<state> q;
    q.emplace_back(50, 500, bossStrength);
  
    while(!q.empty()) {
      auto c = q.front();
      q.pop_front();

      if(i == 1 && c.playerturn) {
	c.playerHealth--;
      }
    
      if(c.playerHealth <= 0) {
	continue;
      }
      int armor = 0;
      if(c.poisontimer) {
	c.poisontimer--;
	c.bossHealth -= 3;
      }
      if(c.shieldtimer) {
	c.shieldtimer--;
	armor = 7;
      }
      if(c.rechargetimer) {
	c.rechargetimer--;
	c.mana += 101;
      }
      if(c.bossHealth <= 0) {
	if(i == 0) {
	  ans1 = c.manaspent;
	} else {
	  ans2 = c.manaspent;
	}
	break;
      }
    
      if(c.playerturn) {
	c.playerturn = false;
	if(c.mana >= 53) {
	  auto n = c;
	  n.mana -= 53;
	  n.manaspent += 53;
	  n.bossHealth -= 4;
	  q.push_back(n);
	}
	if(c.mana >= 73) {
	  auto n = c;
	  n.mana -= 73;
	  n.manaspent += 73;
	  n.bossHealth -= 2;
	  n.playerHealth += 2;
	  q.push_back(n);
	}
	if(c.mana >= 113 && !c.shieldtimer) {
	  auto n = c;
	  n.mana -= 113;
	  n.manaspent += 113;
	  n.shieldtimer = 6;
	  q.push_back(n);
	}
	if(c.mana >= 173 && !c.poisontimer) {
	  auto n = c;
	  n.mana -= 173;
	  n.manaspent += 173;
	  n.poisontimer = 6;
	  q.push_back(n);
	}
	if(c.mana >= 229 && !c.rechargetimer) {
	  auto n = c;
	  n.mana -= 229;
	  n.manaspent += 229;
	  n.rechargetimer = 5;
	  q.push_back(n);
	}
      } else {
	c.playerturn = true;
	int damage = bossDamage - armor;
	if(damage < 1) damage = 1;
	c.playerHealth -= damage;
	q.push_back(c);
      }
    }
  }
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
