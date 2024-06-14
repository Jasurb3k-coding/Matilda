#include <fmt/core.h>
#include <fmt/color.h>
#include <filesystem>
#include <fstream>
#include "utils.h"
#include "exceptions.h"

auto red_text(const std::string &text) -> std::string {
    auto red_color = 0xFF0000;
    return fmt::format(fg(fmt::color(red_color)), text);
}

auto println_red(const std::string &text) -> void {
    auto message = red_text(text);
    fmt::println("{}", message);
}

auto SUPPORTED_IMAGE_FORMATS = std::vector<std::string>{".png", ".jpg"};


auto validate_image_path(const std::string &image_path, const int &required_access) -> void {
    check_file_exists(image_path);
    check_file_has_permissions(image_path, required_access);
//    check_file_is_supported(image_path);
}

void check_file_exists(const std::string &file_path) {
    auto path = std::filesystem::path(file_path);
    auto file_exists = std::filesystem::exists(file_path);
    if (!file_exists) error_file_does_not_exist(path);

    auto is_regular_file = std::filesystem::is_regular_file(path);
    if (!is_regular_file) error_not_a_regular_file(path);
}

void check_file_has_permissions(const std::string &file_path, const int &required_permissions) {
    auto file = std::fstream(file_path, required_permissions);

    if (!file.is_open()) error_file_does_not_have_permission(file_path);
}

auto print_help() -> void {
    auto supported_image_formats_str = fmt::format("{}", fmt::join(SUPPORTED_IMAGE_FORMATS, ", "));
    auto message =
            "Usage: matilda [OPTIONS] [ARGUMENTS]\n"
            "\n"
            "A command-line tool for image stenography. Supports encrypting/decrypting messages into/from images, reading image information, and checking if the given message is encryptable into given image. \n"
            "\n"
            "Options:\n"
            "\n"
            "  -i, --info <file_path>\n"
            "        Display information about the given image file. Supported formats are " + supported_image_formats_str + " \n"
            "        Example: matilda -i /path/to/image.png\n"
            "        \n"
            "  -e, --encrypt <file_path> <\"message\">\n"
            "        Embed the given message into the given image file.\n"
            "        Example: matilda -e /path/to/image.png \"Your secret message\"\n"
            "        \n"
            "  -d, --decrypt <file_path>\n"
            "        Extract and display the hidden message from the given image file.\n"
            "        Example: matilda -d /path/to/image.png\n"
            "        \n"
            "  -c, --check <file_path> <\"message\">\n"
            "        Check if the given message can be encrypted into the given image file.\n"
            "        Example: matilda -c /path/to/image.png \"Your secret message\"\n"
            "        \n"
            "  -h, --help\n"
            "        Display this help text and information about the program, including supported image formats and usage instructions.\n"
            "        Example: matilda -h\n"
            "\n"
            "Additional Information:\n"
            "\n"
            "  Supported image formats: " + supported_image_formats_str + "\n"
            "  \n"
            "  Error Handling:\n"
            "    - Unsupported flags or missing arguments will result in an error message and a suggestion to use the -h flag.\n"
            "    - If an image file is not in a supported format, an appropriate error message will be displayed.\n"
            "    - If file permissions are insufficient, an appropriate error message will be displayed.\n"
            "    - Excessive arguments for any flag will result in an error message.\n"
            "\n"
            "Examples:\n"
            "\n"
            "  Display information about an image:\n"
            "    matilda -i /path/to/image.png\n"
            "\n"
            "  encrypt a message into an image:\n"
            "    matilda -e /path/to/image.png \"Secret message\"\n"
            "\n"
            "  Extract a hidden message from an image:\n"
            "    matilda -d /path/to/image.png\n"
            "\n"
            "  Check if a message can be encrypted into an image:\n"
            "    matilda -c /path/to/image.png \"Message to check\"\n"
            "\n"
            "Running the program without any flags will display this help text.\n"
            "\n"
            "For more information or to report issues, please refer to github repo";
    fmt::println("{}", message);
}