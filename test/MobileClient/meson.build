inc=include_directories('./include', './source')
lib=dependency('sysrepo-cpp')
stc=static_library('stc',sources:['./source/NetConfAgent.cpp'],include_directories:[inc],dependencies:[lib])
net=declare_dependency(link_with:[stc],include_directories:[inc])