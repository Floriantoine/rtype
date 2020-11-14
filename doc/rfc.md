RFC: R-Type server/client communication protocol


# Problem
The clients need to be able to connect to the server and join or create lobbies to play matches.
We need to define a communication protocol which will allow necessary game information to be conveyed.


# Duration
7 November 2020 - 11 November 2020
14 November 2020 (added METHODs to join and leave lobbies and map name transmission)


# Current state
Approved


# Proposers
* Fahad Assoumani
* Albert Corson
* Adrien Lucbert


# Details
The communication protocol describe in this RFC needs to allow for:

1. A client to connect to or create a lobby on the server
2. The client to receive necessary data before the start of a game
3. The client to send player inputs to the server
4. The server to send game updates to the clients

During a game, the clients should be displaying the most up-to-date information according to the data sent by the server.


# Proposed solution
The connection to the server must be established in two steps:  

* A first connection client to the server in TCP which must then allow it get sufficient information to connect to a lobby and/or to create one.
* Then, connection to the lobby in UDP.

## Data header
For all type of connections, the data sent must respect the following binary format:

```c
<                       header                    > <       body        >
+--------+--------+-----------+--------------------+--------------------+
|  TYPE  | METHOD | BODY_SIZE | CREATION_TIMESTAMP |       BODY...      |
| 2 bits | 6 bits |  8 bytes  |      8 bytes       | BODY_SIZE bytes... |
+--------+--------+-----------+--------------------+--------------------+
```

* <ins>TYPE</ins>: tells type of the IO operation. Must be one of those values:
    - **0**: request
    - **1**: response (a.k.a. the response of a previous request)

* <ins>METHOD</ins>: the type of action required. If <ins>TYPE</ins> equals 1, this is a response to a previous request. Must be one of those values:

    | Decimal | Action                    | Protocol | Need confirmation |
    |---------|---------------------------|----------|-------------------|
    | 0       | [ASK_JOIN](#ASK_JOIN)     | TCP      | No                |
    | 1       | [CREATE](#CREATE)         | TCP      | No                |
    |---------|---------------------------|----------|-------------------|
    | 2       | [GAME_STATE](#GAME_STATE) | UDP      | Yes               |
    | 3       | [MOVE](#MOVE)             | UDP      | No                |
    | 4       | [SPAWN](#SPAWN)           | UDP      | Yes               |
    | 5       | [DESTROY](#DESTROY)       | UDP      | Yes               |
    | 6       | [GRAB](#GRAB)             | UDP      | Yes               |
    | 7       | [DROP](#DROP)             | UDP      | Yes               |
    | 8       | [CHARGE](#CHARGE)         | UDP      | Yes               |
    | 9       | [SHOOT](#SHOOT)           | UDP      | Yes               |
    | 10      | [HIT](#HIT)               | UDP      | Yes               |
    | 11      | [JOIN](#JOIN)             | UDP      | Yes               |
    | 12      | [LEAVE](#LEAVE)           | UDP      | Yes               |

* <ins>BODY_SIZE</ins>: must represent the size of the BODY preceding the header in bytes

* <ins>CREATION_TIMESTAMP</ins>: must represent the creation date of the request. It <ins>TYPE</ins> equals 1, this must be the the <ins>CREATION_TIMESTAMP</ins> of the request this responds to.

## Request confirmations:
If a confirmation is required, the response must at least contain a header even if the <ins>METHOD</ins> doesn't need a body to be sent back.


## TCP pre-game connection

### **ASK_JOIN**
* <ins>LOBBY_ID</ins>: ID of the lobby (6 ascii characters)
* <ins>LOBBY_PORT</ins>: decimal value of the port of the lobby's UDP socket to join
#### REQUEST:
#### *From client:*
> Must Asks the serer to join the lobby.

```
+----------+
| LOBBY_ID |
| unsigned |
|  6 bytes |
+----------+
```
#### RESPONSE:
#### *From server:*
> If <ins>LOBBY_PORT</ins> isn't equal to 0, the server must disconnect the client from the TCP socket. The client should then connect to the UDP socket of the lobby
```
+------------+
| LOBBY_PORT |
|  unsigned  |
|  4 bytes   |
+------------+
```

___
### **CREATE**
#### REQUEST:
#### *From client:*
> Must contain the name of the map to create
```
+-----------------+
|    MAP_NAME     |
|    unsigned     |
| BODY_SIZE bytes |
+-----------------+
```
#### RESPONSE:
#### *From server:*
> If <ins>LOBBY_PORT</ins> isn't equal to 0, the server has created a lobby and must disconnect the client from the TCP socket. The client should then connect to the UDP socket of the lobby
```
+------------+
| LOBBY_PORT |
|  unsigned  |
|  4 bytes   |
+------------+
```

## UDP in-game connection

### **GAME_STATE**
* <ins>STATE</ins>: the state of the game:
    - **0**: game awaiting start
    - **1**: game starting/resuming
    - **2**: game paused
    - **3**: game won (must only be sent by the server)
    - **4**: game lost (must only be sent by the server)
#### REQUEST:
#### *From both:*
> Change the state of the game
```
+----------+
|  STATE   |
| unsigned |
|  1 byte  |
+----------+
```

___
### **MOVE**
* <ins>ENTITY_ID</ins>: entity unique identifier
* <ins>PLAYER_ID</ins>: the players' unique identifier (0-3)
* <ins>X_COORDINATE</ins>: x coordinate in the scene
* <ins>Y_COORDINATE</ins>: y coordinate in the scene
* <ins>DIRECTION</ins>:
    - 1: up
    - 2: down
    - 4: left
    - 8: right
    - 5: up and left (up | left)
    - 9: up and right (up | right)
    - 6: down and left (down | left)
    - 10: down and right (down | right)
#### REQUEST:
#### *From server:*
> Must send an entity's new position
```
+------------+--------------+--------------+
| ENTITY_ID  | X_COORDINATE | Y_COORDINATE |
|  unsigned  |    signed    |    signed    |
|   8 bytes  |   8 bytes    |    8 bytes   |
+------------+--------------+--------------+
```
#### *From client:*
> Must send the players' move direction
```
+------------+-----------+
| PLAYER_ID  | DIRECTION |
|  unsigned  | unsigned  |
|   1 byte   | 1 bytes   |
+------------+-----------+
```

___
### **SPAWN**
* <ins>ENTITY_ID</ins>: entity unique identifier
#### REQUEST:
#### *From server:*
> Must tell the client a new entity has spawned
> The component consists of the component name (used to call a factory function) followed by the binary content of the component (used by the factory)
```
               |<         component list        >|
+------------+?+----------------+----------------+
| ENTITY_ID  |?| COMPONENT_NAME |                |
|  unsigned  |?|    unsigned    | COMPONENT_BODY |
|   8 bytes  |?|   until '\0'   |                |
+------------+?+----------------+----------------+
```

___
### **DESTROY**
* <ins>ENTITY_ID</ins>: entity unique identifier
#### REQUEST:
#### *From server:*
> Must tell the client to destroy a given entity
```
+------------+
| ENTITY_ID  |
|  unsigned  |
|  8 bytes   |
+------------+
```

___
### **GRAB**
* <ins>PLAYER_ID</ins>: the players' unique identifier (0-3)
* <ins>ENTITY_ID</ins>: entity unique identifier
* <ins>DIRECTION</ins>: entity unique identifier:
    - **0**: attach to the front
    - **1**: attach to the back
#### REQUEST:
#### *From server:*
> Must notify a client that an upgrade has been picked up by a player (attached to him). Depending on the type of power-up, the DIRECTION may not be present in the body
```
+-----------+-----------+?+------------+
| PLAYER_ID | ENTITY_ID |?| DIRECTION  |
|  unsigned |  unsigned |?|  unsigned  |
|  1 byte   |  8 bytes  |?|   1 byte   |
+-----------+-----------+?+------------+
```

___
### **DROP**
* <ins>PLAYER_ID</ins>: player unique identifier
#### REQUEST:
#### *From both:*
> From client: must tell the server that the player dropped his force (shield). No body should be sent.
> From server: must notify the clients that a player dropped his force (shield)
```
+-----------+
| PLAYER_ID |
|  unsigned |
|  1 byte   |
+-----------+
```

___
### **CHARGE**
* <ins>PLAYER_ID</ins>: the players' unique identifier (0-3)
#### REQUEST:
#### *From client:*
> Must notify the server that the client starts charging a shot
```
+-----------+
| PLAYER_ID |
| unsigned  |
|  1 byte   |
+-----------+
```

___
### **SHOOT**
* <ins>PLAYER_ID</ins>: player unique identifier
#### REQUEST:
#### *From client:*
> Must notify the server a client shot
```
+-----------+
| PLAYER_ID |
| unsigned  |
|  1 byte   |
+-----------+
```
#### RESPONSE:
#### *From server:*
> Must give the entity id to assign to the shot
```
+-----------+
| ENTITY_ID |
| unsigned  |
|  8 bytes  |
+-----------+
```

___
### **HIT**
* <ins>ENTITY_ID</ins>: entity unique identifier
#### REQUEST:
#### *From server:*
> Must notify clients a shot hit a target
```
+-----------+
| ENTITY_ID |
| unsigned  |
|  8 bytes  |
+-----------+
```

___
### **JOIN**
* <ins>PLAYER_ID</ins>: the players' unique identifier (0-3)
* <ins>MAP_NAME</ins>: a string containing the name of the map to load
#### REQUEST:
#### *From client:*
> An empty body should be sent
#### RESPONSE:
#### *From server:*
> If <ins>PLAYER_ID</ins> is greater than 3 the client's connection has been refused
```
+-----------+-----------------------+
| PLAYER_ID |        MAP_NAME       |
| unsigned  |        unsigned       |
|  1 byte   | (BODY_SIZE - 1) bytes |
+-----------+-----------------------+
```

___
### **LEAVE**
* <ins>PLAYER_ID</ins>: the players' unique identifier (0-3)
#### REQUEST:
#### *From client:*
> Must notify the server that the client is leaving the game
```
+-----------+
| PLAYER_ID |
| unsigned  |
|  1 byte   |
+-----------+
```


# Record of votes
| Vote | Name              |
|------|-------------------|
| +1   | Fahad Assoumani   |
| +1   | Albert Corson     |
| +1   | Alexis Delebecque |
| +1   | Adrien Lucbert    |


# CC
[@Fahad Assoumani](https://github.com/Nero-F)  
[@Albert Corson](https://github.com/Albert-Corson)  
[@Alexis Delebecque](https://github.com/AlexisDelebecque)  
[@Adrien Lucbert](https://github.com/adrienlucbert)  
