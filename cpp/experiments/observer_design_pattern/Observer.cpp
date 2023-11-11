#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace ObserverDesignPattern {

// Problem: Stock Price Alert System
//
// Description:
//
// You are tasked with designing a stock price alert system using the Observer
// design pattern in C++. The system will have the following components:
//
//     - Stock: This class represents a stock in the market. It should have
//     attributes like stock name and price.
//     - StockMarket: This class manages a collection of Stock objects. It
//     should allow adding and updating stock prices.
//     - Observer Interface: This interface should define the method that all
//     observers must implement to receive updates.
//     - DisplayBoard and AlertSystem: Two concrete classes that implement the
//     Observer interface. DisplayBoard displays the latest stock prices, and
//     AlertSystem sends alerts when a stock price reaches a certain threshold.
//
// Requirements:
//
//     - Implement an Observer interface with an update() method.
//     - Stock should be a class with properties for the name and price of the
//     stock. It should notify all observers whenever its price changes.
//     - StockMarket should be able to add new stocks and update the prices of
//     existing stocks.
//     - DisplayBoard and AlertSystem should both implement the Observer
//     interface. DisplayBoard should display the latest prices of stocks, and
//     AlertSystem should check for price thresholds and send alerts.
//     - The system should support multiple DisplayBoard and AlertSystem
//     instances observing the same stocks.
//     - When the price of a stock changes, all registered observers should be
//     notified.
//
// Example:
//
// Suppose the StockMarket has two stocks: Apple (AAPL) and Google (GOOGL). Two
// DisplayBoard instances and one AlertSystem are observing these stocks. When
// the price of Apple stock changes, both DisplayBoard instances should update
// the display, and the AlertSystem should check if the new price crosses a
// predefined threshold and, if so, trigger an alert.

class Stock;

// However, this rule does not always apply neatly to abstract classes
// (interfaces) in C++, especially when you're dealing with polymorphic base
// classes like IObserver and ISubject in your case. These classes are designed
// to be interfaces, providing a contract for derived classes rather than
// holding or managing resources themselves.
//
// Interfaces Are Not Meant to Be Copied: Interface classes are generally not
// meant to be copied or moved. They represent an interface, not a data
// structure. The purpose of these classes is to be inherited by other classes
// that implement the interface, not to hold data or resources that would need
// to be copied or moved.
//
// In conclusion, for your IObserver and ISubject classes, it's perfectly fine
// to define only a virtual destructor and rely on the default copy/move
// constructors and assignment operators provided by the compiler, especially
// since they are meant to be used as interfaces. The Clang-Tidy warning is more
// of a general guideline and may not apply to every situation, particularly in
// cases involving polymorphic base classes like yours.

class IObserver {
 public:
  virtual void OnUpdate(const Stock &stock) = 0;
  virtual ~IObserver() = default;
};

class ISubject {
 public:
  virtual void AddObserver(const std::shared_ptr<IObserver> &observer) = 0;
  virtual void NotifyObservers() = 0;
  virtual ~ISubject() = default;
};

class Stock : public ISubject {
 private:
  static int IDCounter;

  int id_;
  int price_;
  std::string name_;

  std::vector<std::weak_ptr<IObserver>> observers_;

 public:
  Stock() : id_{IDCounter++} {}
  Stock(std::string name, int price)
      : id_{IDCounter++}, name_{std::move(name)}, price_{price} {}

  auto ID() const -> int { return id_; }

  void Name(std::string name) { name_ = std::move(name); }

  auto Name() const -> std::string { return name_; }

  void Price(int price) {
    price_ = price;
    NotifyObservers();
  }

  auto Price() const -> int { return price_; }

  void AddObserver(const std::shared_ptr<IObserver> &observer) override {
    observers_.push_back(observer);
  }

  void NotifyObservers() override {
    for (std::weak_ptr<IObserver> &observer : observers_) {
      if (std::shared_ptr<IObserver> ptr_observer = observer.lock()) {
        ptr_observer->OnUpdate(*this);
      }
    }
  }

  // Thanks to the observable pattern we can observe constructing, copying,
  // moving, assigning, destroying, etc... of the Stock class.
};

constexpr int InitialIDCounter = 1;
int Stock::IDCounter = InitialIDCounter;

class DisplayBoard : public IObserver {
 private:
  std::reference_wrapper<std::ostream> display_;

 public:
  explicit DisplayBoard(std::ostream &display) : display_{display} {}

  void OnUpdate(const Stock &stock) override {
    display_.get() << stock.ID() << ": " << stock.Name() << " - "
                   << stock.Price() << "\n";
  }
};

class AlertSystem : public IObserver {
 private:
  int threshold_;
  std::reference_wrapper<std::ostream> out_;

 public:
  AlertSystem(int threshold, std::ostream &out)
      : threshold_{threshold}, out_{out} {}

  void OnUpdate(const Stock &stock) override {
    if (stock.Price() > threshold_) {
      out_.get() << stock.ID() << ": "
                 << "(Alert!) " << stock.Name() << " - " << stock.Price()
                 << "\n";
    }
  }
};

class StockMarket {
 private:
  std::vector<Stock> stocks_;

 public:
  void AddStock(const Stock &stock) { stocks_.push_back(stock); }

  void RemoveStock(const std::function<bool(const Stock &)> &predicate) {
    stocks_.erase(std::remove_if(stocks_.begin(), stocks_.end(), predicate),
                  stocks_.end());
  }

  void UpdateStock(const std::function<void(Stock &)> &callback) {
    for (auto &stock : stocks_) {
      callback(stock);
    }
  }
};

void RunStockMarket() {
  std::vector<std::unique_ptr<Stock>> stocks;
  constexpr int appleStockPrice{100};
  constexpr int googleStockPrice{200};
  stocks.push_back(std::make_unique<Stock>("Apple", appleStockPrice));
  stocks.push_back(std::make_unique<Stock>("Google", googleStockPrice));

  std::shared_ptr<IObserver> displayToCout{
      std::make_shared<DisplayBoard>(std::cout)};
  std::shared_ptr<IObserver> displayToCerr{
      std::make_shared<DisplayBoard>(std::cerr)};

  constexpr int threshold{150};
  std::shared_ptr<IObserver> alertSystem{
      std::make_shared<AlertSystem>(threshold, std::cout)};

  StockMarket stockMarket;

  for (std::unique_ptr<Stock> &stock : stocks) {
    stock->AddObserver(displayToCout);
    stock->AddObserver(displayToCerr);
    stock->AddObserver(alertSystem);

    stockMarket.AddStock(*stock);
  }

  stockMarket.UpdateStock([&stocks](Stock &stock) {
    if (stock.ID() == stocks[0]->ID()) {
      constexpr int newPrice{150};
      stock.Price(newPrice);
    }
  });

  stockMarket.UpdateStock([&stocks](Stock &stock) {
    if (stock.ID() == stocks[0]->ID()) {
      constexpr int newPrice{200};
      stock.Price(newPrice);
    }
  });

  stockMarket.RemoveStock(
      [&stocks](const Stock &stock) { return stock.ID() == 1; });

  stockMarket.UpdateStock([&stocks](Stock &stock) {
    if (stock.ID() == stocks[1]->ID()) {
      constexpr int newPrice{250};
      stock.Price(newPrice);
    }
  });
}

}  // namespace ObserverDesignPattern

auto main() -> int {
  ObserverDesignPattern::RunStockMarket();

  return 0;
}
