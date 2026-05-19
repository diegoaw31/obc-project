# ####
# # F Prime CMakeLists.txt:
# #
# # SOURCES: list of source files (to be compiled)
# # AUTOCODER_INPUTS: list of files to be passed to the autocoders
# # DEPENDS: list of libraries that this module depends on
# #
# # More information in the F´ CMake API documentation:
# # https://fprime.jpl.nasa.gov/latest/docs/reference/api/cmake/API/
# #
# ####

# # Module names are derived from the path from the nearest project/library/framework
# # root when not specifically overridden by the developer, i.e. the module defined by
# # `MyProj/Some/Path/CMakeLists.txt` will be named `MyProj_Some_Path`.

# set(SOURCE_FILES
#     "${CMAKE_CURRENT_LIST_DIR}/ServoComponent.fpp"
#     "${CMAKE_CURRENT_LIST_DIR}/ServoComponent.cpp"
# )

# set(MOD_DEPS
#     ObcProject_Ports
#     pigpio::pigpio
#     Threads::Threads
# )

# register_fprime_module()

# register_fprime_library(
#     AUTOCODER_INPUTS
#         # "${CMAKE_CURRENT_LIST_DIR}/../../Ports/ServoPorts.fpp"
#         "${CMAKE_CURRENT_LIST_DIR}/ServoComponent.fpp"
#     SOURCES
#         "${CMAKE_CURRENT_LIST_DIR}/ServoComponent.cpp"
#     DEPENDS
#         ObcProject_Ports
#         pigpio::pigpio
#         Threads::Threads
# )

# ### Unit Tests ###
# # register_fprime_ut(
# #     AUTOCODER_INPUTS
# #         "${CMAKE_CURRENT_LIST_DIR}/ServoComponent.fpp"
# #     SOURCES
# #         "${CMAKE_CURRENT_LIST_DIR}/test/ut/ServoComponentTestMain.cpp"
# #         "${CMAKE_CURRENT_LIST_DIR}/test/ut/ServoComponentTester.cpp"
# #     DEPENDS
# #         STest # For rules-based testing
# #     UT_AUTO_HELPERS
# # )
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/ServoComponent.fpp"
    "${CMAKE_CURRENT_LIST_DIR}/ServoComponent.cpp"
)

set(MOD_DEPS
    ObcProject_Ports
    pigpio::pigpio
    Threads::Threads
)

register_fprime_module()

### Unit Tests ###
# register_fprime_ut(
#     AUTOCODER_INPUTS
#         "${CMAKE_CURRENT_LIST_DIR}/ServoComponent.fpp"
#     SOURCES
#         "${CMAKE_CURRENT_LIST_DIR}/test/ut/ServoComponentTestMain.cpp"
#         "${CMAKE_CURRENT_LIST_DIR}/test/ut/ServoComponentTester.cpp"
#     DEPENDS
#         STest
#     UT_AUTO_HELPERS
# )