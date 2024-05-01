This document provides answers to the questions regarding the replacement of RFID with Bluetooth technology.
***

### Question 1: How can Bluetooth be substituted for RFID in the embedded section of the exercise? Please describe our solution.

#### Answer:


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
