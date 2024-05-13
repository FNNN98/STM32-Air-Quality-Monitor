# STM32-Air-Quality-Monitor


  <img src="https://github.com/FNNN98/STM32-Air-Quality-Monitor/blob/main/air-quality-pinout-configuration.png?raw=true" width="800">

# Introduction
As concerns about air pollution continue to rise globally, it's crucial to have access to accurate and real-time data about the air we breathe, whether indoors or outdoors. This project aims to address this need by creating a portable USB-C powered air quality monitoring solution.

The primary goal of this project is to develop a compact indoor/outdoor air quality monitor capable of measuring key pollutants such as PM2.5, PM5, PM10, environmental CO2, TVOC, and providing an Air Quality Index (AQI) reading.

Living in Milan, air quality has and will always be a topic of concern, especially given our location in the heart of the Po Valley (Pianura Padana). The Po Valley is notorious for its heavy industrial activity and dense urbanization, factors that contribute significantly to air pollution levels. In Milan particularly, surrounded by bustling streets and industrial zones, the need for vigilant air quality monitoring is ever-present. 

Since the likelihood of [flattening the Turchino](https://www.youtube.com/watch?v=vmvpm51TdJM) is about as feasible as achieving pristine air in Milan, let's focus on what we can control: creating tools to monitor air pollution and address the health risks it poses.
To my Ligurian friends, I hope you'll pardon my playful jab.

# Hardware Used

- <h3 align="left"> WeActStudio STM32F411CEU6 </h3>

  The STM32F411CEU6 BlackPill is a powerful microcontroller featuring a 100MHz clock speed, 512Kb Flash memory, and 128Kb SRAM. 
  
- <h3 align="left"> Adafruit PMSA003I </h3>
  
  The Adafruit PMSA003I Air Quality Breakout is a sensor that monitors air quality. It measures PM1.0, PM2.5, and PM10.0 concentrations, as well as particulate matter in different size bins.
  It connects via I2C (there are also 2x StemmaQT sockets),  It effectively measures particle concentrations within the PM2.5 standard range of 0~500μg/m³, with a maximum range exceeding 1000μg/m³.
  The module offers high resolution (1μg/m³) and low consistency error (±10%) across different particle concentrations.
  It operates on a 5.0V DC power supply, with an active current draw of ≤100 mA and standby current of ≤200 μA.
  The board can handle both 3.3v and 5v inputs due to its mini boost circuit. The 3.3v pin on the breakout board can also power external devices.
  
- <h3 align="left"> Fermion: ENS160 </h3>
  
  The Fermion ENS160 Air Quality Sensor, featuring ScioSense's ENS160 sensor chip, is designed for indoor air quality monitoring, detecting multiple IAQ parameters such as TVOC, eCO2, and AQI.
  Its TrueVOC™ technology integrates metal oxide (MOX) technology for improved accuracy, rapid response, and anti-interference capabilities.
  Equipped with on-chip algorithms, it outputs comprehensive environmental data while also feauturing an embedded automatic baseline correction algorithm ensures long-term sensor stability.. The sensor undergoes a 3-minute preheating phase upon power-on.
  The DFRobot ENS160 breakout board features a dual I2C-SPI interface, which personally makes it more appealing than the Sparkfun and Adafruit variants.

- <h3 align="left"> Feiyang SSD1306 OLED [128x64] </h3>
  Cheap monochrome OLED screen featuring contrast control, display RAM and an oscillator. 
  By using https://github.com/afiskon/stm32-ssd1306 built-in synthetic benchmarks I was able to reach 34.5fps, I could probably squeeze a little bit      more performance if I were to bit-bang.
  I opted for the I2C model but there are also SSD1306 variants featuring an SPI interface.

- <h3 align="left"> Voktta ST-LINK V2 </h3>
  Cheap STLink V2 clone, based on a F103CBT6, it gets the job done.

Informations and dependencies

    Built with STM32CubeIde Version: 1.15.0 Build 20695_20240315_1429
    C Standard Library


    
<h3 align="left">Connect with me:</h3>
<p align="left">
<a href="https://twitter.com/axaro11" target="blank"><img align="center" src="https://raw.githubusercontent.com/rahuldkjain/github-profile-readme-generator/master/src/images/icons/Social/twitter.svg" alt="axaro11" height="30" width="40" /></a>
</p>
