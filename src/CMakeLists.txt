set(target ${MP2_CUSTOM})

file(GLOB hdrs "*.h*" "${MP2_INCLUDE}/*.h*")
file(GLOB srcs "*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs})
target_include_directories(${target} PRIVATE ${MP2_INCLUDE})