add_compile_definitions(
    BOOST_ERROR_CODE_HEADER_ONLY

)
add_library(boost INTERFACE)

target_include_directories(boost
                           INTERFACE
                           "boost")
