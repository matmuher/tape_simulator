#include <Sort.hpp>
#include <cassert>

namespace ts
{
    Tape merge_tapes(const ts::Tape& lhs, const ts::Tape& rhs)
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

    Tape merge_sort(ts::Tape& tape)
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
}