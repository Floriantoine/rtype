RFC: R-Type server/client communication protocol

# Problem

The clients need to be able to connect to the server and join or create lobbies to play matches.
We need to define a communication protocol which will allow necessary game information to be conveyed.

# Duration

7 November 2020

# Current state

In draft

# Proposers

* Fahad Assoumani
* Albert Corson

# Details

The communication protocol describe in this RFC needs to allow for:

1. A client to connect to or create a lobby on the server
2. The client to receive necessary data before the start of a game
3. The client to send player inputs to the server
4. The server to send game updates to the clients

During a game, the clients should be displaying the most up-to-date information according to the data sent by the server.

# Proposed solution

# Record of votes

# CC

@Nero-F
@Albert-Corson
@AlexisDelebecque
@adrienlucbert
