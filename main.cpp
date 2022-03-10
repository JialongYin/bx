#include <string>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <iterator>
#include <vector>
#include <fstream>
using namespace std;

bool dfs(double tradeSum, unsigned node, unsigned par, map<unsigned, double> &path, set<unsigned> &visited, map<unsigned, map<unsigned, unsigned>> &tradeRule) {
  path[node] = tradeSum;
  for (auto const &neighborTimes: tradeRule[node]) {
    unsigned neighbor = neighborTimes.first;
    double times = neighborTimes.second;
    if (neighbor != par && visited.find(neighbor) == visited.end()) {
      if (times == 0) times = (double) 1 / tradeRule[neighbor][node];
      if (path.find(neighbor) == path.end()) {
        if (dfs(tradeSum*times, neighbor, node, path, visited, tradeRule)) return true;
      }
      else {
        if (abs(tradeSum*times - path[neighbor]) > 0.01) return true;
      }
    }
  }
  visited.insert(node);
  path.erase(node);
  return false;
}

int main() {
  string str;
  ifstream infile("sample_input.txt");
  // getline(cin,str);
  getline(infile,str);
  unsigned pos = str.find(" ");
  unsigned M = stoul(str.substr(0, pos));
  unsigned N = stoul(str.substr(pos+1));

  map<unsigned, map<unsigned, unsigned>> tradeRule;

  for (unsigned i = 0; i < N; ++i) {
    // getline(cin,str);
    getline(infile,str);
    stringstream ss(str);
    istream_iterator<string> begin_i(ss);
    istream_iterator<string> end_i;
    vector<string> vstrings(begin_i, end_i);
    unsigned x = stoul(vstrings[0]), y = stoul(vstrings[1]), z = stoul(vstrings[2]);
    tradeRule[x][y] = z;
    tradeRule[y][x] = 0;
  }

  double tradeSum = 1;
  set<unsigned> visited;
  map<unsigned, double> path;
  unsigned i;
  for (i = 1; i <= M; ++i){
    if (visited.find(i) == visited.end() && dfs(tradeSum, i, 0, path, visited, tradeRule))
        break;
  }
  if (i == M+1)
    cout << "No" << endl;
  else
    cout << "Yes" << endl;
  return 0;
}
