#include <functional>
using namespace std;

// https://leetcode.com/problems/merge-two-sorted-lists/

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* head = nullptr;
    function<void(ListNode*&, ListNode*, ListNode*)> solve{
        [&solve](ListNode*& h, ListNode* l1, ListNode* l2) {
          if (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
              h = new ListNode(l1->val);
              solve(h->next, l1->next, l2);
            } else {
              h = new ListNode(l2->val);
              solve(h->next, l1, l2->next);
            }
          } else if (l1 != nullptr) {
            h = new ListNode(l1->val);
            solve(h->next, l1->next, l2);
          } else if (l2 != nullptr) {
            h = new ListNode(l2->val);
            solve(h->next, l1, l2->next);
          }
        }};

    solve(head, list1, list2);

    return head;
  }
};
