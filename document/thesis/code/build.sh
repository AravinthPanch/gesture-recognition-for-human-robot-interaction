# Clone the source repository
git clone git@github.com:AravinthPanch/gesture-recognition
				-for-human-robot-interaction.git ~/hri

# Install dependencies on Mac OSX
xcode-select --install
brew update; brew install git boost cmake 

cd ~/hri/source/human-robot-interaction
sudo cp lib/OpenNI2/libOpenNI2.dylib /usr/lib
sudo cp lib/NiTE2/libNiTE2.dylib /usr/lib
sudo cp lib/NiTE2/NiTE.ini /usr/lib
sudo cp -R lib/NiTE2/NiTE2 /usr/lib

# Install dependencies on 64-bit Ubuntu
sudo apt-get update
sudo apt-get install git build-essential cmake libboost-all-dev

cd ~/hri/source/human-robot-interaction
sudo cp lib/OpenNI2/libOpenNI2.so /usr/lib
sudo cp lib/NiTE2/libNiTE2.so /usr/lib
sudo cp lib/NiTE2/NiTE.ini /usr/lib
sudo cp -R lib/NiTE2/NiTE2 /usr/lib

# On OpenNAO / NAO OS
cd /source/human-robot-interaction
sudo cp lib/NiTE2/libNiTE2-32.so /usr/lib/libNiTE2.so
sudo cp lib/NiTE2/NiTE.ini /usr/lib
sudo cp -R lib/NiTE2/NiTE2 /usr/lib

# Build it on Mac OSX / Ubuntu / OpenNAO
cd ~/hri/source/human-robot-interaction
mkdir build; cd build
cmake ..
make