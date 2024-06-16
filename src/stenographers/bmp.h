#pragma once


#include <string>
#include <fstream>
#include "base.h"

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t signature;
    uint32_t file_size;
    uint32_t reserved;
    uint32_t data_offset;
};

struct BMPInfoHeader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    uint32_t x_pixels_per_m;
    uint32_t y_pixels_per_m;
    uint32_t colors_used;
    uint32_t important_colors;
};

#pragma pack(pop)

struct BMPImage : public ImageBase {
    explicit BMPImage(const std::string &filePath);

    int get_width() const override;

    int get_height() const override;

    int get_max_secret_characters() const override;


    void check_if_message_can_be_written(const std::string &message) const override;

    void check_for_secret_message() const override;

    void encrypt(const std::string &message) override;

    std::string decrypt() override;

private:
    BMPHeader bmp_header{};
    BMPInfoHeader bmp_info_header{};
    std::vector<std::array<int, 4>> pixel_data{};

    static std::string get_bitset_from_string(const std::string &input);

    std::string get_LSB_string_from_pixel_data() const;

    std::string get_string_from_bitset(const std::string &binaryString);

    int replaceLSBs(int &value, const std::string &bitmap_str);

    bool is_last_char_supported(const std::string &result) const;

    void write_encrypted_message_into_pixels(std::string &encrypted);

    void validate_written_image(const std::string &expected_message);

    void validate_message(const std::string &message) const;

    bool is_rgb{};
    uint32_t pixels_starting_position{};
    int32_t total_number_of_pixels{};
    int pixel_size{};
    int secret_size_per_pixel{};
    int max_secret_chars{};
    int color_count{};

    void persist_pixels() override;

    void read_image() override;

    std::fstream open_file(const int &mode = std::ios::in) override;

    void read_pixels(std::fstream &file) override;
};
