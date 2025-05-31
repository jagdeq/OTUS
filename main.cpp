#include <iostream>

#include <boost/program_options.hpp>

#include "analyzer.hpp"
#include "consts.hpp"
#include "options.hpp"

namespace po = boost::program_options;
using namespace bayan;

int main(int argc, char** argv)
{
    Options opt;

    po::options_description desc("Allowed options");
    desc.add_options()
        // Справка
        ("help,h", "produce help message")
        // Список директорий для сканирования
        ("scan_dir,d", po::value<std::vector<std::string>>()->multitoken()->composing(),
         "list of directories to be scanned")
        // Список игнорируемых директорий
        ("ignor_dir,i", po::value<std::vector<std::string>>()->multitoken()->composing(), "list of ignored directories")
        // Список масок имен файлов для анализа
        ("mask,m", po::value<std::vector<std::string>>()->multitoken()->composing(),
         "filename mask [ex.: *.log, *.txt, ...]")
        // Минимальный размер файла для анализа
        ("file_size,s", po::value<size_t>()->required()->default_value(opt.m_fileBsize), "minimal file size in bytes")
        // Уровень сканирования
        ("level,l", po::value<size_t>()->required()->default_value(opt.m_level),
         "scannig level for all dir's, 0 - current dir")
        // Размер блока данных читаемых за раз
        ("block_size,S", po::value<size_t>()->required()->default_value(opt.m_blockBsize),
         "reading block size in bytes")
        // Используемая хэш-функция
        ("hash,H", po::value<std::string>()->required()->default_value(opt.m_hash),
         "hash function [md5, sha-1, sha-256]");

    po::variables_map vm;

    try {
        po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc;
            return 0;
        }

        if (vm.count("scan_dir"))
            opt.m_scanDirs = vm["scan_dir"].as<std::vector<std::string>>();

        if (vm.count("ignor_dir"))
            opt.m_ignoreDirs = vm["ignor_dir"].as<std::vector<std::string>>();

        if (vm.count("mask"))
            opt.m_masks = vm["mask"].as<std::vector<std::string>>();

        if (vm.count("file_size"))
            opt.m_fileBsize = vm["file_size"].as<size_t>();

        if (vm.count("level"))
            opt.m_level = vm["level"].as<size_t>();

        if (vm.count("block_size"))
            opt.m_blockBsize = vm["block_size"].as<size_t>();

        if (vm.count("hash")) {
            if (std::find(g_allowedHash.begin(), g_allowedHash.end(), vm["hash"].as<std::string>()) !=
                g_allowedHash.end())
                opt.m_hash = vm["hash"].as<std::string>();
            else {
                std::cout << desc;
                return 0;
            }
        }

        std::cout << "bayan started with params:\n";
        std::cout << opt;

    } catch (const po::error& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        std::cerr << desc << "\n";
        return 1;
    }

    Analyzer analyzer;
    analyzer.run(opt);

    return 0;
}
