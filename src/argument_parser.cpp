#include "argument_parser.h"
#include "core.h"
#include "utils.h"

auto get_command_from_string(const std::string &command_str) -> Command {
//  CLRFY: can I use --help instead of -help as was shown in the doc.
    static std::unordered_map<std::string, Command> CommandMap = {
            {"-h",        HELP},
            {"--help",    HELP},
            {"-i",        INFO},
            {"--info",    INFO},
            {"-e",        ENCRYPT},
            {"--encrypt", ENCRYPT},
            {"-d",        DECRYPT},
            {"-–decrypt", DECRYPT},
            {"-c",        CHECK},
            {"--check",   CHECK},
    };
    if (auto command = CommandMap.find(command_str); command != CommandMap.end()) {
        return command->second;
    } else {
        return INVALID;
    }
}

auto parse_arguments(int argc, const char *argv[]) -> std::pair<Command, std::vector<std::string>> {
    if (argc == 0) return {HELP, std::vector<std::string>()};

    std::string command_str = argv[1];
    Command command = get_command_from_string(command_str);

    auto rest_of_the_arguments = std::vector<std::string>();
    for (int i = 2; i < argc; ++i) {
        rest_of_the_arguments.emplace_back(argv[i]);
    }

    return {command, rest_of_the_arguments};
}