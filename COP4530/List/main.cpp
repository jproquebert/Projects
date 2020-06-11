#include <iostream>
#include <string>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include "List.h"

using namespace std;
using namespace cop4530;

#define REPEATS 3

int main(int argc, char ** argv) {
    cout<<endl<<REPEATS<<"Three measurements per list"<<endl<<endl;
    
    
    /* 100 element list       */
    List<int> nums[REPEATS];
    
    int cnt = 100;
    int range = cnt / 3;
    
    for (int j = 0; j < REPEATS; j++) {
        /* initialize a random seed;
         * generate a random number between 1 and range.  */
        srand (time(NULL));
        for (int i = 0; i < cnt; i++) {
            int item = rand() % range + 1;
            nums[j].push_back(item);
        }
    }
    
    auto r_startrev = chrono::steady_clock::now();
    for (int i = 0; i < REPEATS; i++) {
        nums[i].reverse();
    }
    auto r_endrev = chrono::steady_clock::now();
    
    int usecrev = chrono::duration_cast<chrono::microseconds>(r_endrev - r_startrev).count();
    cout << "Average reverse time " <<cnt<<"-item list: " << usecrev/REPEATS<<" usec"<<endl<<endl;
    
    auto r_startdedup = chrono::steady_clock::now();
    for (int i = 0; i < REPEATS; i++) {
        nums[i].deduplicate();
    }
    auto r_enddedup = chrono::steady_clock::now();
    
    int usecdedup = chrono::duration_cast<chrono::microseconds>(r_enddedup - r_startdedup).count();
    cout << "Average deduplicate time " <<cnt<<"-item list: " << usecdedup/REPEATS<<" usec"<<endl<<endl<<endl<<endl;
    
    
    
    
    
    /* 1000 element list       */
    List<int> nums2[REPEATS];
    int cnt2 = 1000;
    int range2 = cnt2 /33;
    
    for (int j = 0; j < REPEATS; j++)
    {
        srand (time(NULL));
        for (int i = 0; i < cnt2; i++)
        {
            int item = rand() % range2 + 1;
            nums2[j].push_back(item);
        }
    }
    
    auto r_start2 = chrono::steady_clock::now();
    for (int i = 0; i < REPEATS; i++) {
        nums2[i].reverse();
    }
    auto r_end2 = chrono::steady_clock::now();
    
    int usec2 = chrono::duration_cast<chrono::microseconds>(r_end2 - r_start2).count();
    cout << "Average reverse time " <<cnt2<<"-item list: " << usec2/REPEATS<<" usec"<<endl<<endl;
    
    auto r_startdedup2 = chrono::steady_clock::now();
    for (int i = 0; i < REPEATS; i++) {
        nums2[i].deduplicate();
    }
    auto r_enddedup2 = chrono::steady_clock::now();
    
    int usecdedup2 = chrono::duration_cast<chrono::microseconds>(r_enddedup2 - r_startdedup2).count();
    cout << "Average deduplicate time " <<cnt2<<"-item list: " << usecdedup2/REPEATS<<" usec"<<endl<<endl<<endl<<endl;
    
    
    
    
    
    /* 10000 element list       */
    List<int> nums3[REPEATS];
    int cnt3 = 10000;
    int range3 = cnt3 /333;
    
    for (int j = 0; j < REPEATS; j++)
    {
        srand (time(NULL));
        for (int i = 0; i < cnt3; i++)
        {
            int item3 = rand() % range3 + 1;
            nums3[j].push_back(item3);
        }
    }
    
    auto r_start3 = chrono::steady_clock::now();
    for (int i = 0; i < REPEATS; i++) {
        nums3[i].reverse();
    }
    auto r_end3 = chrono::steady_clock::now();
    
    int usec3 = chrono::duration_cast<chrono::microseconds>(r_end3 - r_start3).count();
    cout << "Average reverse time " <<cnt3<<"-item list: " << usec3/REPEATS<<" usec"<<endl<<endl;
    
    
    auto r_startdedup3 = chrono::steady_clock::now();
    for (int i = 0; i < REPEATS; i++) {
        nums3[i].deduplicate();
    }
    auto r_enddedup3 = chrono::steady_clock::now();
    
    int usecdedup3 = chrono::duration_cast<chrono::microseconds>(r_enddedup3 - r_startdedup3).count();
    cout << "Average deduplicate time " <<cnt3<<"-item list: " << usecdedup3/REPEATS<<" usec"<<endl<<endl<<endl<<endl;
    
    
    
    
    
    
    
    
    
    return 0;
}

