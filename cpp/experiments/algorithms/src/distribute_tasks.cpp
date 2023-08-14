#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<vector<int>> employees{{1}, {2}, {3}, {4}, {5}};
  vector<vector<int>> tasks{{1}, {2}, {3}};
  vector<vector<int>> graph(tasks.size());

  for (int i = 0; i < tasks.size(); ++i) {
    for (int j = 0; j < employees.size(); ++j) {
      bool can_complete_task{true};

      unordered_set<int> skills;
      for (const int skill : tasks[i]) {
        skills.insert(skill);
      }
      for (const int skill : employees[j]) {
        const bool has_no_skill = skills.count(skill) == 0;
        if (has_no_skill) {
          can_complete_task = false;
        }
      }

      if (can_complete_task) {
        graph[i].push_back(j);
      }
    }
  }

  vector<pair<int, vector<int>>> result(
      employees.size());  // find a way to initialize vector with a callback or
                          // something...
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; i < graph[i].size(); ++j) {
      // employees that can complete that task
      // distribute to the employee that can complete the task and has the
      // lowest amount of tasks for each task there are employees... what if a
      // graph contains a queue to employees, i don't have a way to track
      // employees with the queue...
      // ...
    }
  }

  return 0;
}
