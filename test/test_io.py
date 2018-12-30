import flom

from tempfile import NamedTemporaryFile


def test_dump_load(motion):
    with NamedTemporaryFile() as f:
        motion.dump(f.name)
        loaded = flom.load(f.name)

    assert loaded == motion

def test_dump_load_json(motion):
    with NamedTemporaryFile() as f:
        motion.dump_json(f.name)
        loaded = flom.load_json(f.name)

    assert loaded == motion
