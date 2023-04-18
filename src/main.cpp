#include <iostream>
#include <TapeSimulator.hpp>
#include <Logs.hpp>
#include <vector>

using arr_t = std::vector<int>;

arr_t merge(arr_t lhs, arr_t rhs)
{
    arr_t merged_arr;
    merged_arr.reserve(lhs.size() + rhs.size());

    int arr_walker = 0;
    auto it_lhs = lhs.begin();
    auto it_rhs = rhs.begin();

    while ((it_lhs != lhs.end()) && (it_rhs != rhs.end()))
    {
        if (*it_lhs < *it_rhs)
        {
            merged_arr.push_back(*it_lhs);
            ++it_lhs;
        }
        else
        {
            merged_arr.push_back(*it_rhs);
            ++it_rhs;
        }
    }

    if (it_lhs != lhs.end())
    {
        while (it_lhs != lhs.end())
        {
            merged_arr.push_back(*it_lhs);
            ++it_lhs;
        }
    }
    else if (it_rhs != rhs.end())
    {
        while (it_rhs != rhs.end())
        {
            merged_arr.push_back(*it_rhs);
            ++it_rhs;
        }
    }

    return merged_arr;
}

arr_t get_down_half(arr_t arr)
{
    arr_t down_arr(arr.begin(), arr.begin() + arr.size() / 2);

    return down_arr;
}

arr_t get_up_half(arr_t arr)
{
    arr_t up_arr(arr.begin() + arr.size() / 2, arr.end());

    return up_arr;
}

arr_t merge_sort(arr_t arr)
{
    arr_t down = get_down_half(arr);
    arr_t up = get_up_half(arr);

    if (arr.size() > 2)
    {
        down = merge_sort(down);
        up = merge_sort(up);
    }
    else
    {
        if (!down.empty() &&
            !up.empty() &&
            down[0] > up[0])
        {
            std::swap(down, up);
        }
    }

    return merge(down, up);
}



int main()
{
    ts::Tape tape1{20};
    tape1.dump();

    ts::Tape tape2{10, "tape.txt"};
    tape2.dump();

    return 0;
}