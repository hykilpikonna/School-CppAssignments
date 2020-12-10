//
// Created by Hykilpikonna on 10/21/20.
//
#include "iostream"
#include <cstdint>
#include <iomanip>
#include <vector>
#include "thread"
#define long int64_t

using namespace std;

template <typename T> string join(const vector<T>& array, const string& separator, const string& pre, const string& post)
{
    string result;

    for (int i = 0; i < array.size(); i++)
    {
        result += to_string(array[i]);
        if (i != array.size() - 1)
            result += separator;
    }

    return pre + result + post;
}

int main()
{
    cout << thread::hardware_concurrency() << endl;

    auto lx = vector<int>();
    auto ly = vector<int>();
//    cout << "[" << (15 - i) << ", " << (15 - y) << "]";
    for (int i = 0; i < 8; ++i)
    {
        for (int x = 0; x < i; x++)
        {
            lx.emplace_back(x);
            ly.emplace_back(i);
        }
        for (int y = 0; y <= i; y++)
        {
            lx.emplace_back(i);
            ly.emplace_back(y);
        }
    }
    cout << join(lx, ",", "{", "}") << endl;
    cout << join(ly, ",", "{", "}") << endl;
}
