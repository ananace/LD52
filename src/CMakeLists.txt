file(GLOB SOURCES
    Components/*.cpp
    Components/*.hpp
    Drawables/*.cpp
    Drawables/*.hpp
    States/*.cpp
    States/*.hpp
    Systems/*.cpp
    Systems/*.hpp

    *.cpp
    *.hpp
)

add_executable(LD52 ${SOURCES})
set_target_properties(LD52 PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

set(SFML_COMPONENTS Audio Graphics System Window)
if (WINDOWS)
    set (SFML_COMPONENTS ${SFML_COMPONENTS} Main)
endif()

find_package(EnTT REQUIRED)
find_package(SFML 3 REQUIRED COMPONENTS ${SFML_COMPONENTS})

target_compile_features(LD52 PRIVATE cxx_std_17)
target_link_libraries(LD52 PRIVATE
    EnTT::EnTT
    SFML::Audio
    SFML::Graphics
    SFML::System
    SFML::Window
)
if (WINDOWS)
    target_link_libraries(LD52 PRIVATE
        SFML::Main
    )
endif()

install(TARGETS LD52)
