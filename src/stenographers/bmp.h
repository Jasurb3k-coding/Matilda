#include <string>
#include <fstream>

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

struct BMPImage {
    const std::string &file_path;

    explicit BMPImage(const std::string &filePath);

    int get_width() const;

    int get_height() const;

    int get_max_secret_characters() const;

    void encrypt(const std::string &message);

    std::string decrypt();

private:
    BMPHeader bmp_header{};
    BMPInfoHeader bmp_info_header{};
    std::vector<std::array<int, 4>> pixel_data{};

    static auto get_bitset_from_string(const std::string &input) -> std::string;
    std::string get_LSB_string_from_pixel_data();
    auto get_string_from_bitset(const std::string& binaryString) -> std::string;

    int replaceLSBs(int &value, const std::string &bitmap_str);
    void write_encrypted_message_into_pixels(std::string &encrypted);
    void validate_written_image(const std::string &expected_message);
    void validate_message(const std::string &message);

    bool is_rgb{};
    uint32_t pixels_starting_position{};
    int32_t total_number_of_pixels{};
    int pixel_size{};
    int secret_size_per_pixel{};
    int max_secret_chars{};
    int color_count{};

    void persist_pixels();


    void read_bmp();

    std::fstream open_file(const int &mode = std::ios::in);

    void read_pixels();
};
