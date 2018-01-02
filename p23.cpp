#include <iostream>
#include <vector>
#include <map>
#include <string>

int main() {
  uint32_t ans1 = 0;
  uint32_t ans2 = 0;

  enum class Inst {
    hlf, tpl, inc, jmp, jie, jio
  };

  std::map<std::string, Inst> imap {
    {"hlf", Inst::hlf},
    {"tpl", Inst::tpl},
    {"inc", Inst::inc},
    {"jmp", Inst::jmp},
    {"jie", Inst::jie},
    {"jio", Inst::jio}
  };

  struct cmd {
    Inst inst;
    char reg;
    int off;
    cmd(Inst i, char r, int o) : inst{i}, reg{r}, off{o} {}
  };
  std::vector<cmd> prog;
  
  {
    bool done = false;
    std::string tmp;
    std::string inst;
    char reg = 0;
    int num = 0;
    bool innum = false;
    bool neg = false;
    while(!done) {
      char c;
      std::cin.get(c);
      if(!std::cin.good()) {
	done = true;
	c = '\n';
      }
      if(c >= 'a' && c <= 'z') {
	tmp.push_back(c);
      } else if(!tmp.empty()) {
	if(tmp.size() == 1) {
	  reg = tmp[0] - 'a';
	} else {
	  inst = tmp;
	}
	tmp.clear();
      }

      if(c >= '0' && c <= '9') {
	num *= 10;
	num += c - '0';
	innum = true;
      } else if(c == '-') {
	neg = true;
      }

      if(c == '\n') {
	if(!inst.empty()) {
	  if(neg) num*=-1;
	  prog.emplace_back(imap[inst], reg, num);
	}
	inst.clear();
	tmp.clear();
	reg = 0;
	num = 0;
	neg = false;
	innum = false;
      }
    }    
  }

  for(uint32_t i = 0; i < 2; i++) {
    int pos = 0;
    uint32_t regs[2] = {i, 0};
    while(pos >= 0 && pos < prog.size()) {
      const auto & s = prog[pos];
      pos++;
      switch(s.inst) {
      case Inst::hlf: regs[s.reg] /= 2; break;
      case Inst::tpl: regs[s.reg] *= 3; break;
      case Inst::inc: regs[s.reg]++; break;
      case Inst::jmp: pos += s.off - 1; break;
      case Inst::jie: if(!(regs[s.reg]&1)) pos += s.off - 1; break;
      case Inst::jio: if(regs[s.reg] == 1) pos += s.off - 1; break;
      }
    }

    if(i == 0) ans1 = regs['b' - 'a'];
    else ans2  = regs['b' - 'a'];
  }
    
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;  
}
