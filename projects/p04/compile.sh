# brew install gtkmm4
g++ main.cpp -o output `pkg-config gtkmm-4.0 --cflags --libs` -std=c++2a
chmod +x output
./output