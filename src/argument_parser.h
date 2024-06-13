#pragma once

#include <string>

enum Command {
    INFO,
    ENCRYPT,
    DECRYPT,
    CHECK,
    HELP,
    INVALID
};

auto get_command_from_string(const std::string &command_str) -> Command;

auto parse_arguments(int argc, const char *argv[]) -> std::pair<Command, std::vector<std::string>>;
