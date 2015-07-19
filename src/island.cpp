#include <fstream>
#include <spdlog/spdlog.h>
#include <OpenImageIO/imageio.h>
#include <OpenImageIO/array_view.h>
#include <rapidjson/document.h>
#include <glm/gtc/noise.hpp>

using namespace OIIO;
using namespace glm;
using namespace std;

static float noise_freq;

void render(array_view<float> buffer, int width, int height)
{
    const float coord_scale = 1.0f / width;
    float* ptr = buffer.data();
    for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {

        // Create a normalized texture coordinate.
        vec2 uv = vec2(x, y) * coord_scale;

        // Evaluate the noise function.
        float n = simplex(uv * noise_freq);

        // Transform the result from [-1, +1] to [0, 1].
        *ptr++ = 0.5 + 0.5 * n;
    } }
}

int main(int argc, char** argv)
{
    auto console = spdlog::stdout_logger_mt("console");
    const char* kProcessName = argv[0];
    const char* kJsonFilename = argv[1];
    const int kNumChannels = 1;

    if (argc != 2) {
        console->error("usage: {} example.json\n", kProcessName);
        return 1;
    }

    // Parse the JSON file.
    ifstream json_in(kJsonFilename);
    if (not json_in) {
        console->error("Could not open {}.\n", kJsonFilename);
        return 1;
    }
    istreambuf_iterator<char> begin(json_in);
    istreambuf_iterator<char> end;
    const string json_string(begin, end);
    rapidjson::Document terra;
    terra.Parse(json_string.c_str());
    if (terra.HasParseError()) {
        console->error("Failed to parse JSON: {}\n", terra.GetParseError());
        return 1;
    }
    const auto img_filename = terra["filename"].GetString();
    const int img_width = terra["width"].GetInt();
    const int img_height = terra["height"].GetInt();
    noise_freq = terra["frequency"].GetDouble();

    // Allocate and populate pixels.
    float pixels[img_width * img_height * kNumChannels];
    array_view<float> buffer(pixels, sizeof(pixels));
    render(buffer, img_width, img_height);

    // Describe the image format.
    ImageSpec spec(img_width, img_height, kNumChannels, TypeDesc::FLOAT);
    spec.channelnames[0] = "luminance";

    // Use OpenImageIO to write it out.
    ImageOutput* out = ImageOutput::create(img_filename);
    if (!out) {
        console->error("Unable to open {} for output.\n", img_filename);
        return 1;
    }
    out->open(img_filename, spec);
    out->write_image(TypeDesc::FLOAT, pixels);
    out->close();
    delete out;
    console->info("{} has been written.\n", img_filename);
}
