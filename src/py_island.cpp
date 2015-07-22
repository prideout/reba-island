#include <memory>
#include <boost/python.hpp>
#include <spdlog/spdlog.h>

using namespace boost::python;
using namespace std;

int generate_island(const string& json_string);

static int wrap_generate(const string& json_string)
{
    return generate_island(json_string);
}

struct LibGuard {
    LibGuard() {
        spdlog::stdout_logger_mt("console");
    }
    ~LibGuard() {
    }
};

BOOST_PYTHON_MODULE(island) {
    scope().attr("__doc__") = "an island generator";
    def("generate", wrap_generate, "create an island");
    class_<LibGuard, shared_ptr<LibGuard>, boost::noncopyable>(
        "LibGuard", no_init);
    scope().attr("__libguard") = make_shared<LibGuard>();;

}
