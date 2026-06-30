// main.cpp

//g++ main.cpp -o main && ./main

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

class Hook {
public:
    int length; //1-9
    std::array<int, 2> corner;
    int rotation; //0 -3
    int current_value; //1-9
    Hook(int length) {
        this->length = length;
        rotation = 0; //all hooks start with rotation 0
    }
};

void applyBaseToHooks(int number, int base, std::vector<Hook>& hooks) {
    for (size_t i = 0; i < hooks.size(); i++) {
        hooks[8-i].rotation = number % base;
        number /= base;
    }
}

class Grid {
    public:
        int grid[9][9];
};

class Number {
    public:
        int value;
        int coord[2];
        std::vector<std::vector<int>> partitions;
        std::vector<std::array<int, 2>> orthogonal_squares;
};

void next_corner(int hook, std::vector<Hook>& list){
    std::vector<std::array<int, 2>> corners;
    //get prev corner + length
    if (hook == 9) {
        corners.push_back({0, 0});
        corners.push_back({8, 0});
        corners.push_back({8, 8});
        corners.push_back({0, 8});
    }
    else {
        Hook prev_hook = list[hook];
        int x = prev_hook.corner[0];
        int y = prev_hook.corner[1];

        Hook& current_hook = list[hook-1];
        int l = current_hook.length;

        if (prev_hook.rotation == 0) {
            corners.push_back({x+1, y+1});
            corners.push_back({x+l, y+1});
            corners.push_back({x+l, y+l});
            corners.push_back({x+1, y+l});
        }
        else if (prev_hook.rotation == 1) {
            corners.push_back({x-l, y+1});
            corners.push_back({x-1, y+1});
            corners.push_back({x-1, y+l});
            corners.push_back({x-l, y+l});
        }
        else if (prev_hook.rotation == 2) {
            corners.push_back({x-l, y-l});
            corners.push_back({x-1, y-l});
            corners.push_back({x-1, y-1});
            corners.push_back({x-l, y-1});
        }
        else {
            corners.push_back({x+1, y-l});
            corners.push_back({x+l, y-l});
            corners.push_back({x+l, y-1});
            corners.push_back({x+1, y-1});
        }
    current_hook.corner = corners[current_hook.rotation];
    }
    //get corners of the new grid
    //return the corner based on rotation
}

int main() {
    std::vector<int> v = {2,3,4,5,6,7,8,9};
    std::vector<Hook> hooks;
    for (int i = 9; i > 0; i--) {
        hooks.emplace_back(i);
    }

    for (int i = 8; i >= 0; i--) {
        next_corner(i, hooks);
    }

    for (int a = 0; a < 65537; a++) {
        cout << a << "\n";
        applyBaseToHooks(a, 4, hooks);
        do {
            //makes sure all values can fit in the hooks
            if (v[7] > 3 || v[6] > 5 || v[5] > 7) {continue;}
            //assigns the values to the hooks for this permutation
            for (int i = 0; i < 9; i++) {
                hooks[i].current_value = v[i];
            }
        } while (std::next_permutation(v.begin(), v.end()));


        //for each value combination
    }
}

//plan:
//loop:
    //place every hook on the grid
    //loop:
        //assign values
        //attempt to solve partitions