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
    ts::Tape tape1{"tape.txt"};
    ts::Tape tape2{10, "tape_out.txt"};
    tape2.write(9);

    tape1.dump();
    tape2.dump();

    return 0;
}