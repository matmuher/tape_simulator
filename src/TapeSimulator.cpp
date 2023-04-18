#include <iostream>
#include <TapeSimulator.hpp>
#include <Logs.hpp>

namespace ts
{
    std::size_t Tape::tmp_id = 0;

    Tape::Tape(std::size_t size, const std::string& name, bool init_from_file)
    :
        m_size{size},
        head_pos{0},
        m_name{name},
        vec{}
    {
        vec.reserve(m_size);

        if (init_from_file)
        {
            std::ifstream file;
            file.open(m_name);

            if (!file)
            {
                log() << "Can't open file " << name << '\n';
            }

            for (std::size_t i = 0; i < m_size; ++i)
            {
                int elem;
                file >> elem;
                vec.push_back(elem);

                log() << "Read " << i << "th elem from file [" << name << "]: " << elem << "\n";
            }
            
            file.close();
        }
        else
        {
            for (std::size_t i = 0; i < m_size; ++i)
            {
                vec.push_back(0);
            }
        }
    }

    Tape::Tape(std::size_t size)
    :
        Tape{size, "/tmp/tape_tmp" + std::to_string(++tmp_id), false}
        {}

    void Tape::move_left()
    {
        if (head_pos != 0)
        {
            --head_pos;
        }
    }

    void Tape::move_right()
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

    void Tape::dump() const
    {
        std::ostream& logs = log("dump tape " + m_name);
        for (std::size_t i = 0; i < m_size; ++i)
        {
             logs << vec[i] << ' ';
        }
        logs << '\n';    
    }

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
}