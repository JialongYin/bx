int fds[4000];
int output;
for (int i = 0; i < 4000; ++i) {
  fds[i] = open(to_string(i)+".csv");
}
double parse(const string &time) {
  vector<int> units{3600*10^6, 60*10^6, 10^6};
  int pos = time.find('.');
  double ret = stol(time.substr(pos+1));
  time = time.substr(0, pos);
  int i = 0;
  while ((pos = time.find(':')) != -1) {
    ret += stol(time.substr(0, pos)) * units[i];
    time = time.substr(pos+1);
    ++i;
  }
  return ret;
}
// HH:MM:SS.******
output = open("output.csv");
priority_queue<tuple<unsigned long, string, int>, vector<tuple<unsigned long, string, int>>, greater<tuple<unsigned long, string, int>>> hp;
string line;
for (int i = 0; i < 4000; ++i) {
  line = getline(fds[i]);
  int pos = line.find(',');
  double key = parse(line.substr(0, pos));
  hp.push(make_tuple(key, move(line), i));
}
int fd;
while (!hp.empty()) {
  auto &time_line = hp.top();
  line = move(time_line[1]);
  write(output, line, line.size());
  fd = move(time_line[2]);
  hp.pop();
  if (line = getline(fd)) {
    double key = parse(line);
    hp.push(make_tuple(key, move(line), fd));
  }
}



















class Base {
  int count = 0;
  double price_avg = 0;
  vector<double> prices;
  // double func(double price);
  double complexCompute();
  void onData(double price);
};

// double Base::func(double price) {
//   ++count;
//   price_avg = price_avg * ((count-1) / count) + price * 1 / count;
//   return price_avg;
// }

void onData(double price) {
    prices.push_back(price);
}

double Base::complexCompute() {
    double ret = 0;
    for (auto &p: prices) {
      ret += sqrt(p);
    }
    return ret;
}
