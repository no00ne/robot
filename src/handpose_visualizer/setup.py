from setuptools import setup

package_name = 'handpose_visualizer'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    install_requires=['setuptools'],
    zip_safe=True,
    author='you',
    description='Visualizer for hand flange vs robot pose in RViz2',
    entry_points={
        'console_scripts': [
            'handpose_visualizer = handpose_visualizer.visualizer_node:main',
        ],
    },
)
