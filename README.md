# Shelfr - Media Collection Manager

A modern, cross-platform media collection manager built with C++ and Qt framework. Shelfr helps you organize and manage your personal media collection including books, films, music, and video games.

## Features

- **Multi-Media Support**: Manage books, films, music, and video games in one place
- **Intuitive GUI**: Clean and user-friendly interface built with Qt
- **Theme Support**: Switch between light and dark themes
- **Advanced Search**: Filter and search through your media collection
- **JSON Storage**: All data stored in portable JSON format
- **Visitor Pattern**: Implemented for media-specific operations and filtering


## Media Types Supported

- **Books**: Title, author, genre, publication year, ISBN, etc.
- **Films**: Title, director, genre, release year, duration, etc.
- **Music**: Album, artist, genre, release year, track list, etc.
- **Video Games**: Title, platform, genre, release year, developer, etc.

## Design Patterns

The application utilizes several design patterns:

- **Visitor Pattern**: For media-specific operations and filtering
- **Model-View-Controller**: Separation of data, presentation, and logic
- **Factory Pattern**: Media object creation
- **Singleton Pattern**: Managers (ThemeManager, JsonManager)

## Project Structure

```bash

Shelfr/
├── headers/                        
│   ├── core/                       
│   │   ├── book.h
│   │   ├── film.h
│   │   ├── jsonmanager.h
│   │   ├── media.h                 
│   │   ├── mediavisitorinterface.h
│   │   ├── music.h
│   │   └── videogame.h
│   └── gui/                        
│       ├── mainwindow.h
│       ├── sidebar.h
│       ├── workspace.h
│       ├── views/          
│       ├── mediacard.h     
│       └── thememanager.h
├── src/                    
│   ├── core/               
│   └── gui/                
├── styles/                 
│   ├── dark.css
│   └── light.css
├── media.json              
└── resources.qrc           