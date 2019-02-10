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
ThingDevice radioSwitch("LightController", "IoT-Bus 433Mhz Light Controller", sensorTypes);
ThingProperty switch1("Control 1", "433Mhz Light Control 1", BOOLEAN, "BooleanProperty");
ThingProperty switch2("Control 2", "433Mhz Light Control 2", BOOLEAN, "BooleanProperty");
ThingProperty switch3("Control 3", "433Mhz Light Control 3", BOOLEAN, "BooleanProperty");
ThingProperty switch4("Control 4", "433Mhz Light Control 4", BOOLEAN, "BooleanProperty");

// Proxies for the controller 3 on and off buttons
// Protocols are automatically decoded provided they are supported by RCSwitch
// Look in Protocols.h for the protocol table
// If you run this example you will see any supported device code printed in the serial monitor 
// together with its characteristics
// PROXY_INPUT radio reception, property reference, on code, off code
RadioProxy proxy1(PROXY_INPUT, &switch1, 1135923, 1135932);
RadioProxy proxy2(PROXY_INPUT, &switch2, 1136067, 1136076);
RadioProxy proxy3(PROXY_INPUT, &switch3, 1136387, 1136396);
RadioProxy proxy4(PROXY_INPUT, &switch4, 1137923, 1137932);

ThingDevice Light1("Light 1", "IoT-Bus 433Mhz Light 1", sensorTypes);
ThingProperty light1("light", "433Mhz Light 1", BOOLEAN, "BooleanProperty");
ThingDevice Light2("Light 2", "IoT-Bus 433Mhz Light 2", sensorTypes);
ThingProperty light2("light", "433Mhz Light 2", BOOLEAN, "BooleanProperty");
ThingDevice Light3("Light 3", "IoT-Bus 433Mhz Light 3", sensorTypes);
ThingProperty light3("light", "433Mhz Light 3", BOOLEAN, "BooleanProperty");
ThingDevice Light4("Light 4", "IoT-Bus 433Mhz Light 4", sensorTypes);
ThingProperty light4("light", "433Mhz Light 3", BOOLEAN, "BooleanProperty");

// Proxies for the three Lights
// PROXY_OUTPUT radio transmission, property reference, on code, off code, bit length, pulse length, protocol, repetitions
// Most devices are protocol 1, pulse length varies a lot, bit length is usually 24, reppetitions 10 is usually OK
RadioProxy proxy1o(PROXY_OUTPUT, &light1, 1135923, 1135932, 24, 168, 1, 10);
RadioProxy proxy2o(PROXY_OUTPUT, &light2, 1136067, 1136076, 24, 168, 1, 10);
RadioProxy proxy3o(PROXY_OUTPUT, &light3, 1136387, 1136396, 24, 168, 1, 10);
RadioProxy proxy4o(PROXY_OUTPUT, &light4, 1137923, 1137932, 24, 168, 1, 10);

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
  radioSwitch.addProperty(&switch4);
  adapter->addDevice(&radioSwitch);

  // Initialize MOZ IoT Lights
  Light1.addProperty(&light1);
  adapter->addDevice(&Light1);
  Light2.addProperty(&light2);
  adapter->addDevice(&Light2);
  Light3.addProperty(&light3);
  adapter->addDevice(&Light3);
  Light4.addProperty(&light4);
  adapter->addDevice(&Light4);
 
  // Start the radio
  RadioProxy::begin(true); // verbose
  // start the adapter
  adapter->begin();   
}

void loop() {
  // map a received code to relevant property
  // map all properties to radio status 
  RadioProxy::update();
}





