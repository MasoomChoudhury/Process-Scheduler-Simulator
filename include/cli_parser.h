// include/cli_parser.h
#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <string>

struct CLIArgs {
    int numProcesses = 50;
    int timeQuantum = 4;
    std::string outputFormat = "csv"; // Default output format
};

CLIArgs parseCLIArgs(int argc, char* argv[]);

#endif // CLI_PARSER_H
