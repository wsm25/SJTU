cmake_minimum_required (VERSION 3.10)
project(score-manager)

aux_source_directory(. DIR_SRCS)
add_executable(score-manager ${DIR_SRCS})