import pytest

import flom

@pytest.fixture(params=['sample.fom', 'empty.fom'])
def motion(request):
    return flom.load(f'test/data/{request.param}')
