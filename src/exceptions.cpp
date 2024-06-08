#include <fmt/core.h>
#include "utils.h"

enum EXCEPTION_CODE {
    UNRECOGNISED_COMMAND = 1,
    WRONG_NUMBER_OF_ARGUMENTS = 2,
};

auto try_help_text = "Use -h to see available commands.";

auto error_unrecognized_command(const std::string &command_str) -> void {
    auto message = fmt::format("The command {} is not supported. {}", command_str, try_help_text);
    println_red(message);
    exit(UNRECOGNISED_COMMAND);
}

auto error_wrong_number_of_arguments() -> void {
    auto message = fmt::format("You entered wrong number of arguments. {}", try_help_text);
    println_red(message);
    exit(WRONG_NUMBER_OF_ARGUMENTS);
}