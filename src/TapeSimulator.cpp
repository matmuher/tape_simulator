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
        head_pos{1},
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
        head_pos{1},
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
        if (head_pos != m_size + 1)
        {
            ++head_pos;
        }
    }

    int Tape::read() const
    {
        if (is_in_borders(head_pos))
        {
            return vec[head_pos-1];
        }

        return -1;
    }

    void Tape::write(int val)
    {
        info("Write to %s\n", m_name.c_str());

        if (is_in_borders(head_pos))
        {
            info("Successfuly wrote: %d\n", val);
            vec[head_pos-1] = val;
        }
    }

    int Tape::read_ml() const
    {
        move_left();
        int ret = read();

        return ret;
    }

    int Tape::read_mr() const
    {
        move_right();
        int ret = read();

        return ret;
    }

    void Tape::write_ml(int val)
    {
        move_left();
        write(val);
    }

    void Tape::write_mr(int val)
    {
        move_right();
        write(val);
    }


    void Tape::scroll_to_end() const
    {
        for (size_t i = head_pos; i <= m_size; ++i)
        {
            move_right();
        }
    }

    void Tape::scroll_to_start() const
    {
        for (size_t i = head_pos; i >= 1; --i)
        {
            move_left();
        }
    }

// [get]

    size_t Tape::get_size() const
    {
        return m_size;
    }

    size_t Tape::get_pos() const
    {
        return head_pos;
    }

    std::string Tape::get_name() const
    {
        return m_name;
    }

// [debug]

    void Tape::dump() const
    {
        info("Dump tape [%s]\n", m_name.c_str());

        log("\tSize(%u)\n", m_size);
        log("\tHeadPos(%u)\n", head_pos);

        if (!vec.empty())
        {
            for (std::size_t i = 0; i < m_size; ++i)
            {
                log("%d ", vec[i]);
            }
        }
        else
        {
            log("*empty*");
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
        info("Create name from: %s\n", str.c_str());

        if (str.empty())
        {
            return "/tmp/tape" + std::to_string(++tmp_id);
        }
        else
        {
            return str;
        }
    }

    bool Tape::is_in_borders(size_t i) const
    {
        return (1 <= i) && (i <= m_size);
    }
}