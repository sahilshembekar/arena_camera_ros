#!/usr/bin/env python3


# NEEDED IF "catkin_python_setup" IS USED IN CMakeLists.txt

from distutils.core import setup
from catkin_pkg.python_setup import generate_distutils_setup

d = generate_distutils_setup(
    packages=['arena_camera'],
    package_dir={'': 'test_src'},
)
maps = d
setup(**maps)
