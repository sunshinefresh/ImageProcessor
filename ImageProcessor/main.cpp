/**
 * @file main.cpp
 * @brief ImageProcessor 진입점 — 지원자가 작성해야 할 파일입니다.
 *
 * BMP 입출력과 커맨드라인 파싱은 제공된 코드가 처리합니다.
 * 본 과제에서 작성해야 할 것은 단 하나입니다:
 *
 *     ▶ 이미지 처리 필터 2개 이상 구현 + main 의 TODO 위치에 연결
 *
 * 또한 일관된 컨벤션과 예외 처리, 메모리 안정성도 함께 평가됩니다.
 */

#include "BmpParser.h"
#include "CommandLineParser.h"
#include "Exceptions.h"
#include "FilterFactory.h"
#include "ImageBuffer.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

int main(int argc, char* argv[]) {
    std::string logPath;

    try {
        const ip::ProgramOptions options =
            ip::CommandLineParser::parse(argc, argv);

        logPath = options.logPath;

        const auto startTime =
            std::chrono::steady_clock::now();

        ip::ImageBuffer image =
            ip::BmpParser::loadFromFile(options.inputPath);

        std::cout
            << "Loaded: "
            << image.width()
            << " x "
            << image.height()
            << "\n";

        if (!options.filterName.empty()) {
            std::unique_ptr<ip::FilterBase> filter =
                ip::FilterFactory::create(
                    options.filterName
                );

            filter->apply(
                image,
                options.threadCount
            );
        }
        else {
            std::stringstream pipelineStream(
                options.pipeline
            );

            std::string filterName;

            while (
                std::getline(
                    pipelineStream,
                    filterName,
                    ','
                )
                ) {
                if (filterName.empty()) {
                    throw ip::FilterError(
                        "Pipeline contains an empty filter"
                    );
                }

                std::unique_ptr<ip::FilterBase> filter =
                    ip::FilterFactory::create(
                        filterName
                    );

                filter->apply(
                    image,
                    options.threadCount
                );
            }
        }

        ip::BmpParser::saveToFile(
            options.outputPath,
            image
        );

        const auto endTime =
            std::chrono::steady_clock::now();

        const auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                endTime - startTime
            ).count();

        if (!options.logPath.empty()) {
            std::ofstream logFile(
                options.logPath,
                std::ios::app
            );

            if (!logFile) {
                throw ip::FilterError(
                    "Failed to open log file"
                );
            }

            logFile
                << "input=" << options.inputPath << "\n"
                << "output=" << options.outputPath << "\n";

            if (!options.filterName.empty()) {
                logFile
                    << "filter="
                    << options.filterName
                    << "\n";
            }
            else {
                logFile
                    << "pipeline="
                    << options.pipeline
                    << "\n";
            }

            logFile
                << "threads="
                << options.threadCount
                << "\n"
                << "elapsed_ms="
                << elapsed
                << "\n"
                << "status=success\n\n";
        }

        std::cout
            << "Saved:  "
            << options.outputPath
            << "\n";

        return 0;
    }
    catch (const ip::ArgumentError& e) {
        if (!logPath.empty()) {
            std::ofstream logFile(
                logPath,
                std::ios::app
            );

            if (logFile) {
                logFile
                    << "status=failed\n"
                    << "error=" << e.what()
                    << "\n\n";
            }
        }

        std::cerr << e.what() << "\n\n";

        ip::CommandLineParser::printUsage(
            argc > 0 ? argv[0] : "ImageProcessor"
        );

        return 4;
    }
    catch (const ip::BmpParseError& e) {
        if (!logPath.empty()) {
            std::ofstream logFile(
                logPath,
                std::ios::app
            );

            if (logFile) {
                logFile
                    << "status=failed\n"
                    << "error=" << e.what()
                    << "\n\n";
            }
        }

        std::cerr << e.what() << std::endl;
        return 2;
    }
    catch (const ip::FilterError& e) {
        if (!logPath.empty()) {
            std::ofstream logFile(
                logPath,
                std::ios::app
            );

            if (logFile) {
                logFile
                    << "status=failed\n"
                    << "error=" << e.what()
                    << "\n\n";
            }
        }

        std::cerr << e.what() << std::endl;
        return 3;
    }
    catch (const std::exception& e) {
        if (!logPath.empty()) {
            std::ofstream logFile(
                logPath,
                std::ios::app
            );

            if (logFile) {
                logFile
                    << "status=failed\n"
                    << "error=" << e.what()
                    << "\n\n";
            }
        }

        std::cerr
            << "Unexpected error: "
            << e.what()
            << std::endl;

        return 1;
    }
}