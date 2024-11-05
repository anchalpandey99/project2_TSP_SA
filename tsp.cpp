#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Define number of cities
const int city = 5;

// Distance matrix for Euclidean distances (symmetric matrix)
double dist[city][city] = {
    {0, 15, 25, 10, 25},
    {10, 0, 35, 25, 30},
    {15, 35, 0, 30, 20},
    {20, 25, 30, 0, 15},
    {25, 30, 20, 15, 0}
};

// Function to calculate total tour distance
double calculateDistance(const vector<int>& tour) {
    double totalDist = 0.0;
    for (int i = 0; i < city - 1; ++i) {
        totalDist += dist[tour[i]][tour[i + 1]];
    }
    totalDist += dist[tour[city - 1]][tour[0]];  // Returning to the starting city
    return totalDist;
}

// Generate a random number between 0 and 1
double random01() {
    return (double) rand() / RAND_MAX;
}

// Simulated Annealing algorithm for TSP
vector<int> simulatedAnnealing(double initialTemp, double finalTemp, double alpha, int maxIter) {
    vector<int> currentTour(city), bestTour;
    for (int i = 0; i < city; ++i) currentTour[i] = i; // Initialize tour as (0, 1, 2, ..., N-1)
    
    double currentDist = calculateDistance(currentTour);
    bestTour = currentTour;
    double bestDist = currentDist;
    
    double T = initialTemp;
    
    srand(time(0)); // Seed random number generator
    
    for (int iter = 0; iter < maxIter && T > finalTemp; ++iter) {
        // Generate a neighbor solution by swapping two cities
        int i = rand() % city;
        int j = rand() % city;
        swap(currentTour[i], currentTour[j]);
        
        // Calculate the distance for the new tour
        double newDist = calculateDistance(currentTour);
        
        // Accept the new solution if it's better or based on a probability
        if (newDist < currentDist || random01() < exp((currentDist - newDist) / T)) {
            currentDist = newDist;
            if (newDist < bestDist) {
                bestTour = currentTour;
                bestDist = newDist;
            }
        } else {
            swap(currentTour[i], currentTour[j]); // Revert swap if not accepted
        }
        
        // Reduce the temperature according to the cooling schedule
        T *= alpha;
    }
    
    return bestTour;
}

int main() {
    // Parameters for Simulated Annealing
    double initialTemp = 10000;   // Starting temperature
    double finalTemp = 1e-5;      // Ending temperature
    double alpha = 0.995;         // Cooling rate
    int maxIter = 10000;          // Maximum number of iterations
    
    // Execute Simulated Annealing to find the optimal tour
    vector<int> bestTour = simulatedAnnealing(initialTemp, finalTemp, alpha, maxIter);
    double bestDist = calculateDistance(bestTour);
    
    // Output the results
    cout << "Optimal Tour: ";
    for (int city : bestTour) {
        cout << city << " ";
    }
    cout << endl;
    cout << "Minimum Distance: " << bestDist << endl;
    
    return 0;
}