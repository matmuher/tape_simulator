#include <Config.hpp>

Config get_config(const std::string& config_name)
{
    static bool is_init = false;
    static Config config;

    if (!is_init)
    {
        std::ifstream file;
        file.open(config_name);

        if (!file.is_open())
        {
            std::cout << "[error] Can't config file: " << config_name << '\n';
            exit(1);
        }

        file >> config.read_time;
        file >> config.write_time;
        file >> config.move_time;

        file.close();

        std::cout << "Read time: " << config.read_time << '\n';
        std::cout << "Write time: " << config.write_time << '\n';
        std::cout << "Move time: " << config.move_time << '\n';

        is_init = true;
    }
    
    return config;
}