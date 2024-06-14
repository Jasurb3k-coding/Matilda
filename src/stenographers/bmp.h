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

    void encrypt() const;

private:
    BMPHeader bmp_header{};
    BMPInfoHeader bmp_info_header{};
    std::vector<std::array<int, 4>> pixel_data{};

    bool is_rgb{};
    uint32_t pixels_starting_position{};
    int32_t total_number_of_pixels{};
    int pixel_size{};
    int color_count{};

    void remove_red();

    void write_pixels();


    void read_bmp();

    std::fstream open_file(const int &mode = std::ios::in);

    void read_pixels();
};
