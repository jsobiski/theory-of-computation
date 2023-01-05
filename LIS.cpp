
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void lis(int arr[], int n)
{
    int lis[50];
    int x = 0;
    vector < int > v;
    vector < int > longest;

    lis[0] = 1;

    for (int i = 1; i < n; i++) {
        lis[i] = 1;
        if (v.size() > longest.size())
        {
            longest.clear();
            longest = v;
            v.clear();
        }
        else
            v.clear();
        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1)
            {
                lis[i] = lis[j] + 1;
                v.push_back(arr[j]);
            }
        }
        v.push_back(arr[i]);
    }
    int max = 0;
    for (int i = 0; i < n; i++)
            if (lis[i] > max)
                max = lis[i];

    cout << "The LIS is: " << max;
    cout << endl << endl << "The order is: ";
    for (int i = 0; i < longest.size(); i++)
        cout << longest.at(i) << " ";
    

    return;
}

int main()
{
    int count = 0;
    int arr[50];
    int x;

    ifstream file("incseq.txt");
    
    while (file >> x)
        arr[count++] = x;
          
    file.close();

    int size = sizeof(arr) / sizeof(arr[0]);
    lis(arr, size);
    return 0;
}
