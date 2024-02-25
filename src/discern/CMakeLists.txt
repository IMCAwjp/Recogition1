cmake_minimum_required(VERSION 3.8)
project(discern)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

########
##find##
########

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

#######
#build#
#######

ament_auto_add_library(${PROJECT_NAME} SHARED
  DIRECTORY src
)

rclcpp_components_register_node(${PROJECT_NAME}
  PLUGIN Identify::Id_node
  EXECUTABLE ${PROJECT_NAME}_node
)
 

######
#test#
######

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
 
  set(ament_cmake_copyright_FOUND TRUE)
  
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()


#########
#install#
#########
ament_auto_package(
  INSTALL_TO_SHARE
  config
  launch
)