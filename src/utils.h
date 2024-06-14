#pragma once

#include <string>

auto println_red(const std::string &text) -> void;

auto red_text(const std::string &text) -> std::string;

auto validate_image_path(const std::string &image_path, const int &required_permissions) -> void;

auto check_file_exists(const std::string &image_path) -> void;

auto check_file_has_permissions(const std::string &image_path, const int &required_permissions) -> void;

auto print_help() -> void;