def test_key_range_joint(motion):
    j1 = set(motion.joint_names())
    j2 = set(motion.frame_at(0).positions.keys())
    assert j1 == j2

def test_key_range_effector(motion):
    e1 = set(motion.effector_names())
    e2 = set(motion.frame_at(0).effectors.keys())
    assert e1 == e2

def test_frame_range(oneshot_motion):
    for i, frame in enumerate(oneshot_motion.frames(1)):
        assert frame == oneshot_motion.frame_at(i)

