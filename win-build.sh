#!/bin/sh
g++ -g -o build/dagashi main.cpp src/*.cpp src/system/*.cpp src/component/*.cpp src/world/*.cpp -Iinclude -Isrc -LC:/Users/sweetsbeats/Dagashi/lib -lsfml-system-2 -lsfml-window-2 -lsfml-graphics-2 -lentityx -ltmxlite
