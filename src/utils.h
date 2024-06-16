#pragma once

#include <string>

auto println_red(const std::string &text) -> void;

auto red_text(const std::string &text) -> std::string;

auto validate_image_path(const std::string &image_path, const int &required_permissions) -> void;

auto check_file_exists(const std::string &image_path) -> void;

auto check_file_has_permissions(const std::string &image_path, const int &required_permissions) -> void;

void check_file_is_supported(const std::string &file_path);

void display_image_info(const std::string &file_path);

void encrypt_message(const std::string &file_path, const std::string &message);

void decrypt_message(const std::string &file_path);

void is_valid_message(const std::string &message);

auto get_image_dimensions(const std::string &file_path) -> std::pair<int, int>;

template<typename TP>
tm *to_local_time(TP tp);

auto print_help() -> void;