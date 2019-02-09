/*
  This example shows how to use a 433Mhz controller and devices through Mozilla Webthings.
  You need to use the advanced-receive example to find out the codes from your controller.
  Then you simply define the Mozilla WebThings as usual then add a proxy for each buttonPtoperty 
  or device using the RadioProxy class. Then enable the radio. The 433Mhz input and mapping of 
  Mozilla WebThing properties to device state is performed in the loop as shown below. 
  That's all that's required.

  // map a received code to relevant property
  RadioProxy::mapRadioStatus();
  // map all properties to radio status 
  RadioProxy::mapPropertyStatus();

  RadioProxy - Arduino libary for mapping 433Mhz devices and Mozilla
  WebThings. It uses RCbuttonPtoperty for communication through the
  oddWires IoT-Bus 433Mhz board based on the Hope RFM69 module.
  Copyright (c) 2018 ian Archbell, oddWires.  All right reserved.

  Original RCbuttonPtoperty project home: https://github.com/sui77/rc-buttonPtoperty/
  Also see copyright and license notices in RCbuttonPtoperty sources.

  Project home for iot-bus: https://github.com/iot-bus/rc-buttonPtoperty/

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

/*
* This example does not use the original controllers but uses a red button to control outlet 1
* and a key ring power button to control a light
*
* Note that the initial status of the device must be OFF as the example uses a WHILE rule
* which works fine if the device is off initially but the device will never turnoff if it is 
* initially on. The problem can be avoided by using two IF rules so that there is never 
* an indeterminate state
*/

#include <Arduino.h>
#include <Thing.h>
#include <WebThingAdapter.h>
#include "RadioProxy.h"

//TODO: Hardcode your WiFi credentials here (and keep it private)
const char* ssid = "NETGEAR96";
const char* password = "phoebe1984";

WebThingAdapter* adapter;

// round red button
const char* sensorTypes[] = {"binarySensor", nullptr};
ThingDevice redButton("Moz It Button Red", "IoT-Bus 433Mhz Moz It Red button", sensorTypes);
ThingProperty buttonProperty1("Button", "433Mhz Red Button 1", BOOLEAN, "BooleanProperty");

// keyring with single button
const char* sensorTypes2[] = {"binarySensor", nullptr};
ThingDevice keyButton("Moz It Button Keyring", "IoT-Bus 433Mhz Moz It Power Button", sensorTypes2);
ThingProperty buttonProperty2("Power", "433Mhz Power", BOOLEAN, "BooleanProperty");

// keyring with two buttons
const char* sensorTypes3[] = {"binarySensor", nullptr};
ThingDevice keyButton2("Moz It Two Buttons", "IoT-Bus 433Mhz Moz It Two Buttons", sensorTypes3);
ThingProperty buttonProperty3("Button A", "433Mhz Key Button A", BOOLEAN, "BooleanProperty");
ThingProperty buttonProperty4("Button B", "433Mhz Key Button B", BOOLEAN, "BooleanProperty");

// Protocols are automatically decoded provided they are supported by RCSwitch
// Look in Protocols.h for the protocol table
// If you run this example you will see any supported device code printed in the serial monitor 
// together with its characteristics
// PROXY_INPUT radio reception, property reference, on code, off code (only onCode if flipflop switch)
RadioProxy proxy1(PROXY_INPUT, &buttonProperty1, 15864961);
RadioProxy proxy2(PROXY_INPUT, &buttonProperty2, 12412833);
RadioProxy proxy3(PROXY_INPUT, &buttonProperty3, 10063521);
RadioProxy proxy4(PROXY_INPUT, &buttonProperty4, 10063522);

ThingDevice Light3("Light 3", "IoT-Bus 433Mhz Light 3", sensorTypes);
ThingProperty light3("light", "433Mhz Light 3", BOOLEAN, "BooleanProperty");
ThingDevice Outlet1("Outlet 1", "IoT-Bus 433Mhz Outlet 1", sensorTypes);
ThingProperty outlet1("Power", "433Mhz Outlet 3", BOOLEAN, "BooleanProperty");

// Proxy for a light(3 on controller) and one of the outlets and an outlet (1 on controller)
// PROXY_OUTPUT radio transmission, property reference, on code, off code, bit length, pulse length, protocol, repetitions
// Most devices are protocol 1, pulse length varies a lot, bit length is usually 24, reppetitions 10 is usually OK
RadioProxy proxylight(PROXY_OUTPUT, &light3, 1136387, 1136396, 24, 183, 1, 10);
RadioProxy proxyOutlet(PROXY_OUTPUT, &outlet1, 5264691, 5264700, 24, 183, 1, 10);

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
  
  // Initialize MOZ IoT buttons
  redButton.addProperty(&buttonProperty1);
  adapter->addDevice(&redButton);
  
  keyButton.addProperty(&buttonProperty2);
  adapter->addDevice(&keyButton);
  
  keyButton2.addProperty(&buttonProperty3);
  keyButton2.addProperty(&buttonProperty4);
  adapter->addDevice(&keyButton2);

  // Initialize MOZ IoT Light and outlet

  Light3.addProperty(&light3);
  adapter->addDevice(&Light3);
  Outlet1.addProperty(&outlet1);
  adapter->addDevice(&Outlet1);
 
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





