import pytest
import requests
import os

TIMEOUT = 5


@pytest.fixture(scope='module')
def renderfarm(request):
    from subprocess import Popen
    import time
    child = Popen(['python', 'src/server.py'])
    time.sleep(0.5)
    request.addfinalizer(lambda: child.terminate())
    return child


def test_server(renderfarm):
    payload = open('test/example.json').read()
    headers = {'content-type': 'application/json'}
    req = requests.post(
        'http://0.0.0.0:8082/render',
        data=payload,
        headers=headers)
    imgid = req.text
    path = imgid + '.png'
    assert os.path.exists(path)
    os.unlink(path)
