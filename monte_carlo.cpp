#include <iostream>
#include <vector>
#include <cmath>
#include <random>

class MonteCarloSimulation {
public:
    MonteCarloSimulation(int numSimulations, double initialPrice, double drift, double volatility)
        : numSimulations_(numSimulations), initialPrice_(initialPrice), drift_(drift), volatility_(volatility) {}

    double simulate() {

        std::default_random_engine generator;
        std::normal_distribution<double> distribution(0.0, 1.0);

        std::vector<double> prices;
        prices.reserve(numSimulations_);

        for (int i = 0; i < numSimulations_; i++) {
            double time = 1.0;
            double randNorm = distribution(generator);
            double price = initialPrice_ * std::exp(drift_ * time + std::sqrt(volatility_ * time) * randNorm);
            prices.push_back(price);
        }

        double meanPrice = 0.0;
        for (double price : prices) {
            meanPrice += price;
        }
        meanPrice /= numSimulations_;

        double variance = 0.0;
        for (double price : prices) {
            variance += (price - meanPrice) * (price - meanPrice);
        }
        variance /= numSimulations_;
        double stdDevPrice = std::sqrt(variance);

        std::cout << "Standard Deviation: " << stdDevPrice << std::endl;

        return meanPrice + stdDevPrice;
    }

private:
    int numSimulations_;
    double initialPrice_;
    double drift_;
    double volatility_;
};

int main() {
    MonteCarloSimulation simulation(1000, 100.0, 0.01, 0.1);
    double result = simulation.simulate();
    std::cout << "Mean + Std Dev Price: " << result << std::endl;
    return 0;
}
