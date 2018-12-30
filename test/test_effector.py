import flom

def test_location_type(effector):
    assert isinstance(effector.location, flom.Location) or isinstance(effector.location, type(None))

def test_rotation_type(effector):
    assert isinstance(effector.rotation, flom.Rotation) or isinstance(effector.rotation, type(None))
