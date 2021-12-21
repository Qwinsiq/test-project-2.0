project('test', 'cpp', default_options : ('cpp_std=c++2a'))
subdir('MobileClient')
exe=executable('main_exe', 'main.cpp',include_directories:['./MobileClient/include'],dependencies:[net,lib,lib1])
#subdir('Test')