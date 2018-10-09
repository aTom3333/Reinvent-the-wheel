add_library(variant INTERFACE)
target_sources(variant INTERFACE
        ${CMAKE_SOURCE_DIR}/src/variant/variant.hpp
        ${CMAKE_SOURCE_DIR}/src/variant/detail/variant_data.hpp
        ${CMAKE_SOURCE_DIR}/src/variant/detail/variant_impl.hpp
        ${CMAKE_SOURCE_DIR}/src/variant/detail/variant_storage.hpp
        ${CMAKE_SOURCE_DIR}/src/variant/detail/variant_utilities.hpp
    )
target_compile_features(variant INTERFACE
        cxx_std_17)
target_include_directories(variant INTERFACE "${CMAKE_SOURCE_DIR}/src/variant")