cmake_minimum_required(VERSION 3.16)

project(cwk2 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts Sql)
qt_standard_project_setup()

qt_add_executable(watersampletool
    main.cpp
    water_sample.cpp
    dataset.cpp
    table_model.cpp
    pollutant_line_chart.cpp
    window.cpp
    navbar.cpp
    custom_proxy_model.cpp
    pages/page.cpp
    pages/compliance_dashboard.cpp
    pages/data_page.cpp
    pages/environmental_litter_indicators.cpp
    pages/fluorinated_compounds.cpp
    pages/home.cpp
    pages/persistent_organic_pollutants.cpp
    pages/pollutant_overview.cpp

)

target_link_libraries(watersampletool PRIVATE Qt6::Widgets Qt6::Charts Qt6::Sql)

set_target_properties(watersampletool PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE OFF
)

file(COPY data DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY statics DESTINATION ${CMAKE_BINARY_DIR}/)
