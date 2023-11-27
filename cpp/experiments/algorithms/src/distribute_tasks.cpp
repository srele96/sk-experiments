#include <bits/stdc++.h>
using namespace std;

vector<pair<int, vector<int>>> distribute_tasks(
    const vector<vector<int>>& employees, const vector<vector<int>>& tasks) {
  // Also works... But instantiating something of type deduced from this lambda,
  // where's the implementation? When deducing a type, it's missing an
  // implementation, however when I create a struct it can instantiate an object
  // that has implemented operator... Pff!

  // auto comp = [](const pair<int, int>& a, const pair<int, int>& b) {
  //   return a.second < b.second;
  // };
  // vector<priority_queue<pair<int, int>, vector<pair<int, int>,
  // decltype(comp)>>>
  //     graph(tasks.size());

  // Does not work...

  // function<bool(const pair<int, int>&, const pair<int, int>&)> comp{
  //     [](const pair<int, int>& a, const pair<int, int>& b) {
  //       return a.second < b.second;
  //     }};
  // vector<
  //   priority_queue<
  //     pair<int, int>,
  //     vector<pair<int, int>>,
  //     function<bool(const pair<int, int>&, const pair<int, int>&)>
  //   >
  // > graph(tasks.size(), comp);

  // struct Comp {
  //   bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
  //     return a.second < b.second;
  //   }
  // };
  // vector<priority_queue<pair<int, int>, vector<pair<int, int>>, Comp>> graph(
  //     tasks.size());

  // That worked... My comparison function did not work... Why?
  vector<priority_queue<pair<int, int>>> graph(tasks.size());

  for (int i = 0; i < tasks.size(); ++i) {
    for (int j = 0; j < employees.size(); ++j) {
      bool can_complete_task{true};

      unordered_set<int> skills;
      for (const int skill : employees[j]) {
        skills.insert(skill);
      }
      for (const int skill : tasks[i]) {
        const bool has_no_skill = skills.count(skill) == 0;
        if (has_no_skill) {
          can_complete_task = false;
        }
      }

      if (can_complete_task) {
        graph[i].push({0, j});
      }
    }
  }

  vector<pair<int, vector<int>>> result(employees.size());
  for (int i = 0; i < result.size(); ++i) {
    result[i].first = i;
  }

  for (int i = 0; i < graph.size(); ++i) {
    pair<int, int> employee =
        graph[i].top();       // Take employee with lowest capacity
    ++employee.first;         // Increase tasks
    graph[i].push(employee);  // Reorder
    result[employee.second].second.push_back(i);  // Assign task
  }

  return result;
}

void print(const vector<pair<int, vector<int>>>& pairs) {
  for (pair<int, vector<int>> p : pairs) {
    cout << p.first << "\n";
    if (p.second.size() == 0) {
      cout << "None";
    }
    for (const int task : p.second) {
      cout << task << " ";
    }
    cout << "\n";
  }
}

int main() {
  const vector<pair<vector<vector<int>>, vector<vector<int>>>> tests{
      {
          {{1}, {2}, {3}, {4}, {5}},  // Employees with skills
          {{1}, {2}, {3}}             // Tasks with skills
      },                              //
      {
          {{1, 2}, {3}, {1}},  // Employees with skills
          {{1}, {2}},          // Tasks with skills
      },                       //
      {
          {{1, 2, 3}, {4}, {5}},               // Employees with skills
          {{1}, {1, 2}, {1, 2, 3}, {4}, {5}},  // Tasks with skills
      },                                       //
      {
          {{1, 2, 3}, {1}, {2}, {3}},  // Employees with skills
          {{1}, {2}, {3}, {1}},        // Tasks with skills
      },                               //
  };

  for (const pair<vector<vector<int>>, vector<vector<int>>>& test : tests) {
    cout << "----\n";
    print(distribute_tasks(test.first, test.second));
    cout << "----";
  }

  return 0;
}
