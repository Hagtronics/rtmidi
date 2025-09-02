cd build
sudo cmake .. 

echo "Building"
sudo make -j4

echo "Installing"
sudo make install
sudo ldconfig

echo "Done!"