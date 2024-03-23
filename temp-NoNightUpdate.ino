#include <PietteTech_DHT.h>
#define DHTTYPE DHT22
#define DHTPIN D4

PietteTech_DHT DHT(DHTPIN, DHTTYPE);

double warehouseTempMax = 91;
double warehouseHumidityMax = 65;
double warehouseTemp;
double warehouseHumidity;
double maxAllowedTemp = 95.0; // Change this value as needed
bool tooHumid = false;
double maxTemperature = -1000.0; // Initialize with a very low value

const int tempArraySize = 16; // Store 4 hours worth of temperature data (4 hours * 4 readings/hour)
double tempArray[tempArraySize];
int tempArrayIndex = 0;

void setup()
{
    Serial.begin(9600);
    Particle.variable("WarehouseTemp", &warehouseTemp, DOUBLE);
    Particle.variable("WarehouseHumidity", &warehouseHumidity, DOUBLE);
}

void loop()
{
    int result = DHT.acquireAndWait(2000);

    warehouseTemp = DHT.getFahrenheit();
    warehouseHumidity = DHT.getHumidity();

    // Update the maximum temperature
    if (warehouseTemp > maxTemperature) {
        maxTemperature = warehouseTemp;
    }

    // Store temperature value in the array
    tempArray[tempArrayIndex] = warehouseTemp;
    tempArrayIndex = (tempArrayIndex + 1) % tempArraySize;

    // Get the current hour (assumes Particle device can access the time)
    Time.zone(-4); // Set the time zone as needed (-4 for EDT, for example)
    int currentHour = Time.hour();

    static unsigned long lastPublishTime = 0;
    unsigned long currentTime = millis();
    unsigned long publishInterval = 600000; // Default to 10 minutes

    // Change publish interval to 1 hour if between 9 PM and 7 AM
    if (currentHour >= 21 || currentHour < 7) {
        publishInterval = 3600000; // 1 hour in milliseconds
    }

    // Publish temperature, humidity, and maximum temperature values based on the time interval or if overheat
    if (currentTime - lastPublishTime >= publishInterval || warehouseTemp >= maxAllowedTemp) {
        String tempStr = String::format("%.2f", warehouseTemp);
        String humidityStr = String::format("%.2f", warehouseHumidity);
        String maxTempStr = String::format("%.2f", maxTemperature);
        Particle.publish("warehouse_data", "Temperature: " + tempStr + "°F, Humidity: " + humidityStr + "%, Maximum Temperature: " + maxTempStr + "°F", PRIVATE);
        lastPublishTime = currentTime;
    }

    if (warehouseTemp >= maxAllowedTemp) {
        Particle.publish("warehouse_temp", "overheat");
    }

    if (warehouseHumidity >= warehouseHumidityMax && !tooHumid) {
        Particle.publish("warehouse_humidity", "tooHumid");
        tooHumid = true;
    }
    else if (warehouseHumidity < warehouseHumidityMax && tooHumid) {
        Particle.publish("warehouse_humidity", "normal");
        tooHumid = false;
    }

    // Publish the maximum temperature value every 4 hours
    static unsigned long lastTempPublishTime = 0;
    if (currentTime - lastTempPublishTime >= 14400000) { // 14400000 milliseconds = 4 hours
        double maxTemp = -1000;
        for (int i = 0; i < tempArraySize; i++) {
            if (tempArray[i] > maxTemp) {
                maxTemp = tempArray[i];
            }
        }
        String maxTempStr = String::format("%.2f", maxTemp);
        Particle.publish("warehouse_max_temp", "Maximum Temperature: " + maxTempStr + "°F", PRIVATE);
        lastTempPublishTime = currentTime;
    }

    delay(60000); // 60000 milliseconds = 1 minute
}
