#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

//конвертация индекса в название курса
std::string name_by_value(const std::unordered_map<std::string, int> &map,int value) 
{
  for (const auto &pair : map) {
    if (pair.second == value)
      return pair.first;
  }
  return "";
}
//для проверки на циклы
void dfs(int i, const std::vector<std::vector<int>> &graph, std::vector<int> &used) 
{
  used[i] = 1;
  for (int u : graph[i]) {
    if (used[u] == 0) {
      dfs(u, graph, used);
    } else if (used[u] == 1)
      throw std::runtime_error("There՞s unavalible sequence of courses :(");
  }
  used[i] = 2;
}
//перый ввод 
std::pair<std::vector<std::vector<int>>, std::unordered_map<std::string, int>> input(int n, int m) 
{
  std::string name;
  std::vector<std::vector<int>> graph(n);
  std::unordered_map<std::string, int> match(n); //граф для соответствия названия курса и индекса
  std::cout << "Enter courses: ";
  for (int i = 0; i < n; i++) {

    std::cin >> name; //ввод названия курса
    match[name] = i;  //соответствие вершине
  }
  std::cout << "Enter dependences: ";
  while (m--) {
    std::string n1, n2;

    std::cin >> n1 >> n2; //ввод зависимостей между курсами
    int v = match[n1];     //индекс 1 курса
    int u = match[n2];     //индекс 2 курса
    graph[v].push_back(u); //создание графа смежности
  }
//проверка на циклы
  std::vector<int> visited(n);
  for (int i = 0; i < n; i++) {
    if (!visited[i])
      dfs(i, graph, visited);
  }
//для return
  std::pair<std::vector<std::vector<int>>, std::unordered_map<std::string, int>> pairs;
  pairs.first = graph;
  pairs.second = match;
  return pairs;
}

//вывод
void output(std::vector<int> &sort_result,
            std::unordered_map<std::string, int> &match) {
  for (int el : sort_result)
    std::cout << name_by_value(match, el) << " ";
}

void dfs_with_order(int i, const std::vector<std::vector<int>> &graph, std::vector<char> &used, std::vector<int> &v) 
{
  used[i] = true;
  for (int u : graph[i]) {
    if (!used[u]) {
      dfs_with_order(u, graph, used, v);
    }
  }
  v.push_back(i);
}

std::vector<int> top_sort(const std::vector<std::vector<int>> &graph) 
{
  std::vector<int> v;
  std::vector<char> used(graph.size(), false);

  for (int i = 0; i < used.size(); ++i) {
    if (!used[i])
      dfs_with_order(i, graph, used, v);
  }

  std::reverse(v.begin(), v.end());
  return v;
}

//переворот графа
std::vector<std::vector<int>> reverse_graph(const std::vector<std::vector<int>> &g) 
{
  std::vector<std::vector<int>> rg(g.size());

  for (int v = 0; v < g.size(); ++v) {
    for (int u : g[v])
      rg[u].push_back(v);
  }
  return rg;
}
// SCC
void print_scc(const std::vector<std::vector<int>> &graph, std::unordered_map<std::string, int> &match) 
{
  std::vector<int> v;
  std::vector<char> used(graph.size(), false);

  for (int i = 0; i < used.size(); ++i) {
    if (!used[i])
      dfs_with_order(i, graph, used, v);
  }

  std::reverse(v.begin(), v.end());
  std::vector<std::vector<int>> rg = reverse_graph(graph);

  used.clear();
  used.resize(graph.size(), false);

  int c = 0;
  for (int u : v) {
    if (!used[u]) {
      ++c;
      std::vector<int> component;
      dfs_with_order(u, rg, used, component);
      std::cout << "Components of course " << c << ": ";

      for (int el : component)
        std::cout << name_by_value(match, el) << " ";

      std::cout << std::endl;
    }
  }
}

int main() 
{
  int n; //количество курсов
  int m; //количество зависимостей между курсами
  std::cout << "Enter courses and dependences number: ";
  std::cin >> n >> m;
  //ввод графа
  std::pair<std::vector<std::vector<int>>, std::unordered_map<std::string, int>>
      inputs(input(n, m));
  //сохранение графа
  std::vector<std::vector<int>> graph_res(n);
  std::vector<std::vector<int>> graph_scc(n);
  graph_scc = inputs.first;
  graph_res = inputs.first;

  std::unordered_map<std::string, int> match(n);
  match = inputs.second;

  //вывод последовательности курсов
  std::vector<int> sort_result = top_sort(graph_res);
  std::cout << "The right sequence of courses: ";
  output(sort_result, match);

  //добавление нового курса
  std::string name; //название
  int k;            // количество зависимостей
  std::cout << std::endl
            << std::endl
            << "Enter new course and number of dependences: ";

  while (true) {
    std::cin >> name >> k;
    match[name] = n;
    std::vector<int> v(k);
    graph_scc.push_back(v);
    std::vector<int> v1(0);
    graph_res.push_back(v1);
    ++n;
    std::cout << "Enter new dependency: ";
    while (k--) {
      std::string n1, n2;
      std::cin >> n1 >> n2; //ввод зависимостей между курсами
      int v = match[n1];         //индекс 1 курса
      int u = match[n2];         //индекс 2 курса
      graph_res[v].push_back(u); //создание графа смежности
      graph_scc[v].push_back(u); //создание графа смежности
    }
//проверка на циклы
    std::vector<int> visited(n);
    for (int i = 0; i < n; i++) {
      if (!visited[i])
        dfs(i, graph_res, visited);
    }
//сортировки и вывод
    sort_result = top_sort(graph_res);
    std::cout << "The right sequence of courses: ";
    output(sort_result, match);
    std::cout << std::endl;
    print_scc(graph_scc, match);
    std::cout << std::endl << std::endl << "Enter new course and number of dependences: ";
  }
}