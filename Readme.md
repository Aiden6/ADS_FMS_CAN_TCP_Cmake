##### PRE INSTALL 
```
sudo apt-get install libusb-dev
sudo apt-get install libusb-1.0-0-dev
```
##### copy file to your /usr/lib
```
libusbcan.so libusbcan.so.1
```
##### STEP1
```
cmake .
```
##### STEP2
```
make
```
##### STEP3
```
sudo./ADS_FMS_OTA
```
