#!/bin/bash

echo "HAVE YOU EXPANDED FILE SYSTEM? IF NOT: sudo raspi-config"
echo "INCREASED SWAP SPACE? IF NOT: sudo nano /etc/dphys-swapfile\n\
     CONF_SWAPSIZE=2048\n\
     sudo /etc/init.d/dphys-swapfile stop\n\
     sudo /etc/init.d/dphys-swapfile start"

# update system
sudo apt-get update
sudo apt-get upgrade -y

# install developer tools
sudo apt-get install build-essential cmake unzip pkg-config -y

# image and video I/O libraries
sudo apt-get install libjpeg-dev libpng-dev libtiff-dev -y
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev -y
sudo apt-get install libxvidcore-dev libx264-dev -y

# GTK for GUI backend
sudo apt-get install libgtk-3-dev -y

# package which may reduce pesky GTK warnings
sudo apt-get install libcanberra-gtk* -y

# mathematical optimizations for OpenCV
sudo apt-get install libatlas-base-dev gfortran -y

# Python 3 development headers
sudo apt-get install python3-dev -y

# download OpenCV with additional contrib modules
cd ~
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.0.0.zip
wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.0.0.zip

# unzip the archives
unzip opencv.zip
unzip opencv_contrib.zip

# rename the directories
mv opencv-4.0.0 opencv
mv opencv_contrib-4.0.0 opencv_contrib

# install pip
wget https://bootstrap.pypa.io/get-pip.py
sudo python3 get-pip.py

# install virtualenv and virtualenvwrapper
sudo pip install virtualenv virtualenvwrapper
sudo rm -rf ~/get-pip.py ~/.cache/pip

# update ~/.profile	
echo -e "\n# virtualenv and virtualenvwrapper" >> ~/.profile
echo "export WORKON_HOME=$HOME/.virtualenvs" >> ~/.profile
echo "export VIRTUALENVWRAPPER_PYTHON=/usr/bin/python3" >> ~/.profile
echo "source /usr/local/bin/virtualenvwrapper.sh" >> ~/.profile
source ~/.profile

# Create a virtual environment
mkvirtualenv cv -p python3
workon cv

# install NumPy
pip install numpy

#  create + enter a build  directory
cd ~/opencv
mkdir build
cd build

# configure the OpenCV 4 build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
    -D ENABLE_NEON=ON \
    -D ENABLE_VFPV3=ON \
    -D BUILD_TESTS=OFF \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D INSTALL_PYTHON_EXAMPLES=OFF \
    -D BUILD_EXAMPLES=OFF ..

# compile OpenCV 4
make -j4

# install OpenCV 4 
sudo make install
sudo ldconfig

# rename OpenCV python bindings
cd /usr/local/python/cv2/python-3.*
sudo mv cv2.cpython-3~ cv2.so

# sym-link our OpenCV cv2.so bindings into our cv virtual environment
cd ~/.virtualenvs/cv/lib/python3.*/site-packages/
ln -s /usr/local/python/cv2/python-3.*/cv2.so cv2.so

echo "DECREASED SWAP SPACE? IF NOT: sudo nano /etc/dphys-swapfile\n\
     CONF_SWAPSIZE=100\n\
     sudo /etc/init.d/dphys-swapfile stop\n\
     sudo /etc/init.d/dphys-swapfile start"