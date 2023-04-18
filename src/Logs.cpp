#include <Logs.hpp>
#include <stdarg.h>

namespace ts
{
    FILE* get_log(const std::string log_file_name = "log.txt")
    {
        static bool is_init{false};
        static FILE* log_file;

        if (!is_init)
        {
            log_file = fopen(log_file_name.c_str(), "w");
            
            if (log_file == NULL)
            {
                std::cout << "[error] Can't open log file (" << log_file_name << ")\n";
            }

            is_init = true;
        }

        return log_file;
    }

    static void log_msg(    const std::string& msg,
                            const std::string& fmt, va_list args)
    {
        std::string new_fmt = msg + fmt;
        vfprintf(get_log(), new_fmt.c_str(), args);
        fflush(get_log());
    }

    void info(const std::string& fmt, ...)
    {
        va_list args;
        va_start(args, fmt);

        log_msg("[info] ", fmt, args);

        va_end(args);
    }

    void log(const std::string& fmt, ...)
    {
        va_list args;
        va_start(args, fmt);

        log_msg("", fmt, args);

        va_end(args);
    }

    void err(const std::string& fmt, ...)
    {
        va_list args;
        va_start(args, fmt);

        log_msg("[error] ", fmt, args);

        va_end(args);
    }

    void end_log()
    {
        fclose(get_log());
    }
}