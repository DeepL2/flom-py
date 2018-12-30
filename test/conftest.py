import pytest

import flom

@pytest.fixture
def motion():
    return flom.load('test/data/sample.fom')
