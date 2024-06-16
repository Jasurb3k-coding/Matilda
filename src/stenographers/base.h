#include <string>
#include <fstream>
#include <vector>
#include <array>

class ImageBase {
public:
    explicit ImageBase(const std::string &filePath) : file_path(filePath) {}

    virtual int get_width() const = 0;

    virtual int get_height() const = 0;

    virtual int get_max_secret_characters() const = 0;

    virtual void check_if_message_can_be_written(const std::string &message) const = 0;

    virtual void check_for_secret_message() const = 0;

    virtual void encrypt(const std::string &message) = 0;

    virtual std::string decrypt() = 0;

protected:
    const std::string &file_path;

    virtual void persist_pixels() = 0;

    virtual void read_image() = 0;

    virtual std::fstream open_file(const int &mode = std::ios::in) = 0;

    virtual void read_pixels() = 0;
};