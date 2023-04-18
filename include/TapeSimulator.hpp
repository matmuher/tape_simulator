#pragma once

#include <string>
#include <cstddef>
#include <fstream>
#include <vector>

namespace ts
{
    class Tape
    {   
    private:

    // [private members]

        static std::size_t tmp_id;

        const std::size_t m_size;
        std::size_t head_pos;
        std::string m_name;

        std::vector<int> vec;

    // [private functions]

        std::string create_name(const std::string& str);

    public:

    // [ctor]

        Tape(const std::string& name); // for inpute tape
        Tape(std::size_t size, const std::string& name = "");


    // [interact]

        void move_left();
        void move_right();

        int read() const;
        void write(int val);

        /*
            [for easier working with tape]

            read_ml = read + move_left
            write_mr = write + move_right
        */
        int read_ml();
        int read_mr();
        void write_ml(int val);
        void write_mr(int val);

    // [get]

        int get_size() const;

    // [debug]

        void dump() const;

    // [dtor]

        ~Tape();
    };
}


