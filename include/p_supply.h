#define S_SDA 32
#define S_SCL 33
#include <INA219_WE.h>
#include <Wire.h>
#define INA219_ADDRESS 0x42
INA219_WE ina219 = INA219_WE(INA219_ADDRESS);

float shuntVoltage_mV = 0.0;
float loadVoltage_V = 0.0;
float busVoltage_V = 0.0;    //Define the serial bus voltage 
float current_mA = 0.0;    //Define current
float power_mW = 0.0;      //Define power 
bool ina219_overflow = false;

float percentage = 0;

void InitINA219(){
  if(!ina219.init()){
    //Initialize INA219 module
    Serial.println("INA219 not connected!");
  }
  ina219.setADCMode(BIT_MODE_9);
  ina219.setPGain(PG_320);
  ina219.setBusRange(BRNG_16);
  ina219.setShuntSizeInOhms(0.01); // used in INA219.
}

void InaDataUpdate(){
  shuntVoltage_mV = ina219.getShuntVoltage_mV();
  busVoltage_V = ina219.getBusVoltage_V();    //Get serial bus voltage  
  current_mA = ina219.getCurrent_mA();    //Get current
  power_mW = ina219.getBusPower();    //Get power
  loadVoltage_V  = busVoltage_V + (shuntVoltage_mV/1000);
  ina219_overflow = ina219.getOverflow();
//   percentage = ((loadVoltage_V - 9.0) / 3.6) * 100
}



const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>Battery Monitor</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <style>
      body {
        font-family: Arial;
        text-align: center;
        padding-top: 50px;
      }
      .box {
        border: 1px solid #333;
        padding: 20px;
        margin: 10px auto;
        width: 200px;
      }
    </style>
  </head>
  <body>
    <h1>Ro-Arm Battery Monitor</h1>
    <div class="box">Voltage: <span id="temp1">%TEMP1%</span> V</div>
    <div class="box">Current: <span id="temp2">%TEMP2%</span> mAmps</div>

    <script>
      setInterval(function () {
        fetch("/temps")
          .then((response) => response.json())
          .then((data) => {
            document.getElementById("temp1").innerHTML = data.temp1;
            document.getElementById("temp2").innerHTML = data.temp2;
          });
      }, 1000);
    </script>
  </body>
</html>
)rawliteral"; 