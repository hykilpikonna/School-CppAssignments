# brew install gtk+3 gtkmm3
g++ `pkg-config --cflags --libs gtkmm-3.0` -c Run.cpp -o a.bin -std=c++17
