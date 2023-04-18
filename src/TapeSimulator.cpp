#include <iostream>
#include <TapeSimulator.hpp>
#include <Logs.hpp>

namespace ts
{
    std::size_t Tape::tmp_id = 0;

// [ctor]

    Tape::Tape(const std::string& name)
    :
        m_size{0},
        head_pos{0},
        m_name{name},
        vec{}
    {
        vec.reserve(m_size);

        std::ifstream file;
        file.open(m_name);

        if (!file)
        {
            err("Can't open file %s\n", name);
        }

        for (int elem; file >> elem;)
        {
            vec.push_back(elem);

            info("Read %uth elem from file [%s]: %d\n", vec.size(), name.c_str(), elem);
        }
        
        file.close();

        const_cast<std::size_t&>(m_size) = vec.size();
    }

    Tape::Tape(std::size_t size, const std::string& name)
    :
        m_size{size},
        head_pos{0},
        m_name{create_name(name)},
        vec{}
    {
        vec.reserve(m_size);

        for (std::size_t elem_id = 0; elem_id < m_size; ++elem_id)
        {
            vec.push_back(0);
        }
    }

// [interact]

    void Tape::move_left() const
    {
        if (head_pos != 0)
        {
            --head_pos;
        }
    }

    void Tape::move_right() const
    {
        if (head_pos + 1 != m_size)
        {
            ++head_pos;
        }
    }

    int Tape::read() const
    {
        return vec[head_pos];
    }

    void Tape::write(int val)
    {
        vec[head_pos] = val;
    }

    int Tape::read_ml() const
    {
        int ret = read();
        move_left();

        return ret;
    }

    int Tape::read_mr() const
    {
        int ret = read();
        move_right();

        return ret;
    }

    void Tape::write_ml(int val)
    {
        write(val);
        move_left();
    }

    void Tape::write_mr(int val)
    {
        write(val);
        move_right();
    }

// [get]

    int Tape::get_size() const
    {
        return m_size;
    }

// [debug]

    void Tape::dump() const
    {
        info("Dump tape [%s]\n", m_name);

        log("\tSize(%d)\n", m_size);

        for (std::size_t i = 0; i < m_size; ++i)
        {
            log("%d ", vec[i]);
        }

        log("\n");  
    }

// [dtor]

    Tape::~Tape()
    {
        std::ofstream file;
        file.open(m_name, std::ofstream::trunc);

        for (std::size_t i = 0; i < m_size; ++i)
        {
            file << vec[i] << ' ';
        }
        file << '\n';

        file.close();
    }

// [private functions]

    std::string Tape::create_name(const std::string& str)
    {
        if (str.empty())
        {
            return "tmp/tape" + std::to_string(++tmp_id);
        }
        else
        {
            return str;
        }
    }
}