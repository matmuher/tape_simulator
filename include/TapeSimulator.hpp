#pragma once

#include <string>
#include <cstddef>
#include <fstream>
#include <vector>

namespace ts
{
    class Tape
    {   
        static std::size_t tmp_id;

        const std::size_t m_size;
        std::size_t head_pos;
        std::string m_name;

        std::vector<int> vec;

    public:

        Tape(std::size_t size, const std::string& name, bool init_from_file = true);
        Tape(std::size_t size);

        void move_left();
        void move_right();

        int read() const;
        void write(int val);

        void dump() const;

        ~Tape();
    };
}
