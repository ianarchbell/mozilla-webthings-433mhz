/*
  This example shows how to use a 433Mhz controller and devices through Mozilla Webthings.
  You need to use the advanced-receive example to find out the codes from your controller.
  Then you simply define the Mozilla WebThings as usual then add a proxy for each switch 
  or device using the RadioProxy class. Then enable the radio. The 433Mhz input and mapping of 
  Mozilla WebThing properties to device state is performed in the loop as shown below. 
  That's all that's required.
  
  // map all properties to radio status 
  // map a received code to relevant property
  RadioProxy::update();
  
  RadioProxy - Arduino libary for mapping 433Mhz devices and Mozilla
  WebThings. It uses RCSwitch for communication through the
  oddWires IoT-Bus 433Mhz board based on the Hope RFM69 module.
  Copyright (c) 2018 ian Archbell, oddWires.  All right reserved.
  Original RCSwitch project home: https://github.com/sui77/rc-switch/
  Also see copyright and license notices in RCSwitch sources.
  Project home for iot-bus version: https://github.com/iot-bus/rc-switch/
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
const char* ssid = "........";
const char* password = ".......";

//WebThingAdapter* adapter;
WebThingAdapter adapter("adapter", WiFi.localIP());

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

// Proxies for the button properties above
// Protocols are automatically decoded provided they are supported by RCSwitch
// Look in Protocols.h for the protocol table
// If you run this example you will see any supported device code printed in the serial monitor 
// together with its characteristics
// PROXY_INPUT radio reception, property reference, on code, off code (only onCode if flipflop switch)
RadioProxy proxy1(PROXY_INPUT, &buttonProperty1, 15864961);
RadioProxy proxy2(PROXY_INPUT, &buttonProperty2, 12412833);
RadioProxy proxy3(PROXY_INPUT, &buttonProperty3, 10063521);
RadioProxy proxy4(PROXY_INPUT, &buttonProperty4, 10063522);

// Light controller WebThing
ThingDevice lightController("LightController", "IoT-Bus 433Mhz Light Controller", sensorTypes);
ThingProperty control1("Control 1", "433Mhz Light Control 1", BOOLEAN, "BooleanProperty");
ThingProperty control2("Control 2", "433Mhz Light Control 2", BOOLEAN, "BooleanProperty");
ThingProperty control3("Control 3", "433Mhz Light Control 3", BOOLEAN, "BooleanProperty");
ThingProperty control4("Control 4", "433Mhz Light Control 4", BOOLEAN, "BooleanProperty");

// Proxies for the controller 3 on and off buttons
// Protocols are automatically decoded provided they are supported by RCSwitch
// Look in Protocols.h for the protocol table
// If you run this example you will see any supported device code printed in the serial monitor 
// together with its characteristics
// PROXY_INPUT radio reception, property reference, on code, off code
RadioProxy proxy5(PROXY_INPUT, &control1, 1135923, 1135932);
RadioProxy proxy6(PROXY_INPUT, &control2, 1136067, 1136076);
RadioProxy proxy7(PROXY_INPUT, &control3, 1136387, 1136396);
RadioProxy proxy8(PROXY_INPUT, &control4, 1137923, 1137932);

// Light WebThings
ThingDevice Light1("Light 1", "IoT-Bus 433Mhz Light 1", sensorTypes);
ThingProperty light1("light", "433Mhz Light 1", BOOLEAN, "BooleanProperty");
ThingDevice Light2("Light 2", "IoT-Bus 433Mhz Light 2", sensorTypes);
ThingProperty light2("light", "433Mhz Light 2", BOOLEAN, "BooleanProperty");
ThingDevice Light3("Light 3", "IoT-Bus 433Mhz Light 3", sensorTypes);
ThingProperty light3("light", "433Mhz Light 3", BOOLEAN, "BooleanProperty");
ThingDevice Light4("Light 4", "IoT-Bus 433Mhz Light 4", sensorTypes);
ThingProperty light4("light", "433Mhz Light 3", BOOLEAN, "BooleanProperty");

// Proxies for the four lights
// PROXY_OUTPUT radio transmission, property reference, on code, off code, bit length, pulse length, protocol, repetitions
// Most devices are protocol 1, pulse length varies a lot, bit length is usually 24, reppetitions 10 is usually OK
RadioProxy proxy9(PROXY_OUTPUT, &light1, 1135923, 1135932, 24, 168, 1, 10);
RadioProxy proxy10(PROXY_OUTPUT, &light2, 1136067, 1136076, 24, 168, 1, 10);
RadioProxy proxy11(PROXY_OUTPUT, &light3, 1136387, 1136396, 24, 168, 1, 10);
RadioProxy proxy12(PROXY_OUTPUT, &light4, 1137923, 1137932, 24, 168, 1, 10);

// Outlet controller WebThing
ThingDevice outletController("OutletController", "IoT-Bus 433Mhz Outlet Controller", sensorTypes);
ThingProperty switch1("Control 1", "433Mhz Outlet Control 1", BOOLEAN, "BooleanProperty");
ThingProperty switch2("Control 2", "433Mhz Outlet Control 2", BOOLEAN, "BooleanProperty");
ThingProperty switch3("Control 3", "433Mhz Outlet Control 3", BOOLEAN, "BooleanProperty");

// Proxies for the controller 3 on and off buttons
// Protocols are automatically decoded provided they are supported by RCSwitch
// Look in Protocols.h for the protocol table
// If you run this example you will see any supported device code printed in the serial monitor 
// together with its characteristics
// PROXY_INPUT radio reception, property reference, on code, off code
RadioProxy proxy13(PROXY_INPUT, &switch1, 5264691, 5264700);
RadioProxy proxy14(PROXY_INPUT, &switch2, 5264835, 5264844);
RadioProxy proxy15(PROXY_INPUT, &switch3, 5265155, 5265164);

ThingDevice outlet1("Outlet 1", "IoT-Bus 433Mhz Outlet 1", sensorTypes);
ThingProperty power1("Power", "433Mhz Outlet 1", BOOLEAN, "BooleanProperty");
ThingDevice outlet2("Outlet 2", "IoT-Bus 433Mhz Outlet 2", sensorTypes);
ThingProperty power2("Power", "433Mhz Outlet 2", BOOLEAN, "BooleanProperty");
ThingDevice outlet3("Outlet 3", "IoT-Bus 433Mhz Outlet 3", sensorTypes);
ThingProperty power3("Power", "433Mhz Outlet 3", BOOLEAN, "BooleanProperty");

// Proxies for the three outlets
// PROXY_OUTPUT radio transmission, property reference, on code, off code, bit length, pulse length, protocol, repetitions
// Most devices are protocol 1, pulse length varies a lot, bit length is usually 24, reppetitions 10 is usually OK
RadioProxy proxy16(PROXY_OUTPUT, &power1, 5264691, 5264700, 24, 184, 1, 10);
RadioProxy proxy17(PROXY_OUTPUT, &power2, 5264835, 5264844, 24, 184, 1, 10);
RadioProxy proxy18(PROXY_OUTPUT, &power3, 5265155, 5265164, 24, 184, 1, 10);

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
  //adapter = new WebThingAdapter("adapter", WiFi.localIP());

  // Initialize MOZ IoT buttons
  redButton.addProperty(&buttonProperty1);
  adapter.addDevice(&redButton);
  
  keyButton.addProperty(&buttonProperty2);
  adapter.addDevice(&keyButton);
  
  keyButton2.addProperty(&buttonProperty3);
  keyButton2.addProperty(&buttonProperty4);
  adapter.addDevice(&keyButton2);
  
  // Initialize MOZ IoT controller
  lightController.addProperty(&control1);
  lightController.addProperty(&control2);
  lightController.addProperty(&control3);
  lightController.addProperty(&control4);
  adapter.addDevice(&lightController);

  // Initialize MOZ IoT Lights
  Light1.addProperty(&light1);
  adapter.addDevice(&Light1);
  Light2.addProperty(&light2);
  adapter.addDevice(&Light2);
  Light3.addProperty(&light3);
  adapter.addDevice(&Light3);
  Light4.addProperty(&light4);
  adapter.addDevice(&Light4);

  // Initialize MOZ IoT controller
  outletController.addProperty(&switch1);
  outletController.addProperty(&switch2);
  outletController.addProperty(&switch3);
  adapter.addDevice(&outletController);

  // Initialize MOZ IoT outlets
  outlet1.addProperty(&power1);
  adapter.addDevice(&outlet1);
  outlet2.addProperty(&power2);
  adapter.addDevice(&outlet2);
  outlet3.addProperty(&power3);
  adapter.addDevice(&outlet3);
 
  // start the radio
  RadioProxy::begin(true); // verbose
  // start the adapter
  adapter.begin();   
}

void loop() {
  // map a received code to relevant property
  // map all properties to radio status 
  RadioProxy::update();
}
