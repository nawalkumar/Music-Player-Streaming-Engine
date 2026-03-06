🎵 Music Player Streaming Engine

A modular Music Player Streaming Engine built using Object-Oriented Design principles and multiple Design Patterns.
The system simulates the backend logic of a modern music streaming platform, allowing flexible playback strategies, device connectivity, playlist management, and simplified interaction with complex subsystems.

This project demonstrates Low-Level System Design (LLD) concepts and design pattern implementations commonly used in scalable software systems.

🚀 Features

🎧 Playlist Management

🔀 Multiple Playback Strategies

📡 Device Connectivity (Bluetooth, speakers, etc.)

🎼 Song Streaming Simulation

🧠 Modular Architecture using Design Patterns

🧩 Simplified interface using Facade

⚡ Command-based action execution (Play, Pause, Next, etc.)

🏗 System Architecture
User
  │
  ▼
MusicSystemFacade
  │
  ├── PlaylistManager (Singleton)
  ├── DeviceManager (Singleton)
  ├── StreamingEngine (Singleton)
  │
  ▼
Player
  │
  ▼
Playback Strategy
(Sequential / Random / Custom Queue)
  │
  ▼
DeviceFactory
  │
  ▼
Adapter
(External Device Integration)

The Facade acts as the main entry point that coordinates all subsystems.

🧠 Design Patterns Implemented

1️⃣ Strategy Pattern


Used to support different song playback strategies.

Playback modes include:

Sequential Play

Random Play

Custom Queue Play

This allows the system to switch playback behavior dynamically at runtime.

Example:

PlayStrategy
   ├── SequentialPlay
   ├── RandomPlay
   └── CustomQueuePlay
   
2️⃣ Factory Pattern


Used to create device objects dynamically without exposing creation logic.

Supported devices may include:

Bluetooth Speaker

Wired Headphones

Smart Speaker

External Audio Device

Example:

DeviceFactory → createDevice(type)

3️⃣ Adapter Pattern


Used to integrate external or third-party audio devices whose interfaces differ from the internal player interface.

The adapter converts external APIs into a common device interface so the player can interact with them seamlessly.

ExternalDeviceAPI
      │
      ▼
 DeviceAdapter
      │
      ▼
   Player
   
4️⃣ Singleton Pattern


Ensures that only one instance of core managers exists in the system.

Singleton is used for:

PlaylistManager

DeviceManager

StreamingEngine

Benefits:

Global access

Controlled resource usage

Consistent system state

5️⃣ Facade Pattern


Provides a simplified interface to interact with complex subsystems.

Instead of interacting with multiple managers directly, the client communicates through:

MusicSystemFacade

Example:

musicFacade.playSong("SongName");

The facade internally coordinates:

Playlist Manager

Device Manager

Streaming Engine

Player

6️⃣ Command Pattern


Encapsulates actions as command objects, allowing flexible command execution.

Commands include:

    PlaySongCommand
    
    PauseSongCommand
    
    NextSongCommand
    
    PreviousSongCommand

Flow:

    User → UI Button → Command → MusicPlayer

Benefits:

    Decouples request sender and receiver
    
    Enables command queuing
    
    Supports undo/redo operations

📂 Project Structure
Music-Player-Streaming-Engine
│
├── models
│   ├── Song
│   ├── Playlist
│
├── managers
│   ├── PlaylistManager
│   ├── DeviceManager
│   └── StreamingEngine
│
├── strategies
│   ├── SequentialPlay
│   ├── RandomPlay
│   └── CustomQueuePlay
│
├── factory
│   └── DeviceFactory
│
├── adapters
│   └── DeviceAdapter
│
├── commands
│   ├── PlayCommand
│   ├── PauseCommand
│   └── NextCommand
│
├── facade
│   └── MusicSystemFacade
│
└── main.cpp
💻 Technologies Used

    C++
    
    Object-Oriented Programming
    
    Design Patterns
    
    Data Structures

🎯 Learning Objectives

This project demonstrates:

    Low Level System Design
    
    Design Pattern Implementation
    
    Clean Modular Architecture
    
    Real-world system modeling

It serves as a practice project for software engineering interviews and system design preparation.

🔮 Future Improvements


    Possible enhancements include:
    
    Song recommendation engine
    
    Streaming buffer simulation
    
    Observer pattern for playback events
    
    Undo/Redo command history
    
    UI integration

👨‍💻 Author

    Naval Kumar
    
    Computer Science Engineering Student
    Interested in System Design, Backend Development, and Scalable Architectures
