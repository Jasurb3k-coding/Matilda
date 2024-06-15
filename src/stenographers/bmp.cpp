#include <fmt/core.h>
#include <fmt/ostream.h>
#include <iostream>
#include "bmp.h"
#include "../exceptions.h"
#include <string>
#include <algorithm>

std::string eol = std::bitset<32>(0b11011010110010101101111010111010).to_string();

BMPImage::BMPImage(const std::string &filePath) : file_path(filePath) {
    read_bmp();
}

void BMPImage::encrypt(const std::string &message) {
    auto encrypted = get_bitset_from_string(message);
    encrypted += eol;
    int pixel = 0;
    int color = 0;
    for (int i = 0; i < encrypted.size(); i += secret_size_per_pixel) {
        if (i>encrypted.size()-10){

        }
        replaceLSBs(pixel_data[pixel][color], encrypted.substr(i, secret_size_per_pixel));

        if (++color == 3) {
            color = 0;
            pixel++;
        }
    }
    write_pixels();

//    Validate written message
    read_bmp();
    auto written_message = decrypt();
    if (written_message != message) {
        error_write_failed();
    }
}

std::string BMPImage::decrypt() {
    auto lsb = get_LSB_string_from_pixel_data();
    auto message = get_string_from_bitset(lsb);
    return message;
}

int BMPImage::replaceLSBs(int &value, const std::string &bitmap_str) {
    int bitmap = std::stoi(bitmap_str, nullptr, 2);
    bitmap <<= (secret_size_per_pixel - bitmap_str.size());
    int mask = ~((1 << secret_size_per_pixel) - 1);
    value = (value & mask) | (bitmap & ~mask);
    return value;
}

auto BMPImage::get_bitset_from_string(const std::string &input) -> std::string {
    std::string final_string = "";
    for (char c: input) {
        std::bitset<8> binary_char(c);
        final_string += binary_char.to_string();
    }
    return final_string;
}

auto BMPImage::get_string_from_bitset(const std::string &binaryString) -> std::string {
    std::string text = "";
    for (size_t i = 0; i < binaryString.size(); i += 8) {
        std::bitset<8> bits(binaryString.substr(i, 8));
        char character = static_cast<char>(bits.to_ulong());
        text += character;
    }
    return text;
}

std::string BMPImage::get_LSB_string_from_pixel_data() {
    std::string result = "";
    std::string ev = "";
//    EOL:                         "11011010110010101101111010111010"
//                               "01110110101100101011011110101110"
//                                 "11011010110010101101111010111001"
    auto color = 0;
    for (int i = 0; i < pixel_data.size();) {
        std::bitset<8> binary(pixel_data[i][color]);
        ev += binary.to_string();
        result += binary.to_string().substr(8 - secret_size_per_pixel);
        if (result.size() > 52) {

        }
        if (result.size() >= eol.length()) {
            auto div = result.size() % 8 % 3;
            auto possible_eol = result.substr(std::max((int) (result.size() - eol.length() - div), 0), eol.length());
            if (possible_eol == eol) {
                result.erase(result.length() - eol.length() - div, eol.length() + div);
                break;
            }
        }

        if (++color == 3) {
            color = 0;
            i++;
        }
    }

    return result;
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
    max_secret_chars = (secret_size_per_pixel * total_number_of_pixels) / 8 - eol.size();

    is_rgb = pixel_size % 3 == 0;
    color_count = is_rgb ? 3 : 4;

    uint8_t pixels[total_number_of_pixels][color_count];

    file.seekg(pixels_starting_position, std::fstream::beg);
    file.read(reinterpret_cast<char *>(&pixels), bmp_info_header.image_size);


    for (int64_t i = 0; i < total_number_of_pixels; i++) {
        pixel_data.reserve(total_number_of_pixels);
        auto &red = pixels[i][0];
        auto &green = pixels[i][1];
        auto &blue = pixels[i][2];
        const auto &alpha = is_rgb ? 255 : pixels[i][3];
        pixel_data.push_back({red, green, blue, alpha});
    }
}

void BMPImage::write_pixels() {

    auto file = open_file(std::ios::in | std::ios::out);

    uint8_t pixels[total_number_of_pixels][color_count];
    file.seekg(pixels_starting_position, std::fstream::beg);
    for (int i = 0; i < total_number_of_pixels; ++i) {
        pixels[i][0] = pixel_data[i][0];
        pixels[i][1] = pixel_data[i][1];
        pixels[i][2] = pixel_data[i][2];
        if (is_rgb) {
            pixels[i][3] = pixel_data[i][3];
        }
    }
    file.write(reinterpret_cast<char *>(&pixels), bmp_info_header.image_size);
    file.close();
}

std::fstream BMPImage::open_file(const int &mode) {
    return std::fstream(file_path, mode | std::ios::binary);
}
