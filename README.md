# Computer Graphic Project

# 🏙️ Urban Scenery with interection and animation

This project is a 2D animated city scene created using C++ and OpenGL (GLUT). It simulates buildings, windows with interactive lighting, animated clouds, a movable car, and a day/night toggle based on user interaction.

---

## 🚀 Features

- 🏢 **Multiple Buildings**: Automatically generated windows and doors.
- 💡 **Interactive Windows**: Toggle window lights at night by clicking.
- ☀️ **Day/Night Cycle**: Click the sun or moon to change the time of day.
- ☁️ **Animated Clouds**: Clouds move continuously across the sky.
- 🚗 **Movable Car**: Use arrow keys to move the car on the road.

---

## 🎮 Controls

| Action                  | Input              |
|-------------------------|--------------------|
| Toggle Day/Night        | Click on Sun/Moon  |
| Toggle Window Light     | Click on Window (Night Only) |
| Move Car Left           | ← Arrow Key        |
| Move Car Right          | → Arrow Key        |
| Move Car Up             | ↑ Arrow Key        |
| Move Car Down           | ↓ Arrow Key        |

---

## 🧱 Code Structure

### Main Components

- `drawBuildings()`: Draws all buildings and doors
- `drawWindows()`: Renders windows with dynamic lighting
- `drawSky()`: Renders the sky color (based on time of day)
- `drawSun()`: Draws the sun or moon
- `drawCloud()`: Renders stylized clouds
- `drawRoad()`: Draws road with lane markers
- `drawCar()`: Draws car and wheels

### Interaction Functions

- `mouseClick(...)`: Detects clicks on sun/moon or windows
- `keyboard(...)`: Responds to arrow key movement
- `updateClouds(...)`: Animates clouds on a timer

---

## 🛠️ Setup & Usage

### Prerequisites

- C++ Compiler (e.g., `g++`)
- OpenGL and GLUT libraries installed

### Team members:
Ramim, Mim, Sazzad
