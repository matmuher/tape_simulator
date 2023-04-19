#pragma once

#include <string>
#include <fstream>
#include <iostream>

struct Config
{
    int read_time;
    int write_time;
    int move_time;
};

Config get_config(const std::string& config_name = "config.txt");