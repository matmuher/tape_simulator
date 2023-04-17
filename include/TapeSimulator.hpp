#pragma once

#include <string>
#include <cstddef>
#include <fstream>

namespace ts
{
    class Tape
    {   
        static std::size_t tmp_id;

        std::size_t m_size;
        std::size_t head_pos;
        
        std::fstream file;

    public:

        Tape(std::size_t size, const std::string& name = "tmp") {}
    };
}

std::size_t ts::Tape::tmp_id = 0;