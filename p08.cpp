#include <iostream>

int main() {
  int ans1 = 0;
  int ans2 = 0;

  {
    bool done = false;
    int tot = 0;
    int dec = 0;
    int enc = 0;
    bool esc = 0;
    int hex = 0;
    int linelen = 0;
    while(!done) {
      char c;
      std::cin.get(c);
      if(!std::cin.good()) {
	done = true;
	c = '\n';
      }

      if(c == '\n') {
	if(linelen) {
	  enc+=2;
	}
	linelen = 0;
      }
      
      if(isspace(c)) continue;
      linelen++;
      tot++;
      enc++;
      if(c == '\\' || c == '\"' || c == '\'') enc++;
      
      if(esc) {
	esc = false;
	if(c == 'x') hex = 2;
	continue;
      }

      if(hex) {
	hex--;
	continue;
      }

      if(c == '\"') {
	continue;
      }

      dec++;
      if(c == '\\') {
	esc = true;
      }
    }
    std::cout << tot << " " << dec << " " << enc << std::endl;
    ans1 = tot-dec;
    ans2 = enc-tot;
  }

  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
