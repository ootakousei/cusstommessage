from setuptools import find_packages
from setuptools import setup

setup(
    name='can_packet',
    version='0.0.0',
    packages=find_packages(
        include=('can_packet', 'can_packet.*')),
)
