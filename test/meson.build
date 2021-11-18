project('test', 'cpp')
subdir('MobileClient')
lib=dependency('sysrepo-cpp')
exe=executable('main_exe', 'main.cpp',include_directories:['./MobileClient/include'],dependencies:[net,lib])
