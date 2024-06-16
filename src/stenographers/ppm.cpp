#include <iostream>
#include <fstream>
#include "ppm.h"
#include "../exceptions.h"
#include "../utils.h"
#include <string>
#include <algorithm>
#include <sstream>


PPMImage::PPMImage(const std::string &filePath) : ImageBase(filePath) {
    PPMImage::read_image();
}

void PPMImage::encrypt(const std::string &message) {
    validate_message(message);
    auto encrypted_message = get_bitset_from_string(message);
    write_encrypted_message_into_pixels(encrypted_message);
    persist_pixels();
    validate_written_image(message);
}

std::string PPMImage::decrypt() {
    auto lsb = get_LSB_string_from_pixel_data();
    auto message = get_string_from_bitset(lsb);
    return message;
}

void PPMImage::validate_written_image(const std::string &expected_message) {
    auto written_message = decrypt();
    if (written_message != expected_message) {
        error_write_failed();
    }
};

void PPMImage::validate_message(const std::string &message) const {
    is_valid_message(message);
    if (message.length() > max_secret_chars) {
        error_message_too_long(message.length(), max_secret_chars);
    };
}


void PPMImage::check_for_secret_message() const {
    get_LSB_string_from_pixel_data();
};


void PPMImage::check_if_message_can_be_written(const std::string &message) const {
    validate_message(message);
};

int PPMImage::get_max_secret_characters() const {
    return max_secret_chars;
}


void PPMImage::write_encrypted_message_into_pixels(std::string &encrypted) {
    encrypted += eol;
    int pixel = 0;
    int color = 0;
    for (int i = 0; i < encrypted.size(); i += secret_size_per_pixel) {
        replaceLSBs(pixel_data[pixel][color], encrypted.substr(i, secret_size_per_pixel));
        if (++color == 3) {
            color = 0;
            pixel++;
        }
    }
};

int PPMImage::replaceLSBs(int &value, const std::string &bitmap_str) {
    int bitmap = std::stoi(bitmap_str, nullptr, 2);
    bitmap <<= (secret_size_per_pixel - bitmap_str.size());
    int mask = ~((1 << secret_size_per_pixel) - 1);
    value = (value & mask) | (bitmap & ~mask);
    return value;
}

auto PPMImage::get_bitset_from_string(const std::string &input) -> std::string {
    std::string final_string = "";
    for (char c: input) {
        std::bitset<8> binary_char(c);
        final_string += binary_char.to_string();
    }
    return final_string;
}

auto PPMImage::get_string_from_bitset(const std::string &binaryString) -> std::string {
    std::string text = "";
    for (size_t i = 0; i < binaryString.size(); i += 8) {
        std::bitset<8> bits(binaryString.substr(i, 8));
        char character = static_cast<char>(bits.to_ulong());
        text += character;
    }
    return text;
}

bool PPMImage::is_last_char_supported(const std::string &result) const {
    if (result.size() < 8) return true;
    auto reminder = result.size() % 8;
    std::string latest_8_bit_segment = result.substr(result.size() - 8 - reminder, 8);
    char character = static_cast<char>(std::bitset<8>(latest_8_bit_segment).to_ulong());
    auto eol_possibilities = std::vector<std::string>{
            "11011010", "11001010", "11011110", "10111010"
    };
    auto is_eol_char = std::find(eol_possibilities.begin(), eol_possibilities.end(), latest_8_bit_segment) !=
                       eol_possibilities.end();
    return isalnum(character) || isspace(character) || is_eol_char;
}

std::string PPMImage::get_LSB_string_from_pixel_data() const {
    std::string result = "";
    std::string ev = "";
    auto color = 0;
    for (int i = 0; i < pixel_data.size();) {
        std::bitset<8> binary(pixel_data[i][color]);
        ev += binary.to_string();
        result += binary.to_string().substr(8 - secret_size_per_pixel);
        if (result.size() >= eol.length()) {
            auto div = result.size() % 8 % 3;
            auto possible_eol = result.substr(std::max((int) (result.size() - eol.length() - div), 0), eol.length());
            if (possible_eol == eol) {
                result.erase(result.length() - eol.length() - div, eol.length() + div);
                break;
            }
        }

        if (!is_last_char_supported(result)) {
            error_no_secret_message();
        }

        if (++color == 3) {
            color = 0;
            i++;
        }
    }

    return result;
}

int PPMImage::get_width() const {
    return (int) ppm_header.width;
}

int PPMImage::get_height() const {
    return (int) ppm_header.height;
}

void PPMImage::read_image() {
    auto file = open_file();
    file.seekg(0);
    std::string line;

    std::getline(file, line);
    std::istringstream iss(line);
    iss >> ppm_header.signature;

    file >> ppm_header.width >> ppm_header.height >> ppm_header.number_of_colors;
    file.ignore();
    file.ignore();

    pixels_starting_position = file.tellg();
    total_number_of_pixels = ppm_header.width * ppm_header.height;
    max_secret_chars = (secret_size_per_pixel * total_number_of_pixels) / 8 - eol.size();
    read_pixels(file);
    file.close();
}

//
void PPMImage::read_pixels(std::fstream& file) {
    file.seekg(pixels_starting_position);
    pixel_data.clear();
    pixel_data.reserve(total_number_of_pixels);

    for (int i = 0; i < total_number_of_pixels; ++i) {
        unsigned char rgb[3];
        file.read(reinterpret_cast<char *>(rgb), 3);
        pixel_data.push_back({rgb[0], rgb[1], rgb[2]});
    }
}

void PPMImage::persist_pixels() {
    auto file = open_file(std::ios::in | std::ios::out);
    file.seekg(pixels_starting_position, std::fstream::beg);
    for (const auto &pixel: pixel_data) {
        unsigned char rgb[3] = {static_cast<unsigned char>(pixel[0]),
                                static_cast<unsigned char>(pixel[1]),
                                static_cast<unsigned char>(pixel[2])};
        file.write(reinterpret_cast<char *>(rgb), 3);
    }
}

std::fstream PPMImage::open_file(const int &mode) {
    return std::fstream(file_path, mode | std::ios::binary);
}
