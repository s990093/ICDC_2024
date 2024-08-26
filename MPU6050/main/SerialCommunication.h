#include <HardwareSerial.h>

class SerialCommunication
{
public:
    // Constructor
    SerialCommunication(HardwareSerial &serialPort, unsigned long baudRate)
        : serial(serialPort), baud(baudRate) {}

    // Initialize the serial port
    void begin()
    {
        serial.begin(baud);
    }

    // Send data
    void send(const String &data)
    {
        serial.println(data);
    }

    // Read available data
    String receive()
    {
        String receivedData = "";
        while (serial.available())
        {
            char ch = serial.read();
            receivedData += ch;
        }
        return receivedData;
    }

private:
    HardwareSerial &serial; // Reference to the serial port
    unsigned long baud;     // Baud rate
};

// Example usage
// #define RX_PIN 16 // Replace with your RX pin number
// #define TX_PIN 17 // Replace with your TX pin number
// #define BAUD_RATE 9600

// HardwareSerial MySerial(1); // Use Serial1 on ESP32 (could be Serial2 as well)

// SerialCommunication serialComm(MySerial, BAUD_RATE);

// void setup()
// {
//     Serial.begin(115200); // Serial monitor for debugging
//     serialComm.begin();   // Initialize the serial communication with R3
// }

// void loop()
// {
//     // Check if data is available
//     String data = serialComm.receive();
//     if (data.length() > 0)
//     {
//         Serial.println("Received data: " + data);
//         // Process received data here
//     }

//     // Example of sending data
//     serialComm.send("Hello R3!");

//     delay(1000); // Delay to avoid flooding
// }
