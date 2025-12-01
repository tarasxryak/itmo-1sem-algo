#include <iostream>
#include <vector>

std::vector<std::vector<bool> > warshal(int n, std::vector<std::pair<int, int> >& edge) {
  std::vector<std::vector<bool> > dist(n, std::vector<bool>(n, false));

  for (int i = 0; i < n; ++i) {
    dist[i][i] = true;
  }

  for (const auto& el : edge) {
    dist[el.first][el.second] = true;
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        if (dist[k][j] && dist[i][k]) {
          dist[i][j] = true;
        }
      }
    }
  }
  return dist;
}

int main() {
  int n;
  std::cin >> n;

  std::vector<std::pair<int, int> > matrix(n, {0, 0});
  for (int i = 0; i < n; ++i) {
    std::cin >> matrix[i].first >> matrix[i].second;
  }
}



