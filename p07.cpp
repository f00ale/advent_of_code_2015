#include <iostream>
#include <deque>
#include <string>
#include <map>

#include <stdint.h>

int main() {
  int ans1 = 0;
  int ans2 = 0;
  std::map<std::string, uint16_t> values;
  enum class OP {
    Set, And, Or, Not, LShift, RShift
  };
  
  struct gate {
    std::string target;
    OP op;
    std::string reg1;
    std::string reg2;
    uint16_t val1;
    uint16_t val2;
    gate(std::string t, OP o, std::string r1, std::string r2, uint16_t v1, uint16_t v2)
      : target(move(t)), op(o), reg1(move(r1)), reg2(move(r2)), val1(v1), val2(v2) {}
  };

  std::deque<gate> gates;
  
  {
    bool done = false;
    std::string tmp;
    std::string cmd;
    int n1 = 0, n2 = 0;
    std::string r1, r2;
    std::string target;
    bool h1 = false, h2 = false;
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
	if(!h1) {
	  h1 = true;
	  n1 = num;
	} else if(!h2) {
	  h2 = true;
	  n2 = num;
	}
	num = 0;
	innum = false;
      }

      if(c >= 'A' && c <= 'Z') cmd.push_back(c);

      if(c >= 'a' && c <= 'z') {
	tmp.push_back(c);
      } else if(!tmp.empty()) {
	if(!h1) {
	  r1 = tmp;
	  h1 = true;
	} else if(!h2) {
	  r2 = tmp;
	  h2 = true;
	} else {
	  target = tmp;
	}
	tmp.clear();
      }

      if(c == '>') h1 = h2 = true;

      if(c == '\n') {
	if(!target.empty()) {
	  auto op = [](const std::string & s) {
	    if(s.empty()) return OP::Set;
	    else if(s == "OR") return OP::Or;
	    else if(s == "AND") return OP::And;
	    else if(s == "NOT") return OP::Not;
	    else if(s == "LSHIFT") return OP::LShift;
	    else if(s == "RSHIFT") return OP::RShift;
	    else {
	      std::cout << "Cannot decode " << s << std::endl;
	    }
	    return OP::Set;
	  };
	  gates.emplace_back(target, op(cmd), r1, r2, n1, n2);	  
	}

	h1 = h2 = false;
	tmp.clear();
	n1 = n2 = 0;
	r1.clear();
	r2.clear();
	target.clear();
	cmd.clear();
      }
      
    }
  }

  for(int i = 0; i < 2; i++) {
    auto gts = gates;
    while(!gts.empty()) {
      auto g = gts.front();
      gts.pop_front();
      bool ok = true;
      if(values.find(g.target) != values.end()) {
	std::cout << "value for " << g.target << " already set!" << std::endl;
	continue;
      }
      if(!g.reg1.empty() && values.find(g.reg1) == values.end()) ok = false;
      if((g.op == OP::And || g.op == OP::Or || g.op == OP::LShift || g.op == OP::RShift)
	 && !g.reg2.empty() && values.find(g.reg2) == values.end()) ok = false;
      if(ok) {
	uint16_t v1 = g.reg1.empty() ? g.val1 : values[g.reg1];
	uint16_t v2 = g.reg2.empty() ? g.val2 : values[g.reg2];
	switch(g.op) {
	case OP::Set: values[g.target] = v1; break;
	case OP::Not: values[g.target] = ~v1; break;
	case OP::And: values[g.target] = v1 & v2; break;
	case OP::Or:  values[g.target] = v1 | v2; break;
	case OP::LShift: values[g.target] = v1 << v2; break;
	case OP::RShift: values[g.target] = v1 >> v2; break;
	}      
      } else {
	gts.push_back(g);
      }
    }
    
    if(i == 0) {
      ans1 = values["a"];
      values.clear();
      values["b"] = ans1;
    } else {
      ans2 = values["a"];
    }
  }
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
