#include <Logs.hpp>

namespace ts
{
    std::ostream& log(const std::string& msg, const std::string filename)
    {
        static bool is_init{false};
        static std::ofstream file;

        if (!is_init)
        {
            file.open(filename);

            if (!file.is_open())
            {
                std::cout << "[error] can't open log file\n";
            }

            is_init = true;
        }

        file << '[';
        
        if (!msg.empty())
        {
            file << msg;
        }
        else
        {
            file << "info";
        }

        file << "] ";

        return file;
    }

    std::ostream& err()
    {
        return log("error");
    }
}