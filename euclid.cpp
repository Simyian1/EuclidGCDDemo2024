#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <chrono> // cant use #include <sys/time.h> on windows, had to find alternative

using namespace std;

// function calcs the gcd and counts modulus operations
pair<int, int> GCD(int a, int b)
{
    int modCount = 0;
    while (b != 0)
    {
        int r = a % b;
        a = b;
        b = r;
        modCount++;
    }
    return { a, modCount };
}

//main
int main()
{
    int n;
    cout << "Enter a integer n (n > 8): ";
    cin >> n;
    //verify input
    if (n <= 8)
    {
        cout << "Enter a value greater than 8." << endl;
        return 1;
    }

    cout << "========================================================\n";
    //create vectors
    vector<int> modOps;
    vector<int> valsI;
    vector<int> time;

    // record start time with  chrono
    auto start = chrono::high_resolution_clock::now();

    //loop through 8 - n
    for (int i = 8; i <= n; ++i)
    {
        //calculate every 50th gcd to save time and resources
        if (i % 50 == 0)
        {
            int maxModCount = 0;
            pair<int, int> maxPair = { 0, 0 };
            //for every a and b
            for (int a = 1; a <= i; ++a)
            {
                for (int b = 1; b <= i; ++b)
                {
                    if (a == b) continue; // skip if both nums same

                    pair<int, int> result = GCD(a, b);
                    int gcd = result.first;
                    int modCount = result.second - 1;//mod count is 1 too many
                    //get new max mod cnt
                    if (modCount > maxModCount) 
                    {
                        maxModCount = modCount;
                        maxPair = { a, b };
                    }
                }
            }
            // store data for graph
            modOps.push_back(maxModCount);
            valsI.push_back(i);
            //get time
            int time1 = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count();
            time.push_back(time1);
            //gcd
            pair<int, int> result = GCD(maxPair.first, maxPair.second);
            int gcd = result.first;


            cout << "At i=" << i << "; gcd(" << maxPair.first << ", " << maxPair.second << ") = " << gcd << " took " << maxModCount << " modulus operations" << ", time: " << time1 << "ms\n";
        }

        
        
    }

    // end with chrono
    auto end = chrono::high_resolution_clock::now();
    //total time
    auto totalTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "========================================================\n";
    cout << "Total runtime: " << totalTime << " ms\n";

    return 0;
}
