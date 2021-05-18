brew install gtkmm4
g++ main.cpp -o output `pkg-config gtkmm-4.0 --cflags --libs` -std=c++17
chmod +x output
./output