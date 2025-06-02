# A library with many techniques some consider to be unnatural

project(
  'dark-c++',
  'cpp',
  version : '0.1',
  meson_version : '>= 1.3.0',
  default_options : ['warning_level=3', 'cpp_std=c++23'],
)

dependencies = [
]

# These arguments are only used to build the shared library
# not the executables that use the library.
lib_args = ['-DBUILDING_DARK_C__']

lib = library(
  'dark-c++',
  'dark-c++.cpp',
  install : true,
  cpp_shared_args : lib_args,
  gnu_symbol_visibility : 'hidden',
  dependencies : dependencies,
)

test_exe = executable(
  'dark-c++_test',
  'dark-c++_test.cpp',
  dependencies : dependencies,
  link_with : lib,
)
test('dark-c++', test_exe)

# Make this library usable as a Meson subproject.
dark_cpp_dep = declare_dependency(
  include_directories : include_directories('.'),
  dependencies : dependencies,
  link_with : lib,
)
meson.override_dependency('dark-c++', dark_cpp_dep)

# Make this library usable from the system's
# package manager.
install_headers('dark-c++.hpp', subdir : 'dark-c++')

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  lib,
  description : 'Meson sample project.',
  subdirs : 'dark-c++',
)
