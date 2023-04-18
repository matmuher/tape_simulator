#pragma once

#include <TapeSimulator.hpp>
#include <Logs.hpp>

namespace ts
{
    Tape merge_tapes(const ts::Tape& lhs, const ts::Tape& rhs);
    
    void copy_n_elems(const ts::Tape& src, ts::Tape& dst, size_t n);
    
    ts::Tape merge_sort(ts::Tape& tape);

    void launch_sort_tape(  const std::string& input_tape_name,
                            const std::string& output_tape_name);
}