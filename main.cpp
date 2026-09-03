#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

enum Status {
  NO,
  MAYBE,
  YES
};

void draw_table(vector<vector<int>> values) {
  for (int i = 0; i < values[0].size(); i++) {
    for (int j = 0; j < values.size(); j++) {
      if (values[j][i] == 68) {
        cout << " | D";
      }else {
        cout << " | " << values[j][i];
      }
    }
    cout << " |" << endl;
  }
}

void compute_maybe_count(string coords, vector<vector<int>> &maybe_count_mtr) {
  int size_x = maybe_count_mtr.size();
  int size_y = maybe_count_mtr[0].size();
  int curr_x = coords[1] - '0' - 1;
  int curr_y = coords[0] - '0' - 1;
  //36
  maybe_count_mtr[curr_x][curr_y] = (int)'#';
  for (int x_mod = -1; x_mod < 2; x_mod++) {
    for (int y_mod = -1; y_mod < 2; y_mod++) {
      int ind_x = curr_x + x_mod;
      int ind_y = curr_y + y_mod;
      if (ind_x < 0 || ind_x >= size_x || ind_y < 0 || ind_y >= size_y)
        continue;
      if (ind_x == 0 && ind_y == 0)
        continue;
      maybe_count_mtr[curr_x + x_mod][curr_y + y_mod] += 1;
    }
  }
}

int main() {
  while (true) {
    string input;

    int size_x, size_y;
    cout << "Enter height: ";
    cin >> size_y;
    cout << "Enter width: ";
    cin >> size_x;

    vector<vector<int>> maybe_count_mtr(size_x);
    vector<vector<Status>> stat_mtr(size_x);
    unordered_map<string, int> visited_dict;

    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            maybe_count_mtr[i].push_back(0);
        }
    }
    cout << "Enter YXN (D) or exit" << endl;
    while (true) {
      cin >> input;
      if (input == "exit")
        exit(0);
      try {
        if (input[2] == 'D') {
          visited_dict[input.substr(0,2)] = (int)'D';
        }else {
          visited_dict[input.substr(0,2)] = input[2] - '0';
        }
      } 
      catch (const char* msg) {
        cout << "Invalid input" << endl;
      }
      compute_maybe_count(input.substr(0,2), maybe_count_mtr);
      draw_table(maybe_count_mtr);
    }
  }
}
