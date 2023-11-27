#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

// Motivated by:
//
// https://stackoverflow.com/questions/8498300/allow-for-range-based-for-with-enum-classes

namespace iterable {

/**
 * @brief Erase elements from a container while iterating over it in a random
 * order.
 *
 * @tparam T Type of the elements in the container.
 */
template <typename T>
class random_iterator_eraser {
 public:
  class Iterator {
   public:
    explicit Iterator(std::vector<T>& p_pool) : pool_{p_pool} {
      if (!pool_.get().empty()) {
        shuffle_pool();
        current_ = pool_.get().begin();
      }
    }

    Iterator& operator++() {
      if (!pool_.get().empty()) {
        pool_.get().erase(current_);
        shuffle_pool();
        current_ = pool_.get().begin();
      }

      return *this;
    }

    bool operator!=(const Iterator& p_other) const {
      return pool_.get().begin() != p_other.pool_.get().end();
    }

    const T& operator*() const { return *current_; }

   private:
    void shuffle_pool() {
      std::random_device random_device;
      std::mt19937 marsenne_twister(random_device());
      std::shuffle(pool_.get().begin(), pool_.get().end(), marsenne_twister);
    }

    std::reference_wrapper<std::vector<T>> pool_;
    typename std::vector<T>::iterator current_;
  };

  Iterator begin() { return Iterator{std::ref(pool_)}; }

  Iterator end() { return Iterator{std::ref(pool_)}; }

  random_iterator_eraser(std::initializer_list<T> args) : pool_{args} {};

  void insert(T p_item) { pool_.insert(std::move(p_item)); }

  std::vector<T> pool() const { return pool_; }

 private:
  std::vector<T> pool_;  // Is random accessible container
};

}  // namespace iterable

namespace data {

class item {
 public:
  enum class type { a, b, c };

  item() : m_type{type::a} {}
  explicit item(type p_type) : m_type{p_type} {}

  explicit operator type() const { return m_type; }

  std::string to_string() const {
    switch (m_type) {
      case data::item::type::a:
        return "a";
      case data::item::type::b:
        return "b";
      case data::item::type::c:
        return "c";
      default:
        return "unknown";
    }
  }

 private:
  type m_type;
};

}  // namespace data

namespace std {

// Specialize std::hash for data::item to remove compiler error.
template <>
struct hash<data::item> {
  std::size_t operator()(const data::item& p_item) const {
    return std::hash<data::item::type>{}(p_item.operator data::item::type());
  }
};

}  // namespace std

int main() {
  std::cout << "iterable::random\n";

  for (const auto& value : iterable::random_iterator_eraser<data::item>{
           data::item{},                     //
           data::item{},                     //
           data::item{data::item::type::b},  //
           data::item{data::item::type::c},  //
           data::item{}                      //
       }) {
    std::cout << value.to_string() << "\n";
  }

  iterable::random_iterator_eraser<data::item> iterate_and_erase{
      data::item{},                     //
      data::item{},                     //
      data::item{data::item::type::b},  //
      data::item{data::item::type::c},  //
      data::item{}                      //
  };

  std::cout << "Before iterate and erase ( size = "
            << iterate_and_erase.pool().size() << " )\n";

  for (const auto& value : iterate_and_erase) {
    std::cout << value.to_string() << "\n";
  }

  std::cout << "After iterate and erase ( size = "
            << iterate_and_erase.pool().size() << " )\n";

  return 0;
}
