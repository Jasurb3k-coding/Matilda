#include <fmt/core.h>
#include <fmt/ostream.h>
#include <iostream>
#include "bmp.h"

BMPImage::BMPImage(const std::string &filePath) : file_path(filePath) {
    read_bmp();
    encrypt("hi");
    write_pixels();
}

void BMPImage::encrypt(const std::string &message) {
    for (int i = 0; i < total_number_of_pixels; ++i) {
        pixel_data[i][0] > 4 ? pixel_data[i][0] -= 5 : pixel_data[i][0] = 0;
        pixel_data[i][1] > 4 ? pixel_data[i][1] -= 5 : pixel_data[i][1] = 0;
        pixel_data[i][2] > 4 ? pixel_data[i][2] -= 5 : pixel_data[i][2] = 0;
    }
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

    read_pixels();
}

void BMPImage::read_pixels() {
    auto file = open_file();
    pixels_starting_position = bmp_header.data_offset;
    total_number_of_pixels = bmp_info_header.width * bmp_info_header.height;

    pixel_size = bmp_info_header.bits_per_pixel / 8;
    secret_size_per_pixel = (int) (bmp_info_header.bits_per_pixel * 0.1);
    max_secret_chars = (secret_size_per_pixel * total_number_of_pixels) / 8;

    is_rgb = pixel_size % 3 == 0;
    color_count = is_rgb ? 3 : 4;

    uint8_t pixels[total_number_of_pixels][color_count];

    file.seekg(pixels_starting_position, std::fstream::beg);
    file.read(reinterpret_cast<char *>(&pixels), bmp_info_header.image_size);

    int counter = 0;

    for (int64_t i = 0; i < total_number_of_pixels; i++) {
        pixel_data.reserve(total_number_of_pixels);
        auto &red = pixels[i][0];
        auto &green = pixels[i][1];
        auto &blue = pixels[i][2];

        counter++;
        const auto &alpha = is_rgb ? 255 : pixels[i][3];
        pixel_data.push_back({red, green, blue, alpha});


    }
    fmt::println("COUNTER: {}", counter);
}

void BMPImage::write_pixels() {

    auto file = open_file(std::ios::in | std::ios::out);

    uint8_t pixels[total_number_of_pixels][color_count];
    file.seekg(pixels_starting_position, std::fstream::beg);
    std::fstream out = std::fstream("input.txt", std::ios::trunc | std::ios::out);

    for (int i = 0; i < total_number_of_pixels; ++i) {
        pixels[i][0] = pixel_data[i][0];
        pixels[i][1] = pixel_data[i][1];
        pixels[i][2] = pixel_data[i][2];
        if (is_rgb) {
            pixels[i][3] = pixel_data[i][3];
        }
        fmt::println(out, "{} {} {} {}", pixel_data[i][0], pixel_data[i][1], pixel_data[i][2], pixel_data[i][3]);
    }
    file.write(reinterpret_cast<char *>(&pixels), bmp_info_header.image_size);
    file.close();
}

std::fstream BMPImage::open_file(const int &mode) {
    return std::fstream(file_path, mode | std::ios::binary);
}
