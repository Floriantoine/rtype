<p align="center">
  <a>
    <img alt="Coc Logo" src="./r-type.png"/>
  </a>
  <p align="center">A game engine that roars!</p>
</p>

# R-Type

This project is divided into 3 main parts: a game engine, a game, and a server. The goal is to clone the R-Type game and make it multiplayer. The server must be multithreaded and handle multiple game lobbies. The game engine uses a data-oriented implementation of the ECS pattern, and uses the SFML multi-media library for graphics and audio stuff.

## Build

We provide a simple script to setup the project via conan and cmake

```
$ ./build.sh
```

You'll get two binaries located in ./build/bin named `r-type_server` and `r-type_client`.
Launch the server first and then the client.

Enjoy the game

## Documentation

The code is documented, using the Doxygen standard.

## RFC

[An RFC](doc/rfc.md) is provided to describe the communication protocol between the client and the server.

## Feedback

The project could not be finished entirely, because of a lack of time. It includes a functional server, as well as an advanced ECS implementation and a functional game engine and game. However, the game and the server do not communicate.

### Possible improvements

The game engine could be multithreaded pretty easily, enabling parallel computation for heavy tasks such as rendering or physics.

## Authors

| Engine & Game Management | Server/Client & Protocol |
|--------------------------|--------------------------|
| Adrien Lucbert           | Albert Corson            |
| Alexis Delebecque        | Fahad Assoumani          |
