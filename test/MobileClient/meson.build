inc=include_directories('./include', './source')
stc=static_library('stc',sources:['./source/NetConfAgent.cpp'],include_directories:[inc])
net=declare_dependency(link_with:[stc],include_directories:[inc])