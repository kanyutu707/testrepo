#include <iostream>
#include <vector>
#include <cmath>
#include <random>

class StockPriceModel {
public:
    StockPriceModel(double initialPrice, double drift, double volatility)
        : initialPrice_(initialPrice), drift_(drift), volatility_(volatility) {}

    double priceAtTime(double time) {

        static std::default_random_engine generator;
        static std::normal_distribution<double> distribution(0.0, 1.0);

        double randomShock = distribution(generator);
        double price = initialPrice_ * std::exp(drift_ * time + std::sqrt(volatility_ * time) * randomShock);
        return price;
    }

private:
    double initialPrice_;
    double drift_;
    double volatility_;
};

int main() {
    StockPriceModel model(100.0, 0.01, 0.1);
    for (int i = 0; i < 10; i++) {
        double time = i;
        double price = model.priceAtTime(time);
        std::cout << "Time: " << time << ", Price: " << price << std::endl;
    }
    return 0;
}
