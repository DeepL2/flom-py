def test_positions_type(frame):
    assert isinstance(frame.positions, dict)

def test_effectors_type(frame):
    assert isinstance(frame.effectors, dict)
