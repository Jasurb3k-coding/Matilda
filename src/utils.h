#pragma once

#include <string>

auto println_red(const std::string &text) -> void;

auto red_text(const std::string &text) -> std::string;

auto validate_image_path(const std::string &basicString) -> void;

auto check_file_exists(const std::string &basicString) -> void;

auto print_help() -> void;