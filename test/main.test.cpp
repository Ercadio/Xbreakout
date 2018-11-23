#include <iostream>
#include <queue>
#include <functional>
#include <exception>

using namespace std;

queue<queue<function<bool()> > > suites;

int main() {
  cout << "\n\e[48;5;206m[Breakout Tests]\e[0m\n"
          "Suites:\t" << suites.size();
  int failed, errors, total;
  while(not suites.empty()) {
    auto suite = suites.front();
    suites.pop();
    total += suite.size();
    while(not suite.empty()) {
      auto test = suite.front();
      suite.pop();
      int result;
      try {
        result = test();
        failed += result;
        if(result) {
          cout << "Failed a test...\n";
        }
      } catch (exception& e) {
        cout << e.what() << endl;
        ++errors;
      }
    }
  }

  cout << total << "Tests completed [" << errors << " errors, " << 
    failed << " failures, " << (total - errors - failed) << " passed]\n";
}
