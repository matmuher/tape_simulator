#include <iostream>
#include <TapeSimulator.hpp>
#include <Logs.hpp>
#include <vector>
#include <Logs.hpp>

int ret_max = 0;

void sort_tape( const ts::Tape& input_tape,
                ts::Tape& output_tape)
{
    ++ret_max;
    if (ret_max > 100)
    {
        exit(1);
    }
    input_tape.dump();
    std::size_t size = input_tape.get_pos();

    if (size == 0)
    {
        return;
    }

    if (size == 1)
    {
        output_tape.write_mr(input_tape.read());
        return;
    }

    int pivot = input_tape.read();

    ts::Tape lower_tape{size};
    ts::Tape upper_tape{size};

    ts::info("Partly sort tape\n");
    ts::log("Pivot = %d\n\n", pivot);

    input_tape.move_right();

    for (size_t elem_id = 0; elem_id < size; ++elem_id)
    {
        int elem = input_tape.read_ml();
        ts::log("N(%d) %d\n", elem_id, elem);

        if (elem < pivot)
        {
            ts::log("Lower\n");
            lower_tape.write_mr(elem);
        }
        else
        {
            ts::log("Upper\n");
            upper_tape.write_mr(elem);
        }

        ts::log("\n");
    }   

    sort_tape(lower_tape, output_tape);
    sort_tape(upper_tape, output_tape);
}

int main()
{
    ts::Tape input_tape{"tape.txt"};
    input_tape.scroll_to_end();

    ts::Tape output_tape{10, "tape_out.txt"};

    sort_tape(input_tape, output_tape);
    
    input_tape.dump();
    output_tape.dump();

    return 0;
}