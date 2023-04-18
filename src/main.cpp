#include <iostream>
#include <TapeSimulator.hpp>
#include <Logs.hpp>
#include <vector>
#include <Logs.hpp>
#include <Sort.hpp>
#include <cassert>

int main(int argc, const char* argv[])
{
    if (argc < 3)
    {
        std::cout   << "Please, enter cmd coefficients, e.g:\n\n"
                    << "\t./TapeSimulator input.txt output.txt\n\n";

    }
    else
    {
        ts::launch_sort_tape(argv[1], argv[2]);
    }

    return 0;
}