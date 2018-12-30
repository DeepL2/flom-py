import flom

from tempfile import NamedTemporaryFile


def test_dump_load(motion):
    with NamedTemporaryFile() as f:
        motion.dump(f.name)
        loaded = flom.load(f.name)

    assert loaded == motion
