# Bluetooth-Accessibility-Switch-Interface

Overview:
Mobile smart devices are a necessity to the modern world. Ever since the first release of the iPhone back in 2007, these devices have slowly evolved and become a medium for socializing, enhancing productivity for work, expressing creativity, as well as consuming large quantities of entertainment such as movies, music, games. Almost everyone has one type of smart device, if not more, and can easily identify and say that these devices are an essential part of their lives - no one wants to go back to the dark ages. Except there is one demographic that's left in limbo.
The out-of-the-box experience on these devices have a primary focus on individuals who have dexterity and fine motor control. Anyone not as such is stuck unable to fully embrace and utilize the potential of this technology, which unfortunately is anyone with a severe physical disability like quadriplegia.

It took five years before the first human interface device was created for people with disabilities to have some basic control of a smart device. This device was called Tecla. Tecla became a major influencer to bring attention to the mobile smart device market and say that people with disabilities want unparalleled access to these devices just like everyone else. Tecla took advantage of already existing accessibility protocols and bent the rules, essentially creating a whole new access method known as switch scanning. Switch scanning is not a new concept. For over a decade other assistive technology companies have written proprietary software for individuals that use switch scanning. However fast forward several years and as a result, the leading giants (Apple and Google) have begun implementing switch scanning and alternative input configurations and access directly into the Mobile operating systems on their respective devices.


Objective:	
Although this is nothing new, my goal is to demonstrate how easy it can be to create your own switch interface to access any kind of smart device that uses Bluetooth Radio waves. With a little bit of technical know-how, programming skills, and sense of adventure, anyone can make their own cost-effective switch interface. I am presenting and giving all this information as open-source for anyone to use for their liking to create and adapt on their own. Alternatively, if anyone would rather not go through the hassle of tinkering and troubleshooting, I am more than willing to have the device assembled for a minimal cost of parts and labour. Regardless of doing this yourself, or paying me, I promise your total cost will be much less than paying for Tecla or any other commercially available accessibility Interface.


Parts List:	
As of version 1, the following is bare minimum needed to get this interface up and running with you're smart device.
- 1x Adafruit Feather 32u4 BLE Microcontroller.
- 1x Light Emitting Diode (LED) color of your choice.
- 1x Breadboard or Prototype Board.
- 1x Resistor.
- 1x 2 way push button switch / or 3.5 mm Mono or Stereo female jack for use with compliant accessibility switch.

Building:
It is possible to complete this project without any prior soldering knowledge. All components can be clipped onto a breadboard and function as they should. Keeping in mind, breadboards are not permanent solutions. If you intend to use this Interface on the go under rugged conditions, it is recommended to properly solder all the components onto a prototype board. To learn more about soldering there are some great tutorials on YouTube.

I am only going to explain the wiring order. It is up to you as the creator to determine the best practical layout for your components. Feel free to mimic my layout if you desire, but be advised that there are better and more efficient wiring for connecting everything together.
--- Step 1
- The Arduino Feather 32u4 is a unique microcontroller because it comes with a built in Bluetooth radio transmitter. Using this type of microcontroller eliminates the need for sourcing and learning how to use a separate Bluetooth module.
- Attached the Arduino to the board, and bridge the 3V pin from the Arduino to the positive rail on the board which is indicated as red. From there, do the same thing and bridge the ground pin from the Arduino to the negative rail marked as blue on the board. For clarity I colour-coded my wires as red for positive and black for negative.
--- Step 2
- Connect pin 13 from the Arduino to the positive side of the LED (positive side is usually curved).
- Connect the negative side of the LED (flat side) to the ground rail, using a resistor in line between the two points. The resistor restricts the flow of current coming from the LED and stops it from blowing out. Without it your LED will pop and not work.
--- Step 3
- For initial prototyping you can use a standard two-way pushbutton switch to act as your input method. However, attaching a 3.5mm jack enables the option of using an accessibility switch or connecting the interface directly to an environmental control unit (ECU) on a power wheelchair.
- The two-way pushbutton switch is a bit different on how it's wired, but fundamentally done in a similar way as the LED.
- Push button switches follow a diagonal wiring pattern. Anything from top left flows to bottom right, and top right flows to bottom left. Pin 12 from the Arduino is connected to the top left of the pushbutton switch, followed by the bottom right bridging to the 3V positive rail.
- The negative side is connected on the bottom left and bridged to the negative rail using a resistor. In this case the resistor pushes back on the switch (called a pull-up resistor) and physically resets the button to a neutral released state.


Firmware:	The code used for this interface was custom written from scratch. Essentially it monitors the pressed state of the switch and calculates the time variance to give three distinct activation gestures - short press, long press, and longest press. All the details on how it works are commented within the source files.

Download the sketch and all the accompanying source files to go with it. Open inside of the Arduino software or using the specific Visual Studio project files. Compile and flash the code to the microcontroller.
