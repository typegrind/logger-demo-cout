
include_directories(../include) 
include_directories(${GTEST_INCLUDE_DIR})

add_executable(typegrind-logger-demo_cout-tests 
  BasicUsageTest.cpp
)
target_link_libraries(typegrind-logger-demo_cout-tests ${TYPEGRIND_GTEST_LIBRARIES} typegrind-logger-demo_cout)
set_property(TARGET typegrind-logger-demo_cout-tests PROPERTY CXX_STANDARD 14)
