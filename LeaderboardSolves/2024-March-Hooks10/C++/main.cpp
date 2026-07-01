// main.cpp

//g++ main.cpp -o main && ./main

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
#include <chrono>

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
    
    Grid() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                grid[i][j] = 0;
            }
        }
    }
    
    void reset() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                grid[i][j] = 0;
            }
        }
    }
    
    void writeValues(Hook hook) {
        int value = hook.current_value;
        int length = hook.length;
        int rotation = hook.rotation;

        std::array<int, 2> corner = hook.corner;
        int x = corner[0];
        int y = corner[1];

        grid[x][y] = value;

        if (rotation == 0) {
            for (int i = 1; i < length; i++) {
                grid[x+i][y] = value;
                grid[x][y+i] = value;
            }
        }
        else if (rotation == 2) {
            for (int i = 1; i < length; i++) {
                grid[x-i][y] = value;
                grid[x][y+i] = value;
            }
        }
        else if (rotation == 3) {
            for (int i = 1; i < length; i++) {
                grid[x-i][y] = value;
                grid[x][y-i] = value;
            }
        }
        else {
            for (int i = 1; i < length; i++) {
                grid[x+i][y] = value;
                grid[x][y-i] = value;
            }
        }
    }
};

Grid g = Grid();

class Number {
    public:
        int value;
        vector<int> coord;
        std::vector<std::vector<int>> partitions;
        std::vector<std::array<int, 2>> orthogonal_squares;
    Number(int v, vector<int> c, std::vector<std::vector<int>> p, std::vector<std::array<int, 2>> o) {
        value = v;
        coord = c;
        partitions = p;
        orthogonal_squares = o;
    }
    bool fits() {
        //check each orthogonal square and create a list
        vector<int> set;
        for (auto o : orthogonal_squares) {
            set.push_back(g.grid[o[0]][o[1]]);
        }
        
        //sort the collected values for comparison
        sort(set.begin(), set.end());
        
        //check if any partition matches the collected values
        for (auto partition : partitions) {
            //create a copy of partition without -1 values (blanks)
            vector<int> partition_values;
            for (int val : partition) {
                if (val != -1) {
                    partition_values.push_back(val);
                }
            }
            
            //sort partition values for comparison
            sort(partition_values.begin(), partition_values.end());
            
            //check if the partition matches the grid values
            if (partition_values.size() == set.size()) {
                bool matches = true;
                for (size_t i = 0; i < set.size(); i++) {
                    if (set[i] != partition_values[i]) {
                        matches = false;
                        break;
                    }
                }
                if (matches) {
                    return true;
                }
            }
        }
        
        return false;
    }
};
//bordering 3 elements
Number num1 = Number(18, {1, 8}, {{9, 9, -1}, {1, 8, 9}, {2, 7, 9}, {2, 8, 8}, {3, 6, 9}, {3, 7, 8}, {4, 5, 9}, {4, 6, 8}, {4, 7, 7}, {5, 5, 8}, {5, 6, 7}}, {{1, 7}, {0, 8}, {2, 8}});
Number num5 = Number(22, {2, 0}, {{4, 9, 9}, {5, 8, 9}, {6, 7, 9}, {6, 8, 8}, {7, 7, 8}}, {{2, 1}, {1, 0}, {3, 0}});
Number num10 = Number(7, {6, 8}, {{7, -1, -1}, {1, 6,-1}, {2, 5, -1}, {3, 4, -1}, {1, 2, 4}, {1, 3, 3}, {2, 2, 3}}, {{6, 7}, {5, 8}, {7, 8}});
Number num14 = Number(15, {7, 0}, {{6, 9, -1}, {7, 8,-1}, {1, 5, 9}, {1, 6, 8}, {1, 7, 7}, {2, 4, 9}, {2, 5, 8}, {2, 6, 7}, {3, 3, 9}, {3, 4, 8}, {3, 5, 7}, {3, 6, 6}, {4, 4, 7}, {4, 5, 6}}, {{7, 1}, {6, 0}, {8, 0}});

//non bordering 4 elements
Number num2 = Number(5, {1, 4}, {{5, -1, -1, -1}, {1, 4, -1, -1}, {2, 3, -1, -1}, {1, 2, 2, -1}}, {{2, 4}, {0, 4}, {1, 5}, {1, 3}});
Number num3 = Number(9, {1, 2}, {{9, -1, -1, -1}, {1, 8, -1, -1}, {2, 7, -1, -1}, {3, 6, -1, -1}, {4, 5, -1, -1}, {1, 2, 6, -1}, {1, 3, 5, -1}, {1, 4, 4, -1}, {2, 2, 5, -1}, {2, 3, 4, -1}, {1, 2, 2, 4}, {1, 2, 3, 3}}, {{2, 2}, {0, 2}, {1, 3}, {1, 1}});
Number num4 = Number(9, {2, 6}, {{9, -1, -1, -1}, {1, 8, -1, -1}, {2, 7, -1, -1}, {3, 6, -1, -1}, {4, 5, -1, -1}, {1, 2, 6, -1}, {1, 3, 5, -1}, {1, 4, 4, -1}, {2, 2, 5, -1}, {2, 3, 4, -1}, {1, 2, 2, 4}, {1, 2, 3, 3}}, {{3, 6}, {1, 6}, {2, 7}, {2, 5}});
Number num6 = Number(11, {3, 4}, {{2, 9, -1, -1}, {3, 8, -1, -1}, {4, 7, -1, -1}, {5, 6, -1, -1}, {1, 2, 8, -1}, {1, 3, 7, -1}, {1, 4, 6, -1}, {1, 5, 5, -1}, {2, 2, 7, -1}, {2, 3, 6, -1}, {2, 4, 5, -1}, {3, 3, 5, -1}, {3, 4, 4, -1}, {1, 2, 2, 6}, {1, 2, 3, 5}, {1, 2, 4, 4}, {1, 3, 3, 4}, {2, 2, 3, 4}},{{4, 4}, {2, 4}, {3, 5}, {3, 3}});
Number num7 = Number(12, {4, 7}, {{3, 9, -1, -1}, {4, 8, -1, -1}, {5, 7, -1, -1}, {6, 6, -1, -1}, {1, 2, 9, -1}, {1, 3, 8, -1}, {1, 4, 7, -1}, {1, 5, 6, -1}, {2, 2, 8, -1}, {2, 3, 7, -1}, {2, 4, 6, -1}, {2, 5, 5, -1}, {3, 3, 6, -1}, {3, 4, 5, -1}, {1, 2, 2, 7}, {1, 2, 3, 6}, {1, 2, 4, 5}, {1, 3, 3, 5}, {1, 3, 4, 4}, {2, 2, 3, 5}, {2, 2, 4, 4}, {2, 3, 3, 4}}, {{5, 7}, {3, 7}, {4, 8}, {4, 6}});
Number num8 = Number(14, {4, 1}, {{5, 9, -1, -1}, {6, 8, -1, -1}, {7, 7, -1, -1}, {1, 4, 9, -1}, {1, 5, 8, -1}, {1, 6, 7, -1}, {2, 3, 9, -1}, {2, 4, 8, -1}, {2, 5, 7, -1}, {2, 6, 6, -1}, {3, 3, 8, -1}, {3, 4, 7, -1}, {3, 5, 6, -1}, {4, 4, 6, -1}, {4, 5, 5, -1}, {1, 2, 2, 9}, {1, 2, 3, 8}, {1, 2, 4, 7}, {1, 2, 5, 6}, {1, 3, 3, 7}, {1, 3, 4, 6}, {1, 3, 5, 5}, {1, 4, 4, 5}, {2, 2, 3, 7}, {2, 2, 4, 6}, {2, 2, 5, 5}, {2, 3, 3, 6}, {2, 3, 4, 5}, {3, 3, 4, 4}}, {{5, 1}, {3, 1}, {4, 2}, {4, 0}});
Number num9 = Number(22, {5, 4}, {{4, 9, 9, -1}, {5, 8, 9, -1}, {6, 7, 9, -1}, {6, 8, 8, -1}, {7, 7, 8, -1}, {1, 3, 9, 9}, {1, 4, 8, 9}, {1, 5, 7, 9}, {1, 5, 8, 8}, {1, 6, 6, 9}, {1, 6, 7, 8}, {2, 2, 9, 9}, {2, 3, 8, 9}, {2, 4, 7, 9}, {2, 4, 8, 8}, {2, 5, 6, 9}, {2, 5, 7, 8}, {2, 6, 6, 8}, {2, 6, 7, 7}, {3, 3, 7, 9}, {3, 3, 8, 8}, {3, 4, 6, 9}, {3, 4, 7, 8}, {3, 5, 5, 9}, {3, 5, 6, 8}, {3, 5, 7, 7}, {3, 6, 6, 7}, {4, 4, 5, 9}, {4, 4, 6, 8}, {4, 4, 7, 7}, {4, 5, 5, 8}, {4, 5, 6, 7}, {5, 5, 6, 6}}, {{6, 4}, {4, 4}, {5, 5}, {5, 3}});
Number num11 = Number(19, {6, 2}, {{1, 9, 9, -1}, {2, 8, 9, -1}, {3, 7, 9, -1}, {3, 8, 8, -1}, {4, 6, 9, -1}, {4, 7, 8, -1}, {5, 5, 9, -1}, {5, 6, 8, -1}, {5, 7, 7, -1}, {6, 6, 7, -1}, {1, 2, 7, 9}, {1, 2, 8, 8}, {1, 3, 6, 9}, {1, 3, 7, 8}, {1, 4, 5, 9}, {1, 4, 6, 8}, {1, 4, 7, 7}, {1, 5, 5, 8}, {1, 5, 6, 7}, {2, 2, 6, 9}, {2, 2, 7, 8}, {2, 3, 5, 9}, {2, 3, 6, 8}, {2, 3, 7, 7}, {2, 4, 4, 9}, {2, 4, 5, 8}, {2, 4, 6, 7}, {2, 5, 5, 7}, {2, 5, 6, 6}, {3, 3, 4, 9}, {3, 3, 5, 8}, {3, 3, 6, 7}, {3, 4, 4, 8}, {3, 4, 5, 7}, {3, 4, 6, 6}, {3, 5, 5, 6}, {4, 4, 5, 6}}, {{7, 2}, {5, 2}, {6, 3}, {6, 1}});
Number num12 = Number(31,{7, 6}, {{5, 8, 9, 9}, {6, 7, 9, 9}, {6, 8, 8, 9}, {7, 7, 8, 9}}, {{8, 6}, {6, 6}, {7, 7}, {7, 5}});
Number num13 = Number(22, {7, 4}, {{4, 9, 9, -1}, {5, 8, 9, -1}, {6, 7, 9, -1}, {6, 8, 8, -1}, {7, 7, 8, -1}, {1, 3, 9, 9}, {1, 4, 8, 9}, {1, 5, 7, 9}, {1, 5, 8, 8}, {1, 6, 6, 9}, {1, 6, 7, 8}, {2, 2, 9, 9}, {2, 3, 8, 9}, {2, 4, 7, 9}, {2, 4, 8, 8}, {2, 5, 6, 9}, {2, 5, 7, 8}, {2, 6, 6, 8}, {2, 6, 7, 7}, {3, 3, 7, 9}, {3, 3, 8, 8}, {3, 4, 6, 9}, {3, 4, 7, 8}, {3, 5, 5, 9}, {3, 5, 6, 8}, {3, 5, 7, 7}, {3, 6, 6, 7}, {4, 4, 5, 9}, {4, 4, 6, 8}, {4, 4, 7, 7}, {4, 5, 5, 8}, {4, 5, 6, 7}, {5, 5, 6, 6}}, {{8, 4}, {6, 4}, {7, 5}, {7, 3}});

Number nums[14] = {num1, num5, num10, num14, num2, num3, num4, num6, num7, num8, num9, num11, num12, num13};



void next_corner(int hook, std::vector<Hook>& list){
    // corner candidates are ordered by rotation index:
    // 0 = top-left, 1 = top-right, 2 = bottom-left, 3 = bottom-right
    std::vector<std::array<int, 2>> corners;
    if (hook == 0) {
        // largest hook (length 9) sits on a corner of the full 9x9 grid
        corners.push_back({0, 0}); // rot 0: top-left
        corners.push_back({0, 8}); // rot 1: top-right
        corners.push_back({8, 0}); // rot 2: bottom-left
        corners.push_back({8, 8}); // rot 3: bottom-right
        list[hook].corner = corners[list[hook].rotation];
    }
    else {
        Hook prev_hook = list[hook-1];
        int x = prev_hook.corner[0];
        int y = prev_hook.corner[1];

        Hook& current_hook = list[hook];
        int l = prev_hook.length - 1; // inner square offset

        if (prev_hook.rotation == 0) {        // arms go down + right
            corners.push_back({x+1, y+1});
            corners.push_back({x+1, y+l});
            corners.push_back({x+l, y+1});
            corners.push_back({x+l, y+l});
        }
        else if (prev_hook.rotation == 1) {   // arms go down + left
            corners.push_back({x+1, y-l});
            corners.push_back({x+1, y-1});
            corners.push_back({x+l, y-l});
            corners.push_back({x+l, y-1});
        }
        else if (prev_hook.rotation == 2) {   // arms go up + right
            corners.push_back({x-l, y+1});
            corners.push_back({x-l, y+l});
            corners.push_back({x-1, y+1});
            corners.push_back({x-1, y+l});
        }
        else {                                // arms go up + left
            corners.push_back({x-l, y-l});
            corners.push_back({x-l, y-1});
            corners.push_back({x-1, y-l});
            corners.push_back({x-1, y-1});
        }
        current_hook.corner = corners[current_hook.rotation];
    }
}

int main() {
    auto begin = std::chrono::steady_clock::now();
    std::vector<int> v = {1,2,3,4,5,6,7,8,9};
    std::vector<Hook> hooks;

    for (int i = 9; i > 0; i--) {
        hooks.emplace_back(i);
    }

    for (int a = 0; a < 65537; a++) {
        if (a % 1000 == 0) cout << a << "\n";
        applyBaseToHooks(a, 4, hooks);

        for (int i = 0; i <= 8; i++) {
            next_corner(i, hooks);
        }

        do {
            //makes sure all values can fit in the hooks
            if (v[8] > 1 || v[7] > 3 || v[6] > 5 || v[5] > 7) {continue;}
            //assigns the values to the hooks for this permutation
            for (int i = 0; i < 9; i++) {
                hooks[i].current_value = v[i];
            }
            //reset and populate grid with all the values
            g.reset();
            for (Hook h : hooks) {
                g.writeValues(h);
            }
            //check each number
            if (!num1.fits() || !num2.fits() || !num3.fits() || !num4.fits() || 
                !num5.fits() || !num6.fits() || !num7.fits() || !num8.fits() || 
                !num9.fits() || !num10.fits() || !num11.fits() || !num12.fits() || 
                !num13.fits() || !num14.fits()) {
                continue;
            }

            //all numbers fit - print solution
            cout << "Solution found!\n";
            for (int i = 0; i < 9; i++) {
                cout << "Hook " << (9 - i) << ": value = " << hooks[i].current_value 
                     << ", rotation = " << hooks[i].rotation << "\n";
            }
            auto end = std::chrono::steady_clock::now();

            // Calculate elapsed time
            auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
            auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

            std::cout << "Elapsed: " << elapsed_ms.count() << " ms\n";
            std::cout << "Elapsed: " << elapsed_us.count() << " us\n";
            std::cout << "Elapsed: " << elapsed_ns.count() << " ns\n";
            return 0;
            
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