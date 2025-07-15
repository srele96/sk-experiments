#include <unordered_set>
using namespace std;

// Seems like the most optimal solution and worthy of further discovery

// https://stackoverflow.com/questions/494830/how-to-determine-if-a-linked-list-has-a-cycle-using-only-two-memory-locations

// https://en.wikipedia.org/wiki/Cycle_detection#Tortoise_and_hare

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
};

namespace a {

class Solution {
 public:
  // hah! ridiculous! if there's loop iterate until the largest input + 1
  // meaning that there's a loop, lmao
  int end = 0;
  bool hasCycle(ListNode* head) {
    while (head != nullptr) {
      if (end > 10e4) return true;
      ++end;
      head = head->next;
    }
    return false;
  }
};

}  // namespace a

namespace b {

class Solution {
 public:
  unordered_set<ListNode*> us;
  bool hasCycle(ListNode* head) {
    while (head != nullptr) {
      if (us.count(head) != 0) return true;
      us.insert(head);
      head = head->next;
    }
    return false;
  }
};

}  // namespace b

namespace c {

class Solution {
 public:
  bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    int i = 0;
    while (true) {
      if (fast == nullptr) return false;
      fast = fast->next;
      if (i % 2 != 0) slow = slow->next;
      if (slow == fast) return true;
      ++i;
    }
    return false;
  }
};

}  // namespace c

namespace d {

class Solution {
 public:
  bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (true) {
      // head can be nullptr
      if (fast == nullptr) return false;
      // allows us to use `fast->next->next`
      if (fast->next == nullptr) return false;
      // bloody hell, the goal was not to iterate incrementally but to find
      // cycle
      slow = slow->next;
      fast = fast->next->next;

      // as it is, has to be last, because initially these two point to the same
      // thing
      if (slow == fast) return true;
    }
    return false;
  }
};

}  // namespace d
