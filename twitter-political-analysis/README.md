# Twitter Political Analysis

This project analyzes Twitter data to determine the political tendencies of users based on their following of specific media outlets. The analysis is performed using various data structures and algorithms to provide insights into user behavior and influence within the Twitter network.

## Project Structure

```
twitter-political-analysis
├── src
│   ├── main.cpp                # Entry point of the application
│   ├── data
│   │   └── DataLoader.cpp      # Loads user and connection data from CSV files
│   ├── analysis
│   │   └── PoliticalAnalyzer.cpp # Analyzes political tendencies of users
│   ├── algorithms
│   │   └── Clustering.cpp       # Implements clustering algorithms for user graph
│   ├── structures
│   │   └── UserGraph.cpp        # Represents the Twitter user network as a directed graph
│   └── include
│       ├── DataLoader.h         # Header for DataLoader class
│       ├── PoliticalAnalyzer.h   # Header for PoliticalAnalyzer class
│       ├── Clustering.h          # Header for Clustering class
│       └── UserGraph.h           # Header for UserGraph class
├── data
│   └── sample_dataset.csv       # Sample dataset for testing the application
├── CMakeLists.txt              # CMake configuration file
└── README.md                   # Project documentation
```

## Setup Instructions

1. **Clone the repository**:
   ```
   git clone <repository-url>
   cd twitter-political-analysis
   ```

2. **Install dependencies**:
   Ensure you have CMake and a C++ compiler installed on your system.

3. **Build the project**:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```

## Usage Guidelines

1. **Run the application**:
   After building the project, you can run the application using:
   ```
   ./twitter-political-analysis
   ```

2. **Input Data**:
   The application expects a CSV file located in the `data` directory. Modify `sample_dataset.csv` as needed for testing.

3. **Analysis**:
   The application will load the dataset, analyze the political tendencies of users, and output the results to the console.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue for any suggestions or improvements.
