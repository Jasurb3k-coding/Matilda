#include <fmt/core.h>
#include <fmt/ostream.h>
#include <iostream>
#include "bmp.h"
#include "../utils.h"

BMPImage::BMPImage(const std::string &filePath) : file_path(filePath) {
    read_bmp();
}

void BMPImage::encrypt() const {
    // Implementation of encryption
}

int BMPImage::get_width() const {
    return (int) bmp_info_header.width;
}

int BMPImage::get_height() const {
    return (int) bmp_info_header.height;
}

void BMPImage::read_bmp() {
    auto file = open_file();
    file.read(reinterpret_cast<char *>(&bmp_header), sizeof(bmp_header));
    file.read(reinterpret_cast<char *>(&bmp_info_header), sizeof(bmp_info_header));
    file.seekg(bmp_header.data_offset, std::fstream::beg);

    pixel_data.resize(bmp_info_header.image_size);
    file.read(reinterpret_cast<char *>(pixel_data.data()), (long) pixel_data.size());
    read_pixels();
}

void BMPImage::read_pixels() {
    auto file = open_file();
    auto pixels_starting_position = bmp_header.data_offset;
    auto total_number_of_pixels = bmp_info_header.width * bmp_info_header.height;

    auto pixel_size = bmp_info_header.bits_per_pixel / 8;
    bool is_rgb_pixel = pixel_size % 3 == 0;
    auto color_count = is_rgb_pixel ? 3 : 4;

    uint8_t pixels[total_number_of_pixels][color_count];

    file.seekg(pixels_starting_position, std::fstream::beg);
    file.read(reinterpret_cast<char *>(&pixels), bmp_info_header.image_size);

    std::fstream out = std::fstream("input.txt", std::ios::trunc | std::ios::out);
    for (int64_t i = 0; i < total_number_of_pixels; i++) {
        fmt::println(out, "{} {} {}", pixels[i][0], pixels[i][1], pixels[i][2]);
    }
}

std::fstream BMPImage::open_file(const int &mode) {
    return std::fstream(file_path, mode | std::ios::binary);
}
