cmake_minimum_required(VERSION 3.30)
project(Laboratorul_3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Laboratorul_3 main.cpp
        Collection.h
        Transaction.h
        ATM.cpp
        ATM.h
        Collection.tpp
        Set.h
        Set.tpp
        Transaction.tpp
        Iterator.h
        Iterator.tpp
        ATM.tpp
)
