#include <iostream>
#include <TapeSimulator.hpp>
#include <Logs.hpp>
#include <vector>
#include <Logs.hpp>

int ret_max = 0;

void qsort_tape( const ts::Tape& input_tape,
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

    qsort_tape(lower_tape, output_tape);
    qsort_tape(upper_tape, output_tape);
}

ts::Tape merge_tapes(const ts::Tape& lhs, const ts::Tape& rhs)
{
    size_t lhs_size = lhs.get_size();
    size_t rhs_size = rhs.get_size();
    
    size_t output_size = lhs_size + rhs_size;
    ts::Tape output{output_size};
    output.move_right();

    while ((lhs.get_pos() >= 1) && (rhs.get_pos() >= 1))
    {
        int lhs_elem = lhs.read();
        int rhs_elem = rhs.read();

        ts::log("cmp: %d and %d\n", lhs_elem, rhs_elem);

        if (lhs_elem < rhs_elem)
        {
            ts::log("Lhs: %d\n", lhs_elem);
            output.write(lhs_elem);
            lhs.move_left();
        }
        else
        {
            ts::log("Rhs: %d\n", rhs_elem);
            output.write(rhs_elem);
            rhs.move_left();
        }

        output.move_right();
    }


    // TODO copypaste
    while (lhs.get_pos() >= 1)
    {
        int elem = lhs.read();

        output.write(elem);
        output.move_right();

        lhs.move_left();
    }

    while (rhs.get_pos() >= 1)
    {
        int elem = rhs.read();

        output.write(elem);
        output.move_right();

        rhs.move_left();
    }

    output.dump();

    return output;
}

void launch_sort_tape(  const std::string& input_tape_name,
                        const std::string& output_tape_name)
{
    ts::Tape input_tape{input_tape_name};
    input_tape.scroll_to_end();

    ts::Tape output_tape{input_tape.get_size(), output_tape_name};
    qsort_tape(input_tape, output_tape);
}

int main(int argc, const char* argv[])
{
    ts::Tape tp1{"tp1.txt"};
    ts::Tape tp2{"tp2.txt"};

    tp1.scroll_to_end();
    tp2.scroll_to_end();

    ts::Tape merged = merge_tapes(tp1, tp2);
    merged.dump();

    exit(1);

    if (argc < 3)
    {
        std::cout   << "Please, enter cmd coefficients, e.g:\n\n"
                    << "\t./TapeSimulator input.txt output.txt\n\n";

    }
    else
    {
        launch_sort_tape(argv[1], argv[2]);
    }

    return 0;
}