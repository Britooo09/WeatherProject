# ☁️ Weather Project

**Weather Project** is my second complete project, and the first one intended solely for personal and practice purposes. It is a console application written in C++, aimed at consulting, processing, and displaying up-to-date weather information for any city in the world, based on the options chosen by the user.

All data is obtained through a connection to the [OpenWeatherMap API](https://openweathermap.org/api). This project uses [libraries and other technologies developed by third parties](#credits).

## Main Features

**Weather Project** focuses on the usability and flexibility of its console interface:

### Navigation and Search

- **Multiple Query Methods:** Full support for quick search (by name, name + country code, or city ID), advanced search, and instant repetition of the last query.
- **Advanced Search with Geocoding:** The advanced search system now uses OpenWeatherMap's Geocoding service to resolve ambiguous city names, presenting the user with a list of options for precise selection.
- **Menu Flexibility:** The navigation system allows users to dynamically switch between different query modes without having to restart the flow.
- **Technical Data Display:** An option is included to view crucial technical data about a city (such as its ID or coordinates) directly from the search menu.

### Architecture and Stability

- **Modularization:** The code is completely divided into modules (`.cpp`/`.h`) to facilitate maintenance and future development.
- **Configuration Management:** Improved logic for managing program configuration, including validations and fallback mechanisms to prevent data reading failures.
- **Error Handling:** Includes numerous checkpoints and data validations to ensure application stability, preventing unexpected crashes.

## Getting Started

To compile and run **WeatherProject**, you need to have a C++ compiler and a CMake-compatible package management system installed.

### Prerequisites

- C++ compiler compatible with the C++20 standard.
- [CMake](https://cmake.org/) (minimum version 3.16).
- [ninja](https://ninja-build.org/).
- [vcpkg](https://vcpkg.io/en/index.html).

### Dependencies

This project uses the following third-party libraries:

| Dependency | Purpose |
| - | - |
| `curl` | Management of HTTP requests to the weather API |
| `nlohmann/json` | Parsing and manipulation of JSON data from the API |

### API Key

You must register at [OpenWeatherMap](https://home.openweathermap.org/users/sign_up) and obtain your own API key (the free plan is sufficient).

1. Go to [this link](https://home.openweathermap.org/api_keys) and generate an API key.
2. Create a file called `api_keys.hpp` anywhere on your computer.
3. Add the following code to the file, replacing `[YOUR_API_KEY]` with your personal key obtained in step 1:

```c++
#ifndef OWM_API_KEY
#define OWM_API_KEY

const std::string OPENWEATHERMAP_API_KEY = "[YOUR_API_KEY]";

#endif
```

> [!NOTE]
> The `api_keys.hpp` file is excluded from version control using `.gitignore` to ensure security.

### Compilation

To build the project in a general environment:

1. Clone the Repository:
```bash
git clone https://github.com/Britooo09/WeatherProject.git
cd WeatherProject
```
2. Move the `api_keys.hpp` file you created earlier to the `lib/` folder of the cloned repository.
3. Install dependencies with vcpkg:
```bash
vcpkg install curl nlohmann-json
```
4. Configure and Compile with CMake:
```bash
cmake -B build -S . -G “Ninja” -DCMAKE_TOOLCHAIN_FILE=[PATH_TO_VCPKG]/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

To build the project in Visual Studio, simply open the folder containing the `CMakeLists.txt` file with the IDE. Make sure you have all the prerequisites installed and correctly configured, including the relevant environment variables.

### Running the program

Once compiled, the executable will be located in the `build/` directory (or similar, depending on your CMake configuration).

- **In Console:** Run the binary:
```bash
./build/WeatherProject      # Example on Linux/macOS
.\build\WeatherProject.exe  # Example on Windows
```

- **Graphical Mode on Windows:** The program can be run by double-clicking directly on the `WeatherProject.exe` file.

## License

Distributed under the [MIT License](https://opensource.org/licenses/MIT). See the [`LICENSE`](https://github.com/Britooo09/WeatherProject/blob/main/LICENSE) file for more information.

## Credits

This project is made possible by the dedication of the open source communities and developers of the following technologies:

- **[OpenWeatherMap](https://openweathermap.org/):** For providing a robust and accessible weather API that powers the core functionality of the application.
- **[CMake](https://cmake.org/):** For the cross-platform automation, configuration, and compilation system that manages the project build.
- **[Ninja](https://ninja-build.org/):** The fast build system that speeds up the project compilation process.
- **[vcpkg](https://vcpkg.io/en/index.html):** For its service as a C/C++ package manager for dependency management.
- **[cURL](https://curl.se/):** For the fundamental library used to make HTTP requests to the OpenWeatherMap API.
- **[nlohmann/json](https://github.com/nlohmann/json):** For the JSON parsing and manipulation library, crucial for processing API responses.
