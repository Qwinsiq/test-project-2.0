dep=dependency('gtest', main:true)

e=executable('test1', 'ConcreteProductA1Test.cpp',
include_directories:[inc], dependencies:[dep, abstr_depend])

test('test',e)