cmake_minimum_required(VERSION 3.30)
project(ECS)

set(CMAKE_CXX_STANDARD 20)

add_executable(ECS main.cpp
        Entity.h
        Components.h
        EntityManager.h
        IComponentArray.h
        ComponentManager.h
        System.h
        SparseSet.h
        TestSparseSet.cpp
        SystemManager.h
        Signature.h
        Coordinator.h
)
