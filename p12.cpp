#include <iostream>
#include <stack>

int main() {
  int ans1 = 0;
  int ans2 = 0;

  {
    bool done = false;
    bool innum = false;
    int num = 0;
    bool neg = false;
    std::string tmp;
    std::stack<bool> red;
    std::stack<int> st;
    st.push(0);
    red.push(false);
    while(!done) {
      char c;
      std::cin.get(c);
      if(!std::cin.good()) {
	done = true;
	c = '\n';
      }
      
      if(c == '[') {
	red.push(false);
	st.push(0);
      }
      if(c == '{') {
	red.push(false);
	st.push(0);
      }

      if(c >= 'a' && c <= 'z') {
	tmp.push_back(c);
      } else {
	if(tmp == "red") {
	  red.top() = true;
	}
	tmp.clear();
      }
      
      if(c >= '0' && c <= '9') {
	innum = true;
	num *= 10;
	num += c - '0';
      } else if(!innum && c == '-') {
	innum = true;
	neg = true;
      } else {
	if(innum) {
	  ans1 += (neg?-1:1)*num;
	  st.top() += (neg?-1:1)*num;
	  num = 0;
	}
	neg = innum = false;
      }      

      if(c == ']') {
	red.pop();
	auto tmp = st.top();
	st.pop();
	st.top() += tmp;
      }
      
      if(c == '}') {
	auto tmp = (red.top() ? 0 : st.top());
	red.pop();
	st.pop();
	st.top() += tmp;	
      }
      
    }
    
    while(!st.empty()) {
      if(!red.top()) 
	ans2 += st.top();
      st.pop();
    }
  }
  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
