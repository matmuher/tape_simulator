#include <iostream>
#include <TapeSimulator.hpp>
#include <Logs.hpp>
#include <vector>
#include <Logs.hpp>

void sort_tape( const ts::Tape& input_tape,
                ts::Tape& output_tape)
{
    std::size_t size = input_tape.get_size();

    if (size == 1)
    {
        output_tape.write_mr(input_tape.read());
        return;
    }

    int pivot = input_tape.read_mr();

    ts::Tape lower_tape{size};
    ts::Tape upper_tape{size};

    for (size_t elem_id = 0; elem_id < size; ++elem_id)
    {
        int elem = input_tape.read_mr();
        
        if (elem < pivot)
        {
            lower_tape.write_mr(elem);
        }
        else
        {
            upper_tape.write_mr(elem);
        }
    }

    sort_tape(lower_tape, output_tape);
    sort_tape(upper_tape, output_tape);
}

int main()
{
    ts::Tape input_tape{"tape.txt"};
    ts::Tape output_tape{13, "tape_out.txt"};

    sort_tape(input_tape, output_tape);
    
    input_tape.dump();
    output_tape.dump();

    return 0;
}