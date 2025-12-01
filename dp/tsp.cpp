#include <vector>
#include <limits>
#include <iostream>
#include <cmath>

std::vector<int> find_nearest(const std::vector<std::vector<double>>& dist, int start = 0) {
  int n = dist.size();
  std::vector<bool> visited(n, false);
  std::vector<int> path;

  path.push_back(start);
  visited[start] = true;
  int cur = start;

  for (int i = 0; i < n - 1; ++i) {
    int next_town = -1;
    double min_dist = std::numeric_limits<double>::max();

    for (int j = 0; j < n; ++j) {
      if (!visited[j] && dist[cur][j] < min_dist) {
        min_dist = dist[cur][j];
        next_town = j;
      }
    }

    if (next_town == -1) break;

    path.push_back(next_town);
    visited[next_town] = true;
    cur = next_town;
  }

  path.push_back(start);

  return path;
}

double find_len(const std::vector<int>& path, const std::vector<std::vector<double>>& dist) {
  double len = 0.0;
  for (size_t i = 0; i < path.size() - 1; ++i) {
    len += dist[path[i]][path[i + 1]];
  }
  return len;
}

int main() {

  std::vector<std::pair<double, double>> towns = {
    {0, 0},
    {1, 3},
    {4, 2},
    {3, 0},
    {2, 4}
  };

  int n = towns.size();
  std::vector<std::vector<double>> dists(n, std::vector<double>(n, 0.0));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      double dx = towns[i].first - towns[j].first;
      double dy = towns[i].second - towns[j].second;
      dists[i][j] = std::sqrt(dx * dx + dy * dy);
    }
  }

  std::cout << "Матрица расстояний: " << std::endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << dists[i][j] << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  for (int i = 0; i < n; ++i) {
    std::vector<int> path = find_nearest(dists, i);
    double len = find_len(path, dists);

    std::cout << "Старт из города: " << i << std::endl;
    std::cout << "Путь: ";
    for (int& city : path) {
      std::cout << city << ' ';
    }
    std::cout << '\n';
    std::cout << "Длина: " << len << std::endl << std::endl;
  }

  return 0;
}