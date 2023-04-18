#include <iostream>
#include <TapeSimulator.hpp>
#include <Logs.hpp>
#include <vector>
#include <Logs.hpp>
#include <cassert>

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
    ts::log("\n\n Merge [%s] and [%s]\n", lhs.get_name().c_str(), rhs.get_name().c_str());

    ts::log("\nLHS:\n");
    lhs.dump();

    ts::log("\nRHS:\n");
    rhs.dump();

    size_t lhs_size = lhs.get_size();
    size_t rhs_size = rhs.get_size();

    size_t output_size = lhs_size + rhs_size;
    lhs.scroll_to_start();
    rhs.scroll_to_start();
    lhs.move_right();
    rhs.move_right();

    ts::Tape output{output_size};

    while ((lhs.get_pos() <= lhs.get_size()) && (rhs.get_pos() <= rhs.get_size()))
    {
        int lhs_elem = lhs.read();
        int rhs_elem = rhs.read();

        ts::log("cmp: %d and %d\n", lhs_elem, rhs_elem);

        if (lhs_elem > rhs_elem)
        {
            ts::log("Lhs: %d\n", lhs_elem);
            output.write(lhs_elem);
            lhs.move_right();
        }
        else
        {
            ts::log("Rhs: %d\n", rhs_elem);
            output.write(rhs_elem);
            rhs.move_right();
        }

        output.move_right();
    }


    // TODO copypaste
    while (lhs.get_pos() <= lhs.get_size())
    {
        int elem = lhs.read();

        output.write(elem);
        output.move_right();

        lhs.move_right();
    }

    while (rhs.get_pos() <= rhs.get_size())
    {
        int elem = rhs.read();

        output.write(elem);
        output.move_right();

        rhs.move_right();
    }

    ts::log("\nOUT:\n");
    output.dump();

    return output;
}

void copy_n_elems(const ts::Tape& src, ts::Tape& dst, size_t n)
{
    ts::info("Make copy, src(%s), dst(%s)\n", src.get_name().c_str(), dst.get_name().c_str());

    if (n == 0)
    {
        return;
    }

    assert(src.get_size() >= n);
    assert(dst.get_size() >= n);

    while (n > 0)
    {
        int elem = src.read();
        dst.write(elem);

        src.move_left();
        dst.move_right();

        ts::log("copy elem(%d)\n", elem);

        --n;
    }
}

ts::Tape merge_sort(ts::Tape& tape)
{
    ts::info("\n\n I process %s\n", tape.get_name().c_str());
    tape.dump();

    if (tape.get_size() < 2)
    {
        return tape;
    }

    tape.move_left();

    ts::Tape tape_h1{tape.get_size() / 2};
    ts::log("\nh1(%d):\n", tape_h1.get_size());
    copy_n_elems(tape, tape_h1, tape_h1.get_size());
    tape_h1.dump();

    ts::Tape tape_h2{tape.get_size() - tape.get_size() / 2};
    ts::log("\nh2(%d):\n", tape_h2.get_size());
    copy_n_elems(tape, tape_h2, tape_h2.get_size());
    tape_h2.dump();

    ts::log("\n");

    return merge_tapes(merge_sort(tape_h1), merge_sort(tape_h2));
}

void launch_sort_tape(  const std::string& input_tape_name,
                        const std::string& output_tape_name)
{
    ts::Tape input_tape{input_tape_name};
    input_tape.scroll_to_end();

    ts::Tape output_tape{input_tape.get_size(), output_tape_name}; 
    ts::Tape tmp = merge_sort(input_tape);
    tmp.move_left();

    copy_n_elems(tmp, output_tape, input_tape.get_size());
    output_tape.dump();
}

int main(int argc, const char* argv[])
{
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