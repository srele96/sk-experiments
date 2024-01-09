#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// https://www.learncpp.com/cpp-tutorial/circular-dependency-issues-with-stdshared_ptr-and-stdweak_ptr/

namespace One {

class Node : public std::enable_shared_from_this<Node> {
  struct Private {
    // Test members
    int m_a0{0};
    int m_a1{1};
    int m_a2{2};
  };

 public:
  explicit Node(Private p_private) {}

  // explicit Node(Private p_private) {}
  static std::shared_ptr<Node> Create() {
    return std::make_shared<Node>(Private{});
  }

  static void UsePrivateTypeInstance(const std::function<void(Private)>& cb_) {
    cb_(Private{});  // Oopsie... we pass the instance, but not the type.
  }
};

}  // namespace One

namespace Two {

template <typename T>
class Observer {
 public:
  virtual void Update(const T& p_subject) = 0;
  virtual ~Observer() = default;
};

template <typename T>
class Subject {
 public:
  virtual void AttachObserver(std::shared_ptr<Observer<T>> p_observer) = 0;
  virtual void NotifyObservers() = 0;
  virtual ~Subject() = default;
};

class Stock : public Subject<Stock> {
 private:
  std::vector<std::weak_ptr<Observer<Stock>>> m_observers;

  std::string m_name;
  double m_price;

  void NotifyObservers() override {
    for (const std::weak_ptr<Observer<Stock>>& observer : m_observers) {
      if (std::shared_ptr<Observer<Stock>> ptr = observer.lock()) {
        ptr->Update(*this);
      }
    }
  }

 public:
  Stock(std::string p_name, double p_price)
      : m_name{std::move(p_name)}, m_price{p_price} {}

  void AttachObserver(std::shared_ptr<Observer<Stock>> p_observer) override {
    m_observers.push_back(p_observer);
  }

  double Price() const { return m_price; }
  void Price(double p_price) {
    m_price = p_price;
    NotifyObservers();
  }

  std::string Name() const { return m_name; }
  void Name(std::string p_name) {
    m_name = std::move(p_name);
    NotifyObservers();
  }

  std::string ToString() const {
    return m_name + " is " + std::to_string(m_price);
  }
};

class StockAlert : public Observer<Stock> {
 private:
  std::reference_wrapper<std::ostream> m_out;

 public:
  explicit StockAlert(std::ostream& p_out) : m_out{p_out} {}

  void Update(const Stock& p_subject) override {
    m_out.get() << "(StockAlert): " << p_subject.ToString() << "\n";
  }
};

}  // namespace Two

namespace Three {}

int main() {
  std::shared_ptr<One::Node> node0{One::Node::Create()};
  std::shared_ptr<One::Node> node1{node0->shared_from_this()};
  std::shared_ptr<One::Node> node2{node1->shared_from_this()};

  // std::weak_ptr<One::Node> node2{node0->GetPtr()};

  // One::Node node;  // Error

  // Two::Node node;

  One::Node::UsePrivateTypeInstance([](auto privateTypeInstance) {
    using PrivateType = decltype(privateTypeInstance);

    PrivateType useDeducedPrivateType;
    std::cout << "( m_a0 = " << useDeducedPrivateType.m_a0
              << " , m_a1 = " << useDeducedPrivateType.m_a1
              << " , m_a2 = " << useDeducedPrivateType.m_a2 << " )\n";
  });

  std::vector<std::weak_ptr<One::Node>> nodes;

  nodes.push_back(One::Node::Create());
  nodes.push_back(One::Node::Create());
  nodes.push_back(One::Node::Create());

  {
    nodes.push_back(One::Node::Create());
    nodes.push_back(One::Node::Create());
  }

  nodes.push_back(One::Node::Create());

  nodes.push_back(node0);

  for (const std::weak_ptr<One::Node>& node : nodes) {
    if (std::shared_ptr<One::Node> ptr = node.lock()) {
      std::cout << "Node is valid\n";
    } else {
      std::cout << "Node is invalid\n";
    }
  }

  std::cout << "Done\n";

  // https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
  // https://en.cppreference.com/w/cpp/memory/shared_ptr
  // https://stackoverflow.com/questions/38855343/create-shared-ptr-to-stack-object

  const std::string stockName1{"AAPL"};
  const std::string stockName2{"MSFT"};
  const std::string stockName3{"GOOG"};
  constexpr double stockPrice1{318.65};
  constexpr double stockPrice2{166.86};
  constexpr double stockPrice3{1480.20};

  std::vector<std::shared_ptr<Two::Stock>> stocks;

  stocks.push_back(std::make_shared<Two::Stock>(stockName1, stockPrice1));
  stocks.push_back(std::make_shared<Two::Stock>(stockName2, stockPrice2));
  stocks.push_back(std::make_shared<Two::Stock>(stockName3, stockPrice3));

  std::shared_ptr<Two::StockAlert> alertLog{
      std::make_shared<Two::StockAlert>(std::cout)};
  std::shared_ptr<Two::StockAlert> alertError{
      std::make_shared<Two::StockAlert>(std::cerr)};

  for (const std::shared_ptr<Two::Stock>& stock : stocks) {
    stock->AttachObserver(alertLog);
    stock->AttachObserver(alertError);
  }

  for (const std::shared_ptr<Two::Stock>& stock : stocks) {
    constexpr double magnify{1.1};
    stock->Price(stock->Price() * magnify);
  }

  return 0;
}
