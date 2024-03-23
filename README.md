# Warehouse Temperature and Humidity Monitor
TLDR; Using a Particle Boron LTE-M to log temp and alert if to Hot or to Humid

This repository contains code and resources for setting up a real-time temperature and humidity monitoring system in a warehouse environment using Particle IoT devices. The project is designed to alert users to changes in environmental conditions that could affect stored goods or equipment.

## Project Components

The project consists of two main components:

1. **Particle Device Firmware**: Particle firmware is meant for Particle devices like the Boron, Photon or Electron. It reads temperature and humidity data from a DHT22 sensor and publishes this data to the Particle Cloud.

2. **Web Interface**: A simple HTML/CSS/JavaScript web application that allows users to view current environmental conditions and past events through their web browser. It also provides a login functionality for secure access.

## Getting Started

### Prerequisites

- Particle Photon or Electron device
- DHT22 temperature and humidity sensor
- Basic understanding of electronics and web technologies (HTML, JavaScript)

### Hardware Setup

1. Connect the DHT22 sensor to your Particle device. Connect the data pin to D4 (or the pin defined in your code), power to 3V3, and ground to GND.
2. Ensure your Particle device is connected to the internet and registered in your Particle account.

### Software Setup

#### Particle Device

1. Open the Particle IDE and create a new application.
2. Copy the content of the `temp-test.ino` from this repository into your application.
3. Flash the application to your Particle device.

#### Web Interface

1. Host the HTML files from the `Web_Interface` directory on your preferred web server, or open them directly in your browser for testing purposes.
2. Edit the file to include your Particle device's access token and device ID.

## Usage

1. Log in to the web interface using your Particle account credentials.
2. View real-time temperature and humidity data on the dashboard.
3. Receive alerts if temperature or humidity exceed set thresholds.
4. Review past environmental events in the "Past Events" section.

## Contributing

Contributions to this project are welcome. Please fork the repository and submit a pull request with your changes.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

- Thanks to PietteTech for the DHT sensor library.
- Thanks to Particle for providing the IoT platform and documentation.
