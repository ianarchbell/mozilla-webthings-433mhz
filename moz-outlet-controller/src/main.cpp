/*
  This example shows how to use a 433Mhz controller and devices through Mozilla Webthings.
  You need to use the advanced-receive example to find out the codes from your controller.
  Then you simply define the Mozilla WebThings as usual then add a proxy for each switch 
  or device using the RadioProxy class. Then enable the radio. The 433Mhz input and mapping of 
  Mozilla WebThing properties to device state is performed in the loop as shown below. 
  That's all that's required.

  // map a received code to relevant property
  RadioProxy::mapRadioStatus();
  // map all properties to radio status 
  RadioProxy::mapPropertyStatus();

  RadioProxy - Arduino libary for mapping 433Mhz devices and Mozilla
  WebThings. It uses RCSwitch for communication through the
  oddWires IoT-Bus 433Mhz board based on the Hope RFM69 module.
  Copyright (c) 2018 ian Archbell, oddWires.  All right reserved.

  Original RCSwitch project home: https://github.com/sui77/rc-switch/
  Also see copyright and license notices in RCSwitch sources.

  Project home for iot-bus: https://github.com/iot-bus/rc-switch/

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Arduino.h>
#include <Thing.h>
#include <WebThingAdapter.h>
#include "RadioProxy.h"

//TODO: Hardcode your WiFi credentials here (and keep it private)
const char* ssid = "NETGEAR96";
const char* password = "phoebe1984";

WebThingAdapter* adapter;

const char* sensorTypes[] = {"binarySensor", nullptr};
ThingDevice radioSwitch("OutletController", "IoT-Bus 433Mhz Outlet Controller", sensorTypes);
ThingProperty switch1("Control 1", "433Mhz Outlet Control 1", BOOLEAN, "BooleanProperty");
ThingProperty switch2("Control 2", "433Mhz Outlet Control 2", BOOLEAN, "BooleanProperty");
ThingProperty switch3("Control 3", "433Mhz Outlet Control 3", BOOLEAN, "BooleanProperty");

// Proxies for the controller 3 on and off buttons
// Protocols are automatically decoded provided they are supported by RCSwitch
// Look in Protocols.h for the protocol table
// If you run this example you will see any supported device code printed in the serial monitor 
// together with its characteristics
// PROXY_INPUT radio reception, property reference, on code, off code
RadioProxy proxy1(PROXY_INPUT, &switch1, 5264691, 5264700);
RadioProxy proxy2(PROXY_INPUT, &switch2, 5264835, 5264844);
RadioProxy proxy3(PROXY_INPUT, &switch3, 5265155, 5265164);

ThingDevice outlet1("Outlet 1", "IoT-Bus 433Mhz Outlet", sensorTypes);
ThingProperty power1("Power", "433Mhz Outlet 1", BOOLEAN, "BooleanProperty");
ThingDevice outlet2("Outlet 2", "IoT-Bus 433Mhz Outlet", sensorTypes);
ThingProperty power2("Power", "433Mhz Outlet 2", BOOLEAN, "BooleanProperty");
ThingDevice outlet3("Outlet 3", "IoT-Bus 433Mhz Outlet", sensorTypes);
ThingProperty power3("Power", "433Mhz Outlet 3", BOOLEAN, "BooleanProperty");

// Proxies for the three outlets
// PROXY_OUTPUT radio transmission, property reference, on code, off code, bit length, pulse length, protocol, repetitions
// Most devices are protocol 1, pulse length varies a lot, bit length is usually 24, reppetitions 10 is usually OK
RadioProxy proxy1o(PROXY_OUTPUT, &power1, 5264691, 5264700, 24, 184, 1, 10);
RadioProxy proxy2o(PROXY_OUTPUT, &power2, 5264835, 5264844, 24, 184, 1, 10);
RadioProxy proxy3o(PROXY_OUTPUT, &power3, 5265155, 5265164, 24, 184, 1, 10);

void setup() {
  Serial.begin(115200);

  // Start WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Initialize MOZ IoT adapter
  adapter = new WebThingAdapter("adapter", WiFi.localIP());
  
  // Initialize MOZ IoT controller
  radioSwitch.addProperty(&switch1);
  radioSwitch.addProperty(&switch2);
  radioSwitch.addProperty(&switch3);
  adapter->addDevice(&radioSwitch);

  // Initialize MOZ IoT outlets
  outlet1.addProperty(&power1);
  adapter->addDevice(&outlet1);
  outlet2.addProperty(&power2);
  adapter->addDevice(&outlet2);
  outlet3.addProperty(&power3);
  adapter->addDevice(&outlet3);
 
  // RadioProxy::enableRadio(4, true); // data pin, verbose 
  RadioProxy::enableRadio(4, true);
  // start the adapter
  adapter->begin();   
}

void loop() {
  // map a received code to relevant property
  RadioProxy::mapRadioStatus();
  // map all properties to radio status 
  RadioProxy::mapPropertyStatus();
}





