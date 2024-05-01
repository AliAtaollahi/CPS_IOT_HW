This document provides answers to the questions regarding the replacement of RFID with Bluetooth technology.
***

### Question 1: How can Bluetooth be substituted for RFID in the embedded section of the exercise? Please describe our solution.

#### Answer:
To substitute Bluetooth for RFID in our IoT-based entry and exit management system, the solution involves using Bluetooth Low Energy (BLE) modules instead of RFID sensors and tags. Here's how we can implement this:

1. **Replace Hardware**: Swap the RFID sensor and tags with a Bluetooth module such as the HC-05 or HM-10 BLE module on both the Arduino board and the tags/carriers (which could now be smartphones or BLE tags).

2. **Modify Arduino Setup**:
   - Attach the Bluetooth module to the Arduino via serial communication (using RX and TX pins).
   - Implement a BLE beacon scanning routine in the Arduino code that continuously scans for BLE devices nearby.

3. **Software Modifications**:
   - In the Arduino sketch, replace RFID reading logic with code to handle Bluetooth device discovery and data extraction. This involves programming the Bluetooth module to detect BLE beacons (or other BLE devices) and extract their identifiers.
   - Instead of reading RFID data, the Arduino will now read the Bluetooth device's unique address or any predefined service data from BLE advertisements.

4. **Authentication Changes**:
   - Modify the authentication logic on the server to accept and verify Bluetooth addresses or custom service data instead of RFID tags.
   - Maintain a database of authorized Bluetooth addresses or service data on the cloud server for access control.

5. **Security Considerations**:
   - Ensure that the Bluetooth communication is secured using encryption and randomized addresses if necessary to avoid tracking and spoofing vulnerabilities inherent in Bluetooth devices.

This solution leverages Bluetooth's ability to identify devices over short distances without physical contact, offering a modern and potentially more versatile alternative to RFID, with the added benefit of using smartphones as identification devices.

---
### Question 2: Is it possible to exchange necessary information (such as individual identifiers) between Bluetooth modules without needing to pair them? Explain.

#### Answer:


---
### Question 3: Assuming the use of Bluetooth, what alternative would you suggest to replace the use of a timer for closing a company's entrance? Explain.

#### Answer:
An alternative to using a timer for closing a company’s entrance when using Bluetooth could be the implementation of a proximity-based system using Bluetooth signal strength (RSSI - Received Signal Strength Indicator). Here’s how this could work:

1. **Proximity Detection**:
   - Utilize the RSSI value of the Bluetooth signal to determine the distance of the Bluetooth device (such as a smartphone or badge) from the door.
   - Configure the door to close automatically when the Bluetooth device's signal indicates it has moved beyond a certain distance from the door sensor.

2. **Implementation Details**:
   - The Bluetooth scanner at the door measures the RSSI of the recognized device periodically.
   - A threshold RSSI value is set based on empirical data to estimate the distance at which the door should close.

3. **Advantages**:
   - **Dynamic Response**: The door responds dynamically to the actual position of the individual rather than closing after a fixed time period, enhancing both security and user convenience.
   - **Energy Efficiency**: The door remains open only as long as necessary, reducing energy consumption associated with repeatedly opening and closing.

4. **Safety Considerations**:
   - Implement additional checks to ensure the door does not close if someone is in or very close to the door, using infrared sensors or pressure mats.

This proximity-based approach uses Bluetooth’s capabilities for live distance estimation, offering a more responsive and context-aware mechanism compared to a fixed timer, potentially improving both the security and efficiency of the entry and exit management system.
