namespace A {

enum Day { sun, mon, tue, wed, thu, fri, sat };

Day& next(Day& d) {
  d = d == sat ? sun : static_cast<Day>(d + 1);

  return d;
}

Day& operator++(Day& d) { return next(d); }

Day& operator++(Day& d, int) { return next(d); }

}  // namespace A

namespace B {

enum class Day { sun, mon, tue, wed, thu, fri, sat };

Day& next(Day& d) {
  d = d == Day::sat ? Day::sun : static_cast<Day>(static_cast<int>(d) + 1);

  return d;
}

Day& operator++(Day& d) { return next(d); }

Day& operator++(Day& d, int) { return next(d); }

}  // namespace B

int main() {
  {
    A::Day today{A::Day::tue};
    ++today;
    today++;
  }

  {
    B::Day today{B::Day::wed};
    ++today;
    today++;
  }

  return 0;
}
