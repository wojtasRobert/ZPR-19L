#include <iostream>
#include <boost/program_options.hpp>

int main(int argc, char *argv[]) {
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("name", po::value<std::string>(), "set name");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if (vm.count("name")) {
        std::cout << "Hello, " << vm["name"].as<std::string>() << ".\n";
    } else {
        std::cout << "Hello, unknown.\n";
    }

    return 0;
}