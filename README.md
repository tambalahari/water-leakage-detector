 IoT-Based Water Pipeline Leakage Detector for Localized Installations

📌 Project Overview

Water leakage in household pipelines, laboratories, and small industrial installations can lead to significant water wastage if it is not detected early.

The IoT-Based Water Pipeline Leakage Detector is an ESP32-based system that monitors water flow at different points in a pipeline and identifies possible leakage by comparing the flow readings. It uses the Blynk IoT platform to display sensor readings and send alerts when a potential leak is detected.

 🎯 Objectives

- Monitor water flow at multiple points in a pipeline.
- Divide the pipeline into two segments for localized leakage detection.
- Compare inlet and outlet flow readings to identify abnormal flow differences.
- Send real-time sensor readings to the Blynk IoT dashboard.
- Generate event-based alerts when a possible leakage condition persists.

 🛠️ Components Required

| Component | Quantity |
|---|---:|
| ESP32 development board | 1 |
| Water flow sensors | 4 |
| Connecting wires | As required |
| Water pipes and connectors | As required |
| Wi-Fi connection | 1 |
| Blynk IoT account | 1 |

 ⚙️ System Architecture

The pipeline is divided into two monitoring segments:

- **Segment 1:** Sensor S1 (inlet) and Sensor S2 (outlet)
- **Segment 2:** Sensor S3 (inlet) and Sensor S4 (outlet)

The ESP32 reads pulses from the four flow sensors, calculates flow values, compares readings within each segment, and sends the data to the Blynk platform.


Water Pipeline
      |
      v
+-------------------------+
|  Segment 1: S1 and S2   |
|  Inlet/Outlet Monitoring|
+-------------------------+
      |
      v
+-------------------------+
|  Segment 2: S3 and S4   |
|  Inlet/Outlet Monitoring|
+-------------------------+
      |
      v
+-------------------------+
|       ESP32             |
| Flow Calculation        |
| Leakage Detection Logic |
+-------------------------+
      |
      v
+-------------------------+
|      Blynk IoT Cloud    |
| Sensor Readings & Alerts|
+-------------------------+


 🔍 Working Principle

1. Flow Measurement: Each flow sensor generates pulses as water passes through it. The ESP32 counts these pulses using hardware interrupts.

2. Flow Calculation: The pulse counts are converted into flow values using a conversion factor defined in the program.

3. Segment Monitoring: The ESP32 compares the inlet and outlet readings of each pipeline segment to calculate the flow difference.

4. Leak Detection: A possible leak is identified when the inlet flow exceeds the outlet flow by more than the configured absolute and percentage thresholds.

5. Time Validation: The abnormal condition must persist across multiple measurement cycles before a leak alert is generated.

6. IoT Notifications: Sensor readings are sent to Blynk, and event notifications are triggered for the affected segment.

🧠 Leakage Detection Logic

The program uses the following configurable parameters:

| Parameter | Value | Purpose |
|---|---:|---|
| `MIN_FLOW` | 0.3 | Minimum flow threshold used to identify idle conditions |
| `ABS_THRESHOLD` | 1.0 | Minimum absolute flow difference |
| `PERCENT` | 0.2 (20%) | Relative difference threshold |
| Validation counter | Greater than 5 | Confirms a persistent abnormal condition |

 Segment 1

The inlet reading from S1 is compared with the outlet reading from S2.

A possible leak is flagged when:

- The difference `S1 - S2` exceeds the absolute threshold.
- The difference also exceeds 20% of the inlet reading.
- The condition persists for more than five measurement cycles.

 Segment 2

The same logic is applied to S3 and S4.

The system generates separate alerts for Segment 1 and Segment 2.

Note: The current implementation uses flow differences as an indicator of possible leakage. Unequal flow can also occur due to normal water usage, sensor variation, or changing hydraulic conditions. Practical validation is required before treating an alert as a confirmed leak.

 📱 Blynk IoT Integration

The Blynk dashboard is used to monitor the system remotely.

| Virtual Pin / Event | Purpose |
|---|---|
| V0 | Flow reading from S1 |
| V1 | Flow reading from S2 |
| V2 | Flow reading from S3 |
| V3 | Flow reading from S4 |
| `leak_seg1` | Segment 1 leakage event |
| `leak_seg2` | Segment 2 leakage event |

Configure the corresponding datastreams and event definitions in your Blynk template before running the system.

 💻 Technologies Used

- Embedded Programming: Arduino C/C++
- Microcontroller: ESP32
- IoT Platform: Blynk IoT
- Communication: Wi-Fi
- Sensors: Water flow sensors
- Development Environment: Arduino IDE

 🚀 Setup and Installation

1. Install the Arduino IDE.
2. Install the ESP32 board package using the Arduino IDE Boards Manager.
3. Install the **Blynk library** from the Arduino Library Manager.
4. Connect the four flow sensors to the ESP32 pins configured in the code:
   - S1 → GPIO 34
   - S2 → GPIO 35
   - S3 → GPIO 32
   - S4 → GPIO 33
5. Create a Blynk template and configure the required datastreams and event codes.
6. Update the Blynk template ID, authentication token, Wi-Fi SSID, and password in the code.
7. Select the appropriate ESP32 board and COM port.
8. Upload the program and open the Serial Monitor at **115200 baud**.
9. Check the sensor readings and test both pipeline segments under normal and simulated leakage conditions.

 🔐 Security

- Do not publish Wi-Fi passwords or Blynk authentication tokens in a public repository.
- Store credentials securely and replace any credentials that may have been exposed.
- Use placeholders or a separate private configuration file for sensitive information.

 ⚠️ Limitations

- The flow conversion factor must be calibrated for the specific sensors and installation.
- The current detection method assumes that inlet and outlet readings can be meaningfully compared.
- Normal water usage and changing flow conditions may cause false alerts.
- The current code sends an alert when the validation counter exceeds five; it does not implement a separate alert cooldown or automatic valve shutoff.
- The system requires a working power supply and Wi-Fi connection for cloud monitoring.

 🔮 Future Enhancements

- Calibrate flow readings using measured water volumes.
- Improve detection reliability using adaptive thresholds and longer-term flow analysis.
- Add alert cooldowns and recovery notifications.
- Introduce battery backup for power interruptions.
- Integrate an automatic valve mechanism to isolate a detected leak.
- Expand monitoring to additional pipeline segments.

 🌍 Sustainable Development Goals

- SDG 6 – Clean Water and Sanitation:** Supports water conservation by identifying possible pipeline leakage.
- SDG 12 – Responsible Consumption and Production:** Encourages efficient water usage and reduced wastage.

 👩‍💻 Project Status

Prototype under development and testing. Leakage detection performance depends on sensor calibration, pipeline conditions, and practical validation.

---

Project: IoT-Based Water Pipeline Leakage Detector for Localized Installations

Platform: ESP32 + Arduino IDE + Blynk IoT
