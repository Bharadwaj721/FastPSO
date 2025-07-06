#include <bits/stdc++.h>
using namespace std;

// Global Constants
const int numParticles = 10;
const int lowerBound = 0;
const int upperBound = 10;
const double convergenceThreshold = 0.05;
const int c1 = 1, c2 = 1;

// Global Variables
double position[numParticles] = {0};
double velocity[numParticles] = {0};
double personalBest[numParticles] = {0};
double globalBest = 0;

// Fitness Function: Maximizing f(x) = -x^2 + 10x + 20
double fitness(double x) {
    return -(x * x) + 10 * x + 20;
}

// Initialization Function
void initializeParticles() {
    for (int i = 0; i < numParticles; i++) {
        double randFactor = (double)rand() / RAND_MAX;

        // Modified Initialization: Position initialized uniformly across blocks
        position[i] = i + (upperBound - lowerBound) * randFactor;

        // Modified Initialization: Small random initial velocities
        velocity[i] = randFactor;
    }
}

// Update Personal Bests
void updatePersonalBest() {
    for (int i = 0; i < numParticles; i++) {
        if (personalBest[i] == 0 || fitness(personalBest[i]) < fitness(position[i])) {
            personalBest[i] = position[i];
        }
    }
}

// Update Global Best
void updateGlobalBest() {
    for (int i = 0; i < numParticles; i++) {
        if (fitness(globalBest) < fitness(personalBest[i])) {
            globalBest = personalBest[i];
        }
    }
}

// Move a random particle directly to global best (forced exploitation)
void moveRandomParticleToGbest() {
    int randIndex = rand() % numParticles;
    personalBest[randIndex] = globalBest;
    position[randIndex] = globalBest;
}

// Update velocities and positions with selective position updates
void updateParticles() {
    for (int i = 0; i < numParticles; i++) {
        double r1 = (double)rand() / RAND_MAX;
        double r2 = (double)rand() / RAND_MAX;

        velocity[i] = velocity[i]
                      + c1 * r1 * (personalBest[i] - position[i])
                      + c2 * r2 * (globalBest - position[i]);

        // Modified Update: Only update if the new position is no worse
        if (fitness(position[i] + velocity[i]) > fitness(position[i])) {
            position[i] += velocity[i];
        }
    }
}

int main() {
    srand(time(0)); // Seed RNG

    initializeParticles();
    int iteration = 0;

    // Run until convergence near expected optimum (x ≈ 5 for this function)
    while (abs(globalBest - 5) > convergenceThreshold) {
        updatePersonalBest();
        updateGlobalBest();
        moveRandomParticleToGbest();
        updateParticles();

        cout << "Iteration " << iteration << " | Gbest: " << globalBest
             << " | Fitness: " << fitness(globalBest) << "\n";
        iteration++;
    }

    cout << "\nFinal Global Best: " << globalBest
         << " | Fitness: " << fitness(globalBest) << "\n";
    cout << "Total Iterations: " << iteration << "\n";

    return 0;
}
