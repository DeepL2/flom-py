import pytest

import flom

@pytest.fixture(params=['sample.fom', 'empty.fom'])
def motion(request):
    return flom.load(f'test/data/{request.param}')

@pytest.fixture
def oneshot_motion(motion):
    # TODO: Use flom.LoopType.None_ or something like that
    motion.set_loop(getattr(flom.LoopType, 'None'))
    return motion

@pytest.fixture
def frame():
    return flom.Frame()

@pytest.fixture
def effector():
    return flom.Effector()
