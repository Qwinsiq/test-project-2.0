inc=include_directories('../include')

src= shared_library('src',sources:['ConcreteFactory1.cpp', 'ConcreteFactory2.cpp', 'ConcreteProductA1.cpp', 'ConcreteProductA2.cpp', 'ConcreteProductB1.cpp', 'ConcreteProductB2.cpp'],include_directories:[inc])

abstr_depend=declare_dependency(link_with:[src],include_directories:[inc])
