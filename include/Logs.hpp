#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

// TODO RAII

namespace ts
{
    void info(const std::string& fmt, ...);
    void log(const std::string& fmt, ...);
    void err(const std::string& fmt, ...);
}
