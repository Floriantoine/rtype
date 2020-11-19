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
    | 3       | [POSITION](#POSITION)     | UDP      | No                |
    | 4       | [MOVE](#MOVE)             | UDP      | Yes               |
    | 5       | [SPAWN](#SPAWN)           | UDP      | Yes               |
    | 6       | [DESTROY](#DESTROY)       | UDP      | Yes               |
    | 7       | [GRAB](#GRAB)             | UDP      | Yes               |
    | 8       | [DROP](#DROP)             | UDP      | Yes               |
    | 9       | [CHARGE](#CHARGE)         | UDP      | Yes               |
    | 10      | [SHOOT](#SHOOT)           | UDP      | Yes               |
    | 11      | [HIT](#HIT)               | UDP      | Yes               |
    | 12      | [JOIN](#JOIN)             | UDP      | Yes               |
    | 13      | [LEAVE](#LEAVE)           | UDP      | Yes               |

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
|  2 bytes   |
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
+------------+----------+
| LOBBY_PORT | LOBBY_ID |
|  unsigned  | unsigned |
|  2 bytes   |  6 bytes |
+------------+----------+
```

## UDP in-game connection

### **GAME_STATE**
* <ins>STATE</ins>: the state of the game:
    - **0**: game awaiting start
    - **1**: game running
    - **2**: game won (must only be sent by the server)
    - **3**: game lost (must only be sent by the server)
    - **4**: game timeout: lobby/player inactive for too long (must only be sent by the server)
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
### **POSITION**
* <ins>ENTITY_ID</ins>: entity unique identifier
* <ins>X_COORDINATE</ins>: x coordinate in the scene
* <ins>Y_COORDINATE</ins>: y coordinate in the scene
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

___
### **MOVE**
* <ins>ENTITY_ID</ins>: entity unique identifier of the corresponding player
* <ins>DIRECTION</ins>:
    - 0: up
    - 1: left
    - 2: down
    - 3: right
* <ins>STATE</ins>: boolean describing the state of the movement (ON or OFF)
#### REQUEST:
#### *From client:*
> Must send the players' move direction
```
+-----------+-----------+-----------+
| ENTITY_ID | DIRECTION |  STATE    |
|  unsigned | unsigned  | unsigned  |
|   8 bytes |  1 byte   |  1 byte   |
+-----------+-----------+-----------+
```

___
### **SPAWN**
* <ins>ENTITY_ID</ins>: entity unique identifier
#### REQUEST:
#### *From server:*
> Must tell the client a new entity has spawned
> The component consists of the component name (used to call a factory function) followed by the binary content of the component (used by the factory)
```
+-----------+-------------+
| ENTITY_ID | ENTITY_JSON |
|  unsigned |  unsigned   |
|   8 bytes |  until '\0' |
+-----------+-------------+
```

___
### **DESTROY**
* <ins>ENTITY_ID</ins>: entity unique identifier
#### REQUEST:
#### *From server:*
> Must tell the client to destroy a given entity
```
+-----------+
| ENTITY_ID |
|  unsigned |
|  8 bytes  |
+-----------+
```

___
### **GRAB**
* <ins>ENTITY_ID</ins>: entity unique identifier that will grab an object
* <ins>ENTITY_ID</ins>: entity unique identifier of the grabbed object
* <ins>DIRECTION</ins>: entity unique identifier:
    - **0**: attach to the front
    - **1**: attach to the back
#### REQUEST:
#### *From server:*
> Must notify a client that an upgrade has been picked up by a player (attached to him). Depending on the type of power-up, the DIRECTION may not be present in the body
```
+-----------+-----------+?+------------+
| ENTITY_ID | ENTITY_ID |?| DIRECTION  |
|  unsigned |  unsigned |?|  unsigned  |
|   8 bytes |  8 bytes  |?|   1 byte   |
+-----------+-----------+?+------------+
```

___
### **DROP**
* <ins>ENTITY_ID</ins>: entity unique identifier
#### REQUEST:
#### *From both:*
> From client: must tell the server that the player dropped his force (shield). No body should be sent.
> From server: must notify the clients that a player dropped his force (shield)
```
+-----------+
| ENTITY_ID |
|  unsigned |
|  8 byte   |
+-----------+
```

___
### **CHARGE**
* <ins>ENTITY_ID</ins>: entity unique identifier
#### REQUEST:
#### *From client:*
> Must notify the server that the client starts charging a shot
```
+-----------+
| ENTITY_ID |
| unsigned  |
|  8 bytes  |
+-----------+
```

___
### **SHOOT**
* <ins>ENTITY_ID</ins>: entity unique identifier
* <ins>IS_VALID</ins>: a boolean telling if the shot was validated
#### REQUEST:
#### *From client:*
> Must notify the server a client shot
```
+-----------+
| ENTITY_ID |
| unsigned  |
|  8 byte   |
+-----------+
```
#### RESPONSE:
#### *From server:*
> Must give the entity id to assign to the shot
```
+----------+-----------+
| IS_VALID | ENTITY_ID |
| unsigned | unsigned  |
|  1 byte  |  8 bytes  |
+----------+-----------+
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
* <ins>ENTITY_ID</ins>: the entity id of the players
* <ins>MAP_NAME</ins>: a string containing the name of the map to load
#### REQUEST:
#### *From client:*
> An empty body should be sent
#### RESPONSE:
#### *From server:*
> If <ins>ENTITY_ID</ins> is greater than 3 the client's connection has been refused
```
+-----------+--------------+--------------+------------------------+
| ENTITY_ID | X_COORDINATE | Y_COORDINATE |        MAP_NAME        |
| unsigned  |    signed    |    signed    |        unsigned        |
|  8 bytes  |   8 bytes    |    8 bytes   | (BODY_SIZE - 24) bytes |
+-----------+--------------+--------------+------------------------+
```

___
### **LEAVE**
* <ins>ENTITY_ID</ins>: the entity id of the players
#### REQUEST:
#### *From client:*
> Must notify the server that the client is leaving the game
```
+-----------+
| ENTITY_ID |
| unsigned  |
|  8 bytes  |
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
