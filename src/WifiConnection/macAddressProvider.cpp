#include "wifiConnection/macAddressProvider.h"

MacAddressProvider::MacAddressProvider(){
    retrieveMacAddress();
}

String MacAddressProvider::getMacAddress(){
    return macAddress;
}

void MacAddressProvider::retrieveMacAddress(){
    macAddress = WiFi.macAddress();
}