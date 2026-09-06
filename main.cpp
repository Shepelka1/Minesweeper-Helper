#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

//-1 checked
//-2 No
//-3 Yes

int find_max_maybe_count(vector<vector<int>> maybe_count_mtr) {
  int max_count = 0;
  int size_x = maybe_count_mtr.size();
  int size_y = maybe_count_mtr[0].size();
  for (int i = 0; i < size_x; i++) {
    for (int j = 0; j < size_y; j++) {
      if (maybe_count_mtr[i][j] > max_count)
        max_count = maybe_count_mtr[i][j];
    }
  }
  return max_count;
}

void draw_table(vector<vector<int>> values, vector<vector<int>> old_values) {
  int max_count = find_max_maybe_count(values);
  for (int i = 0; i < values[0].size(); i++) {
    for (int j = 0; j < values.size(); j++) {
      if (values[j][i] == -3) {
        if (old_values[j][i] != -3)
          cout << " | y";
        else
          cout << " | Y";
      }else if (values[j][i] == -2){
        cout << " | N";
      }else if (values[j][i] == -1){
        cout << " | #";
      }else if (values[j][i] == max_count){
        cout << " | ?";
      }else {
        cout << " |  ";
      }
    }
    cout << " |" << endl;
  }
}

void compute_maybe_count(string coords, int item, vector<vector<int>> &maybe_count_mtr) {
  int size_x = maybe_count_mtr.size();
  int size_y = maybe_count_mtr[0].size();
  int curr_x = coords[1] - '0' - 1;
  int curr_y = coords[0] - '0' - 1;
  if (item == -3) {
    maybe_count_mtr[curr_x][curr_y] = -3;
    return;
  }
  maybe_count_mtr[curr_x][curr_y] = -1;
  for (int x_mod = -1; x_mod < 2; x_mod++) {
    for (int y_mod = -1; y_mod < 2; y_mod++) {
      int ind_x = curr_x + x_mod;
      int ind_y = curr_y + y_mod;
      if (ind_x < 0 || ind_x >= size_x || ind_y < 0 || ind_y >= size_y)
        continue;
      if (x_mod == 0 && y_mod == 0)
        continue;
      if (maybe_count_mtr[ind_x][ind_y] >= 0)
        maybe_count_mtr[ind_x][ind_y] += 1;
    }
  }
}

void find_certain_yes(unordered_map<string, int> &visited_dict, vector<vector<int>> &maybe_count_mtr) {
  int size_x = maybe_count_mtr.size();
  int size_y = maybe_count_mtr[0].size();
  int maybe_counter;
  int yes_counter;
  for (auto item : visited_dict) {
    maybe_counter = 0;
    yes_counter = 0;
    int curr_x = item.first[1] - '0' - 1;
    int curr_y = item.first[0] - '0' - 1;
    for (int x_mod = -1; x_mod < 2; x_mod++) {
      for (int y_mod = -1; y_mod < 2; y_mod++) {
        int ind_x = curr_x + x_mod;
        int ind_y = curr_y + y_mod;
        if (ind_x < 0 || ind_x >= size_x || ind_y < 0 || ind_y >= size_y)
          continue;
        if (x_mod == 0 && y_mod == 0)
          continue;
        if (maybe_count_mtr[ind_x][ind_y] >= 0)
          maybe_counter++;
        if (maybe_count_mtr[ind_x][ind_y] == -3)
          yes_counter++;
        }
      }
    if (maybe_counter > item.second - yes_counter)
      continue;
    for (int x_mod = -1; x_mod < 2; x_mod++) {
      for (int y_mod = -1; y_mod < 2; y_mod++) {
        int ind_x = curr_x + x_mod;
        int ind_y = curr_y + y_mod;
        if (ind_x < 0 || ind_x >= size_x || ind_y < 0 || ind_y >= size_y)
          continue;
        if (x_mod == 0 && y_mod == 0)
          continue;
        if (maybe_count_mtr[ind_x][ind_y] >= 0)
          maybe_count_mtr[ind_x][ind_y] = -3;
      }
    }
  }
}

void find_certain_no(unordered_map<string, int> &visited_dict, vector<vector<int>> &maybe_count_mtr) {
  int size_x = maybe_count_mtr.size();
  int size_y = maybe_count_mtr[0].size();
  int yes_counter;
  for (auto item : visited_dict) {
    yes_counter = 0;
    int curr_x = item.first[1] - '0' - 1;
    int curr_y = item.first[0] - '0' - 1;
    for (int x_mod = -1; x_mod < 2; x_mod++) {
      for (int y_mod = -1; y_mod < 2; y_mod++) {
        int ind_x = curr_x + x_mod;
        int ind_y = curr_y + y_mod;
        if (ind_x < 0 || ind_x >= size_x || ind_y < 0 || ind_y >= size_y)
          continue;
        if (x_mod == 0 && y_mod == 0)
          continue;
        if (maybe_count_mtr[ind_x][ind_y] == -3)
          yes_counter++;
        }
      }
    if (yes_counter < item.second)
      continue;
    for (int x_mod = -1; x_mod < 2; x_mod++) {
      for (int y_mod = -1; y_mod < 2; y_mod++) {
        int ind_x = curr_x + x_mod;
        int ind_y = curr_y + y_mod;
        if (ind_x < 0 || ind_x >= size_x || ind_y < 0 || ind_y >= size_y)
          continue;
        if (x_mod == 0 && y_mod == 0)
          continue;
        if (maybe_count_mtr[ind_x][ind_y] >= 0)
          maybe_count_mtr[ind_x][ind_y] = -2;
      }
    }
    visited_dict.erase(item.first);
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

    vector<vector<int>> old_maybe_count_mtr(size_x);
    unordered_map<string, int> old_visited_dict;
    vector<vector<int>> maybe_count_mtr(size_x);
    unordered_map<string, int> visited_dict;
    string key;
    int item;

    for (int i = 0; i < size_x; i++) {
      for (int j = 0; j < size_y; j++) {
        maybe_count_mtr[i].push_back(0);
      }
    }
    cout << "Enter YXN (y) or undo/exit" << endl;
    while (true) {
      cin >> input;
      if (input == "exit")
        exit(0);
      if (input == "undo") {
        maybe_count_mtr = old_maybe_count_mtr;
        visited_dict = old_visited_dict;
        draw_table(maybe_count_mtr, old_maybe_count_mtr);
        continue;
      }
      if (input == "next")
        break;
      try {
        key = input.substr(0,2);
        if (input[2] == 'y') {
          item = -3;
        }else {
          item = input[2] - '0';
          visited_dict[key] = item;
        }
      } 
      catch (const char* msg) {
        cout << "Invalid input" << endl;
      }
      old_maybe_count_mtr = maybe_count_mtr;
      old_visited_dict = visited_dict;
      compute_maybe_count(key, item, maybe_count_mtr);
      find_certain_yes(visited_dict, maybe_count_mtr);
      find_certain_no(visited_dict, maybe_count_mtr);
      draw_table(maybe_count_mtr, old_maybe_count_mtr);
    }
  }
}