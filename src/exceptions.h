#pragma once

auto error_wrong_number_of_arguments() -> void;

auto error_unrecognized_command(const std::string &command_str) -> void;

auto error_file_does_not_exist(const std::string &file_path) -> void;

auto error_not_a_regular_file(const std::string &file_path) -> void;

auto error_file_does_not_have_permission(const std::string &file_path) -> void;

auto error_not_supported_image_type(const std::string &image_type) -> void;

auto error_write_failed() -> void;

auto error_not_supported_characters() -> void;

auto error_message_too_long(const int &provided_message_size, const int &max_message_size) -> void;

auto error_no_secret_message() -> void;

auto error_image_could_not_be_created() -> void;