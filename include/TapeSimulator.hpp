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
        mutable std::size_t head_pos;
        const std::string m_name;

        std::vector<int> vec;

    // [private functions]

        static std::string create_name(const std::string& str);

        bool is_in_borders(size_t i) const;

        static void read_delay();

        static void write_dealy();

        static void move_delay();

    public:

    // [ctor]

        Tape(const std::string& name); // for inpute tape
        Tape(std::size_t size, const std::string& name = "");

    // [interact]

        void move_left() const;
        void move_right() const;

        int read() const;
        void write(int val);

        /*
            [for easier working with tape]

            read_ml = read + move_left
            write_mr = write + move_right
        */
        int read_ml() const;
        int read_mr() const;
        void write_ml(int val);
        void write_mr(int val);

        void scroll_to_end() const;
        void scroll_to_start() const;

    // [get]

        size_t get_size() const;

        size_t get_pos() const;

        std::string get_name() const;

    // [debug]

        void dump() const;

    // [dtor]

        ~Tape();
    };
}


