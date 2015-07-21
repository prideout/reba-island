import island
import os.path


def test_island():
    json = open('test/example.json').read()
    if os.path.exists('elevation.png'):
        os.unlink('elevation.png')
    island.generate(json)
    assert os.path.exists('elevation.png')
    os.unlink('elevation.png')
