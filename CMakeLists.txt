cmake_minimum_required(VERSION 3.21)
project(ArtificialEvolution2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Ofast")

add_executable(ArtificalEvolution2 src/main.cpp src/Cell.h src/Creature.h src/Genome.h src/World.h src/WorldDrawer.h src/vector2.h src/Random.h src/Statistics.h src/Genes/GenFactory.h src/Genes/GrowthGenFactory.h src/Genes/PhotosynthesisGenFactory.h src/Genes/SeparateGenFactory.h src/Genes/GenomeFactory.h src/Genes/EatCellGenFactory.h)

# include sfml
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED system window graphics)

target_link_libraries(ArtificalEvolution2 ${SFML_LIBRARIES})

include_directories(${SFML_INCLUDE_DIR})

file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../lib/*.dll")
file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})

# copy resources
file(COPY fonts DESTINATION ${CMAKE_BINARY_DIR})