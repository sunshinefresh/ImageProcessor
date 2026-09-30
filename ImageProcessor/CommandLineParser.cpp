/**
 * @file CommandLineParser.cpp
 */

#include "CommandLineParser.h"
#include "Exceptions.h"

#include <iostream>
#include <string>

namespace ip {

namespace {
    /// argv 의 다음 인자를 안전하게 가져온다.
    std::string nextArg(int argc, char* argv[], int& i, const std::string& flag) {
        if (i + 1 >= argc) {
            throw ArgumentError(flag + ": missing value");
        }
        return argv[++i];
    }
} // anonymous namespace

ProgramOptions CommandLineParser::parse(int argc, char* argv[]) {
    ProgramOptions options;

    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];

        if (arg == "--input" || arg == "-i") {
            options.inputPath = nextArg(argc, argv, i, arg);
        }
        else if (arg == "--output" || arg == "-o") {
            options.outputPath = nextArg(argc, argv, i, arg);
        }
        else if (arg == "--filter" || arg == "-f") {
            options.filterName = nextArg(argc, argv, i, arg);
        }
        else if (arg == "--pipeline") {
            options.pipeline = nextArg(argc, argv, i, arg);
        }
        else if (arg == "--threads") {
            const std::string valueText =
                nextArg(argc, argv, i, arg);

            try {
                std::size_t parsedLength = 0;

                const int threadCount =
                    std::stoi(valueText, &parsedLength);

                if (
                    parsedLength != valueText.length() ||
                    threadCount <= 0
                    ) {
                    throw ArgumentError(
                        "--threads requires a positive integer"
                    );
                }

                options.threadCount =
                    static_cast<unsigned int>(threadCount);
            }
            catch (const ArgumentError&) {
                throw;
            }
            catch (const std::exception&) {
                throw ArgumentError(
                    "--threads requires a positive integer"
                );
            }
        }
        else if (arg == "--log") {
            options.logPath = nextArg(argc, argv, i, arg);
        }
        else if (arg == "--help" || arg == "-h") {
            printUsage(argv[0]);
            std::exit(0);
        }
        else {
            throw ArgumentError(
                "Unknown option: " + arg
            );
        }
    }

    if (options.inputPath.empty()) {
        throw ArgumentError(
            "--input is required"
        );
    }

    if (options.outputPath.empty()) {
        throw ArgumentError(
            "--output is required"
        );
    }

    if (
        options.filterName.empty() &&
        options.pipeline.empty()
        ) {
        throw ArgumentError(
            "--filter or --pipeline is required"
        );
    }

    if (
        !options.filterName.empty() &&
        !options.pipeline.empty()
        ) {
        throw ArgumentError(
            "--filter and --pipeline cannot be used together"
        );
    }

    return options;
}

void CommandLineParser::printUsage(const std::string& exeName) {
    std::cout
        << "Usage:\n"
        << "  " << exeName
        << " --input <path> --output <path> --filter <name> [options]\n"
        << "  " << exeName
        << " --input <path> --output <path> --pipeline <filters> [options]\n\n"

        << "Options:\n"
        << "  -i, --input     <path>      Input BMP file\n"
        << "  -o, --output    <path>      Output BMP file\n"
        << "  -f, --filter    <name>      Filter name\n"
        << "      --pipeline  <filters>   Comma-separated filters\n"
        << "      --threads   <count>     Number of worker threads\n"
        << "      --log       <path>      Log file path\n"
        << "  -h, --help                  Show help\n\n"

        << "Examples:\n"
        << "  " << exeName
        << " -i input.bmp -o result.bmp -f grayscale\n"

        << "  " << exeName
        << " -i input.bmp -o result.bmp -f threshold:128 --threads 4\n"

        << "  " << exeName
        << " -i input.bmp -o result.bmp"
        << " --pipeline \"grayscale,threshold:128\" --threads 4\n";
}

} // namespace ip
