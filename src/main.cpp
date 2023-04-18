#include <iostream>
#include <TapeSimulator.hpp>
#include <Logs.hpp>
#include <vector>

// void sort_tape( std::size_t N,
//                 const std::string& input_tape_name,
//                 const std::string& output_tape_name)
// {
//     int pivot = input_tape.read_mr();

//     ts::Tape lower_tape{N};
//     ts::Tape upper_tape{N};
// }

int main()
{
    ts::Tape tape1{20};
    tape1.dump();

    ts::Tape tape2{"tape.txt"};
    tape2.dump();

    return 0;
}