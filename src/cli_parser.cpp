// src/cli_parser.cpp
#include "../include/cli_parser.h"
#include <iostream>
#include <string>

CLIArgs parseCLIArgs(int argc, char* argv[]) {
    CLIArgs args;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--num_processes") {
            if (i + 1 < argc) {
                args.numProcesses = std::stoi(argv[i + 1]);
                i++;
            }
        } else if (arg == "--time_quantum") {
            if (i + 1 < argc) {
                args.timeQuantum = std::stoi(argv[i + 1]);
                i++;
            }
        } else if (arg == "--output_format") {
            if (i + 1 < argc) {
                std::string format = argv[i + 1];
                if (format == "csv" || format == "json") {
                    args.outputFormat = format;
                } else {
                    std::cerr << "Warning: Invalid output format. Using default 'csv'." << std::endl;
                }
                i++;
            }
        } else {
            std::cerr << "Warning: Unknown argument " << arg << std::endl;
        }
    }
    return args;
}
