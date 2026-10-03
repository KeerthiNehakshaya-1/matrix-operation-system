# Matrix Operation System

A web-based Matrix Operation System that combines a C++ matrix processing backend with a responsive HTML, CSS, and JavaScript frontend.

The system allows users to enter matrices dynamically and perform different mathematical operations through a simple web interface. The calculations are handled by the C++ backend, while the frontend provides the user interface and displays the results.

## 🚀 Live Application

**Live Website:**  
https://matrix-operation-system-yozy.onrender.com


## 📌 Features

- Dynamic matrix size selection from 1 × 1 to 10 × 10
- Dynamic matrix input generation
- Keyboard navigation using arrow keys
- Enter key navigation between matrix elements
- Matrix A and Matrix B input
- Clear Matrix functionality
- Mathematical matrix formatting
- Separate result page
- Input validation
- Error handling
- C++ backend processing
- REST-style JSON communication
- Docker-based deployment
- Public web deployment using Render

## 🧮 Supported Operations

The system supports the following six operations:

1. Addition
2. Subtraction
3. Multiplication
4. Transpose
5. Determinant
6. Inverse

### Addition

Adds corresponding elements of two matrices.

### Subtraction

Subtracts corresponding elements of Matrix B from Matrix A.

### Multiplication

Performs matrix multiplication when the number of columns of Matrix A matches the number of rows of Matrix B.

### Transpose

Converts rows of a matrix into columns and columns into rows.

### Determinant

Calculates the determinant of a square matrix.

### Inverse

Calculates the inverse of a non-singular square matrix.

## 🛠️ Technologies Used

### Frontend

- HTML5
- CSS3
- JavaScript

### Backend

- C++
- cpp-httplib
- nlohmann/json

### Deployment

- Docker
- GitHub
- Render

## 🏗️ System Architecture


                         USER
                           │
                           ▼
                    Web Browser
                           │
                           ▼
              HTML + CSS + JavaScript
                           │
                       HTTP / JSON
                           │
                           ▼
                    C++ Web Server
                           │
                           ▼
                     Matrix Class
                           │
          ┌────────────────┼────────────────┐
          │                │                │
          ▼                ▼                ▼
      Addition        Subtraction     Multiplication
          │
          ├──────────► Transpose
          │
          ├──────────► Determinant
          │
          └──────────► Inverse
                           │
                           ▼
                    JSON Response
                           │
                           ▼
                     Result Page


## 📂 Project Structure

Matrix Operation System
│
├── frontend
│   ├── index.html
│   ├── style.css
│   ├── script.js
│   └── result.html
│
├── backend
│   ├── matrix.h
│   ├── server.cpp
│   ├── httplib.h
│   └── json.hpp
│
├── Dockerfile
└── README.md

## ⚙️ How It Works

1.The user selects the required matrix dimensions.
2.The frontend dynamically creates the matrix input fields.
3.The user enters the matrix values.
4.The user selects the required matrix operation.
5.JavaScript collects the matrix values from the input fields.
6.The matrix data and selected operation are converted into JSON.
7.The JSON request is sent to the C++ backend.
8.The C++ server receives and processes the request.
9.The Matrix class performs the selected operation.
10.The calculated result is converted into JSON.
11.JavaScript receives and stores the result.
12.The result page is opened.
13.The result is displayed in mathematical matrix format.

## 🔄 Data Flow

Matrix Input
     │
     ▼
JavaScript
     │
     ▼
JSON Request
     │
     ▼
C++ Backend
     │
     ▼
Matrix Operations
     │
     ▼
JSON Response
     │
     ▼
JavaScript
     │
     ▼
Result Page


## 💻 Running Locally

Requirements

- C++ compiler
- Git
- Web browser

## Clone the Repository

- git clone https://github.com/KeerthiNehakshaya-1/matrix-operation-system.git

Navigate into the project:

- cd matrix-operation-system

## Compile the Backend

Navigate to the backend folder:

cd backend

On Linux:

g++ -std=c++17 -pthread server.cpp -o server

On Windows:

g++ -std=c++17 server.cpp -o server.exe -lws2_32


## Run the Server

On Linux:

./server

On Windows:

.\server.exe

The server runs on:

http://localhost:8080

Open the address in a web browser to access the application.

## 🐳 Docker Deployment

The project includes a Dockerfile for containerized deployment.

The Docker configuration:

- Uses Debian Linux as the base image.
- Installs the GNU C++ compiler.
- Copies the backend and frontend files into the container.
- Compiles the C++ backend.
- Starts the C++ server.
- Uses the port provided by the hosting platform.

Docker allows the application to run without requiring the user to install the C++ development environment locally.


## 🌐 Public Deployment

The application is publicly deployed using Render.

The deployment process uses:

- GitHub for source-code management
- Docker for containerization
- Render for cloud hosting

The C++ backend serves both the frontend files and the matrix calculation API.

The application can be accessed through the live Render URL provided at the top of this README.


## 🔒 Input Validation

The system validates the input before performing matrix operations.

Validation includes:

- Matrix dimensions
- Valid numerical matrix values
- Compatible dimensions for addition
- Compatible dimensions for subtraction
- Compatible dimensions for multiplication
- Square matrix requirement for determinant
- Square matrix requirement for inverse
- Singular matrix condition for inverse

Invalid operations are handled by returning an appropriate error message instead of producing an incorrect result.

## 🧪 Testing

All six supported operations have been tested on the deployed application:

Operation	       Status
Addition	       ✅ Passed
Subtraction	       ✅ Passed
Multiplication	   ✅ Passed
Transpose	       ✅ Passed
Determinant	       ✅ Passed
Inverse	           ✅ Passed

The application was tested both locally and through the publicly deployed version.

## 🎯 Project Objective

The objective of this project is to develop an interactive web-based matrix calculation system while demonstrating the integration of C++ programming with web technologies.

The project combines:

Object-oriented programming in C++
Matrix data structures
Mathematical algorithms
HTML and CSS frontend development
JavaScript programming
Client-server communication
JSON-based data exchange
HTTP-based API communication
Docker containerization
Cloud deployment
📚 Key Concepts Demonstrated
Classes and objects
Encapsulation
Two-dimensional arrays
Matrix algorithms
Dynamic HTML elements
JavaScript event handling
Fetch API
JSON data exchange
HTTP requests
C++ web server development
REST-style API design
Docker containerization
Cloud deployment
