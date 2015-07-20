#include <boost/python.hpp>
#include <spdlog/spdlog.h>

using namespace boost::python;
using namespace std;

int generate_island(const string& json_string);

static int wrap_generate(const string& json_string)
{
    auto console = spdlog::stdout_logger_mt("console");
    return generate_island(json_string);
}

BOOST_PYTHON_MODULE(island) {
    scope().attr("__doc__") = "an island generator";
    def("generate", wrap_generate, "create an island");
}
