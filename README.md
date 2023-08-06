# Random Key Generation Using ADC of Arty A7 for Cryptographic Applications

## Project Overview
The project aims to develop a robust method for random key generation using the ADC (Analog-to-Digital Converter) of Arty A7 FPGA. The primary goal is to provide a secure and versatile solution for producing unpredictable keys that can be utilized for encryption in various cryptographic applications.

## Methodology
The project involves collecting raw data values from the ADC of Arty A7. These raw values are then used as seeds for the key generation process. To enhance the randomness and security of the generated keys, the obtained seed is further randomized by applying XOR operations with five current seed values. This ensures that the resulting keys are both unique and suitable for cryptographic purposes.

By combining the raw ADC data with the XOR operations,a robust method for generating random keys is created that can be confidently used in various cryptographic applications.

![arty-2](https://github.com/DeepaV22/Random-Key-Generation-ADC-Arty-A7/assets/127031332/59add81e-35c0-4e42-b1e0-570a8e5325d1)


## Key Features
- **Flexibility:** The method allows the generation of keys of any requested size, providing adaptability to diverse cryptographic algorithms.
- **Uniqueness:** The generated keys exhibit a high level of uniqueness, with a verification result of 99.55%. This ensures robust security for encryption.
- **Practical Applications:** The keys produced by our method can be seamlessly integrated into a wide range of cryptographic scenarios, enhancing data confidentiality and integrity.

## Prerequisites
- Vivado Design Suite for hardware platform creation.
- Vitis IDE for software development.
- Arty A7 FPGA board with XADC, MicroBlaze, and UART components.

## Setup Instructions
1. Connect the Arty A7 board to your computer.
2. Use Vivado to create the hardware platform, integrating XADC, MicroBlaze, and UART.
3. Import the platform into Vitis and write the code for random key generation.
4. Compile and deploy the software onto the FPGA.

## Usage
1. Power on the Arty A7 board.
2. Execute the code on the FPGA to generate random keys from the ADC data.
3. Utilize the generated keys in encryption algorithms of your choice by integrating them into your software.

## Results
The verification of key uniqueness was conducted using 1107 collected values. The obtained result demonstrated an impressive uniqueness percentage of 99.55%. This high level of uniqueness contributes significantly to the security of the generated keys and their suitability for cryptographic applications.
![19768972-7655-476a-8bd0-d280ccc8f0bc](https://github.com/DeepaV22/Random-Key-Generation-ADC-Arty-A7/assets/127031332/1f50a844-770a-4048-b179-47e74d75604f)
![1b3a7f78-4786-40dc-a483-a71550206e04](https://github.com/DeepaV22/Random-Key-Generation-ADC-Arty-A7/assets/127031332/416785a4-3e70-491a-86bd-adbfdb7d84cc)
![0fb0d1c4-af23-407c-81ff-6d583a274fd8](https://github.com/DeepaV22/Random-Key-Generation-ADC-Arty-A7/assets/127031332/ce3053b3-5ab0-42b4-a110-52ba2b13a643)


