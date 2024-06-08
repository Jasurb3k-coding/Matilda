#include "src/argument_parser.h"
#include "src/core.h"
#include "src/exceptions.h"
#include "src/utils.h"

int main(int argc, const char *argv[]) {
    auto [command, arguments] = parse_arguments(argc, argv);
    switch (command) {
        case ENCRYPT:
            encrypt_message_into_picture(arguments);
            break;
        case DECRYPT:
            decrypt_message_from_picture(arguments);
            break;
        case CHECK:
            check(arguments);
            break;
        case HELP:
            print_help();
            break;
        case INFO:
            get_info_about_image(arguments);
            break;
        case INVALID:
            error_unrecognized_command(argv[1]);
            break;
    }
}
