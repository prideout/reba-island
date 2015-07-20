#include <fstream>
#include <spdlog/spdlog.h>

using namespace std;

int generate_island(const string& json_string);

int main(int argc, char** argv)
{
    auto console = spdlog::stdout_logger_mt("console");
    const char* kProcessName = argv[0];
    const char* kJsonFilename = argv[1];

    if (argc != 2) {
        console->error("usage: {} example.json\n", kProcessName);
        return 1;
    }

    ifstream json_in(kJsonFilename);
    if (not json_in) {
        console->error("Could not open {}.\n", kJsonFilename);
        return 1;
    }
    istreambuf_iterator<char> begin(json_in);
    istreambuf_iterator<char> end;
    return generate_island(string(begin, end));
}
