from distutils.core import setup, Extension

module1 = Extension('RangeFinder_C', sources = ['hellomodule.c'])

setup (name = 'PackageName',
	version = '1.0',
	description = 'Time of Flight IR distance sensor C functions',
	ext_modules = [module1])

