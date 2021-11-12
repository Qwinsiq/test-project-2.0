project('protobuf task','cpp')
dep=dependency('protobuf', required:false)
protoc=find_program('protoc', required:false)

gen=generator(protoc,
output:['@BASENAME@.pb.cpp','@BASENAME@pb.h'],
arguments:['--proto_path=@CURRENT_SOURCE_DIR@', '--cpp_out=@BUILD_DIR@', '@INPUT@'])

genereted=gen.process('schema/task_info.proto')
e=executable('prog','main.cpp',genereted,dependencies:[dep])
