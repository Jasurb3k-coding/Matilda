#pragma once

#include <string>
#include <fstream>
#include "base.h"

struct PPMHeader {
    int signature;
    int width;
    int height;
    int number_of_colors;
};


struct PPMImage : public ImageBase {
    explicit PPMImage(const std::string &filePath);

    int get_width() const override;

    int get_height() const override;

    int get_max_secret_characters() const override;


    void check_if_message_can_be_written(const std::string &message) const override;

    void check_for_secret_message() const override;

    void encrypt(const std::string &message) override;

    std::string decrypt() override;

private:
    PPMHeader ppm_header{};
    std::vector<std::array<int, 3>> pixel_data{};

    static std::string get_bitset_from_string(const std::string &input);

    std::string get_LSB_string_from_pixel_data() const;

    std::string get_string_from_bitset(const std::string &binaryString);

    bool is_last_char_supported(const std::string &result) const;

    int replaceLSBs(int &value, const std::string &bitmap_str);

    void write_encrypted_message_into_pixels(std::string &encrypted);

    void validate_written_image(const std::string &expected_message);

    void validate_message(const std::string &message) const;

    uint32_t pixels_starting_position{};
    int32_t total_number_of_pixels{};
    int max_secret_chars{};

    void persist_pixels() override;

    void read_image() override;

    std::fstream open_file(const int &mode = std::ios::in) override;

    void read_pixels() override;
};
