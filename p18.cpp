#include <iostream>
#include <array>

int main() {
  int ans1 = 0;
  int ans2 = 0;

  constexpr int SIZE = 100;
  constexpr int ITER = 100;
  
  std::array<std::array<bool, SIZE>, SIZE> start;
  for(auto & row : start) {
    for(auto & c : row) c = false;
  }

  {
    bool done = false;
    int row = 0;
    int col = 0;
    while(!done) {
      char c;
      std::cin.get(c);
      if(!std::cin.good()) {
	done = true;
	c = '\n';
      }
      if(c == '.' || c == '#') {
	start[row][col++] = (c == '#');
      } else if(c == '\n') {
	if(col != 0) {
	  if(col != SIZE) std::cout << "row " << row << " has length " << col << std::endl;
	  col = 0;
	  row++;
	}
      }
    }

    if(row != SIZE || col != 0) {
      std::cout << "unexpected row " << row << " col " << col << std::endl;
    }
  }

  for(int prob = 0; prob < 2; prob++) {
    auto arr = start;
    if(prob == 1) {
      arr[0][0] = true;
      arr[0][SIZE-1] = true;
      arr[SIZE-1][0] = true;
      arr[SIZE-1][SIZE-1] = true;
    }
    for(int i = 0; i < ITER; i++) {
      decltype(arr) next;
      
      for(int r = 0; r < arr.size(); r++) {
	for(int c = 0; c < arr[r].size(); c++) {
	  int cnt = 0;
	  for(int dr = -1; dr < 2; dr++) {
	    if((r+dr < 0) || (r+dr >= arr.size())) continue;
	    for(int dc = -1; dc < 2; dc++) {
	      if(dr == 0 && dc == 0) continue;
	      if((c+dc < 0) || (c+dc >= arr.size())) continue;
	      if(arr[r+dr][c+dc]) cnt++;
	    }
	  }
	  if(arr[r][c] && (cnt == 2 || cnt == 3)) next[r][c] = true;
	  else if(!arr[r][c] && cnt == 3) next[r][c] = true;
	  else next[r][c] = false;
	}
      }

      if(prob == 1) {
	next[0][0] = true;
	next[0][SIZE-1] = true;
	next[SIZE-1][0] = true;
	next[SIZE-1][SIZE-1] = true;
      }      
      
      std::swap(next, arr);
    }
    
    for(const auto & row : arr) {
      for(const auto & b : row) {
	if(prob == 0 && b) ans1++;
	if(prob == 1 && b) ans2++;
      }
    }
  }

  
  std::cout << ans1 << std::endl;
  std::cout << ans2 << std::endl;
}
