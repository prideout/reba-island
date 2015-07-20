import island
import os.path

JSON = '''
{
    "filename": "elevation.png",
    "width": 512,
    "height": 512,
    "noise_octaves": {
        "frequencies": [3.0, 10.0, 20.0],
        "amplitudes": [0.1, 0.05, 0.025]
    },
    "seed": 7,
    "sealevel": 0.4
}
'''


def test_island():
    if os.path.exists('elevation.png'):
        os.unlink('elevation.png')
    island.generate(JSON)
    assert os.path.exists('elevation.png')
    os.unlink('elevation.png')
