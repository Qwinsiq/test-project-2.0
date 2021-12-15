#gtest_dep = [
#   dependency('gtest',main:true, version : '1.11.0'),
#    dependency('gmock', main:true, version : '1.11.0'),    
#    dependency('gmock_main', version: '1.11.0')
#]
dep=[
    dependency('gtest', main:true),
    dependency('gmock', main:true)
]
mock=include_directories('./Mock')
test=executable('test1', './source/MobileClientTest.cpp',include_directories:[inc, mock],dependencies:[net, dep])
test('test1', test)