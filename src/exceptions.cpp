#include <fmt/core.h>
#include "utils.h"

enum EXCEPTION_CODE {
    UNRECOGNISED_COMMAND = 1,
    WRONG_NUMBER_OF_ARGUMENTS = 2,
    FILE_DOES_NOT_EXIST = 3,
    NOT_A_REGULAR_FILE = 4,
    WRITE_FAILED = 5,
    NOT_SUPPORTED_CHARACTERS = 6,
    MESSAGE_TOO_LONG = 7,
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

auto error_file_does_not_exist(const std::string &file_path) -> void {
    auto message = fmt::format("File {} does not exist", file_path);
    println_red(message);
    exit(FILE_DOES_NOT_EXIST);
}

auto error_not_a_regular_file(const std::string &file_path) -> void {
    auto message = fmt::format("{} is not a regular file", file_path);
    println_red(message);
    exit(NOT_A_REGULAR_FILE);
}

auto error_file_does_not_have_permission(const std::string &file_path) -> void {
    auto message = fmt::format("{} does not have enough permissions", file_path);
    println_red(message);
    exit(NOT_A_REGULAR_FILE);
}

auto error_not_supported_image_type(const std::string &image_type) -> void {
    auto message = fmt::format("{} image type is currently not supported", image_type);
    println_red(message);
    exit(NOT_A_REGULAR_FILE);
}

auto error_write_failed() -> void {
    auto message = fmt::format("There has been an error while writing the message");
    println_red(message);
    exit(WRITE_FAILED);
}

auto error_not_supported_characters() -> void {
    auto message = fmt::format(
            "The provided message has unsupported characters. You can only decrypt alpha-numeric and whitespace characters");
    println_red(message);
    exit(NOT_SUPPORTED_CHARACTERS);
}


auto error_message_too_long(const int &provided_message_size, const int &max_message_size) -> void {
    auto need_to_remove = max_message_size - provided_message_size;
    auto message = fmt::format(
            "The message is too long ({} characters). Max character count is {} characters. Please remove {} characters",
            provided_message_size, max_message_size, need_to_remove);
    println_red(message);
    exit(MESSAGE_TOO_LONG);
}