# Blue Unlock

> A cozy football game built with Raylib, inspired by the manga/anime "Blue Lock".

## Table of Contents

- [About](#about)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Configuration](#configuration)
- [Project Structure](#project-structure)
- [Known Issues](#known-issues)
- [Contributing](#contributing)
- [License](#license)
- [Disclaimer / Credits](#disclaimer--credits)

## About

It is come from the project *Simple Ping Pong* game, and took a week to make it. I also challenge to myself. I WON'T USE ANY OTHERS ASSETS FOR CREATING THIS. But I used audio files :P. Okay. Just let it to be an exception of audio files. 

> This game could be in production. Also didn't add yet, primary features like football physics😅.

## Features

- **Primitive-Only Rendering:** All visuals are drawn using Raylib's basic shapes (like `DrawRectangle`, `DrawCircle`) without any external visual assets (except audio).
- **Custom Pixel Font:** A custom font built entirely using `DrawRectangle()` calls.
- **Player Movement:** Smooth WASD controls with `Lerp`-based camera follow.
- **Stamina System:** Sprinting and kicking consume stamina, which regenerates over time.
- **Dynamic HUD:** Custom UI (HUD) designed with a clean, minimalist style.
- **Audio Integration:** Sound effects loaded for immersion.

### Screenshots

![Title Screen](docs/screenshots/screenshots(0).png)

![Gameplay](docs/screenshots/screenshots(2).png)

![](docs/screenshots/screenshots(3).png)

![](docs/screenshots/screenshots(4).png)

![](docs/screenshots/screenshots(5).png)

![](docs/screenshots/screenshots(6).png)

![](docs/screenshots/screenshots(7).png)

![](docs/screenshots/screenshots(8).png)

![](docs/screenshots/screenshots(9).png)

## Requirements

- **C99** (and higher)
- **CMake**
- **Raylib**

## Installation

```bash
git clone https://github.com/lutherhistory/Blue-Unlock.git
cd Blue-Unlock
mkdir build && cd build
cmake ..
make
```

## Usage

Run the compiled executable:
```Bash
./game
```

Basic Controls (v0.0.3 Alpha):
- WASD: the player
- Left Shift: Sprint (consumes stamina)
- Space: Kick / Basic Interaction (coming soon)

## Project Structure

```
.
├── assets
│   └── audios
│       ├── ball-bouncing.wav
│       ├── floodlight.mp3
│       ├── floodlight.wav
│       ├── football-before-match.mp3
│       └── football-fan-shout.mp3
├── CMakeLists.txt
├── compile_commands.json -> compile_commands.json
├── docs
│   ├── first-version.png
│   ├── recreation-v3.png
│   ├── screenshots
│   ├── second-version.png
│   └── todo.md
├── inc
│   ├── colour.h
│   ├── football
│   │   ├── pitch.h
│   │   ├── player.h
│   │   └── referee.h
│   ├── hud
│   │   └── shape.h
│   ├── managers
│   │   └── game.h
│   └── need.h
├── lib
├── README.md
├── src
│   ├── football-pitch.c
│   ├── football-player.c
│   ├── football-referee.c
│   ├── GameManager.c
│   ├── hud-shape.c
│   └── main.c
└── test
    └── main.test.c
```

## Known Issues

- [ ] Suck stamina😅, but balance.
- [ ] What should I do? Keep using the temporary rectangular textures for players🤔?
- [ ] The ball is hiding from us😶‍🌫️ JK, it has been not working👻
- [ ] Yeah, football opponents AI is still dream😴

## Contributing

Contributions, issues, and pull requests are welcome.

## License

This project is licenesed under the MIT License.
See ![[LICENSE]]  for details.

## Disclaimer / Credits:
This project is a personal, non-commercial fan-made game. It is heavily inspired by the manga/anime series "Blue Lock" (created by Muneyuki Kaneshiro and Yusuke Nomura). All rights to the original "Blue Lock" belong to their respective owners. This game is not affiliated with or endorsed by them.
