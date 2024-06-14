#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include "utils.h"
#include "exceptions.h"

auto validate_number_of_arguments(const std::vector<std::string> &args, const int &required_args_count) {
    if (args.size() != required_args_count) {
        error_wrong_number_of_arguments();
    }
}

auto get_info_about_image(const std::vector<std::string> &args) -> void {
    validate_number_of_arguments(args, 1);
    const std::string &image_path = args[0];
    validate_image_path(image_path, std::ios::in);
}

auto encrypt_message_into_picture(const std::vector<std::string> &args) -> void {
    validate_number_of_arguments(args, 2);
}

auto decrypt_message_from_picture(const std::vector<std::string> &args) -> void {
    validate_number_of_arguments(args, 1);
}

auto check(const std::vector<std::string> &args) -> void {
    validate_number_of_arguments(args, 2);
}