# The Readout Project
This project aims to support as many MCUs with READOUT PROTECTION, providing ready-to-use code to implement ROM chips for security features across a wide range of MCUs

### About The Project
Having a ROM component is an essential part of a secure boot process. Every low-level or embedded project that stores cryptographic material or simply requires its IP to be kept safe, having a readout protection enabled is crucial. It appears that a ton of MCUs have this kind of feature implemented within them, but is seldom activated due to complex configuration and deep datasheet digging that is required.

This project's aim is to provide a ready-to-use source code along with a sample barebone implementation of as many MCUs as possible, enabling these protections, the right way.

IMPORTANT NOTE: Although having a readout protection is crucial for secure boot, secure storage and other security features, this project DOES NOT GUARANTEE other attack vector protections. Examples such as fault injection or power analysis are out of the scope of this project. For devices which are truly invulnerable to deeply intrusive attacks, it is strongly suggested to find MCUs that explicitly target these requirements.

Sword of Secrets is a hardware hacking challenge. It is suitable for both novice and experienced tinkerers and hackers. It utilizes a low number of components to make the challenge easier to grasp, but hold in itself enough intricacies that will require the challenger a keen eye and sharp mind to solve all challenges.

To solve the challenge you will need to discover a series of flags, hidden inside the sword. Each one will help you unlock the next step in the challenge, to finally reveal the ultimate secret the sword holds.

## Current Support
| Vendor | MCU | Programmer | Support |
|--------|-----|------------|---------|
| WCH | CH32V003 | WCH-LinkE | ✅ |
| Atmel | ATMega328p | ISP | ✅ |


<!-- LICENSE -->
## License

Distributed under the MIT License.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Gili Yankovitch - [@GiliYankovitch](https://x.com/GiliYankovitch) - giliy@nyxsecurity.net
