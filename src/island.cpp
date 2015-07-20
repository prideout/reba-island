#include <spdlog/spdlog.h>
#include <OpenImageIO/imageio.h>
#include <OpenImageIO/array_view.h>
#include <rapidjson/document.h>
#include <glm/gtc/noise.hpp>

namespace edt {
    #include <felzenszwalb/misc.h>
    #include <felzenszwalb/dt.h>
}

using namespace OIIO;
using namespace glm;
using namespace std;

#define NUM_OCTAVES 3

static float noise_freq[NUM_OCTAVES];
static float noise_ampl[NUM_OCTAVES];
static float sealevel;
static float seed;

static void render(array_view<float> buffer, int width, int height)
{
    const float coord_scale = 1.0f / width;
    float* ptr = buffer.data();
    for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {

        // Create a normalized texture coordinate.
        vec2 uv = vec2(x, y) * coord_scale;

        // Poor man's distance field.
        float m = 0.707 - distance(uv, vec2(0.5));

        // Each noise function gets back a value in [-1, +1].
        uv += vec2(seed);
        for (int i = 0; i < NUM_OCTAVES; i++) {
            m += noise_ampl[i] * simplex(uv * noise_freq[i]);
        }

        // Apply the step function.
        m -= sealevel;
        *ptr++ = m < 0.0f ? INF : 0;
    } }

    // Compute a distance field.
    int num_bytes = width * height * sizeof(float);
    edt::image<float> distance_field(width, height, true);
    memcpy(distance_field.data, buffer.data(), num_bytes);
    edt::dt(&distance_field);

    // Draw radiating lines.
    float* src = distance_field.data;
    float* dst = buffer.data();
    for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
        float s = *src++;
        float& d = *dst++;
        s = sqrt(s) * coord_scale;
        if (d > 0.0f) {
            d = 1.0f - float(int(s * 100.0) % 2) / (s * 100.0f);
        }
    } }
}

int generate_island(const string& json_string)
{
    auto console = spdlog::get("console");
    const int kNumChannels = 1;

    rapidjson::Document doc;
    doc.Parse(json_string.c_str());
    if (doc.HasParseError()) {
        console->error("Failed to parse JSON: {}\n", doc.GetParseError());
        return 1;
    }
    const auto img_filename = doc["filename"].GetString();
    const int img_width = doc["width"].GetInt();
    const int img_height = doc["height"].GetInt();
    const rapidjson::Value& noise = doc["noise_octaves"];
    for (int i = 0; i < NUM_OCTAVES; i++) {
        noise_freq[i] = noise["frequencies"][i].GetDouble();
        noise_ampl[i] = noise["amplitudes"][i].GetDouble();
    }
    sealevel = doc["sealevel"].GetDouble();
    seed = doc["seed"].GetDouble();

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
    return 0;
}
