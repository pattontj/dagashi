#!/bin/sh
g++  -o dagashi *.cpp src/*.cpp -rdynamic -Iinclude -Isrc -lsfml-system -lsfml-window -lsfml-graphics -lentityx -Wl,-rpath,/usr/local/lib /usr/local/lib/libsfml-system.so.2.5.1 /usr/local/lib/libsfml-window.so.2.5.1 /usr/local/lib/libsfml-graphics.so.2.5.1 
