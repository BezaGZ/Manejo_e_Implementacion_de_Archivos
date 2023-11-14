cmake_minimum_required(VERSION 3.26)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled ejemplo2.c -I /opt/homebrew/Cellar/mysql-client/8.1.0/include -L /opt/homebrew/Cellar/mysql-client/8.1.0/lib -lmysqlclient)
