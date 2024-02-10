#include <iostream>
#include <string>
#include <unordered_map>


const int MIN_SENIORS = 10;
const int MAX_SENIORS = 36;
const int MIN_CARERS = 2;
const int ADDITIONAL_CARERS_THRESHOLD = 24;


std::unordered_map<std::pair<int, int>, std::unordered_map<std::string, double>> costRanges = {
    {{12, 16}, {{"coach", 150}, {"meal", 14.00}, {"ticket", 21.00}}},
    {{17, 26}, {{"coach", 190}, {"meal", 13.50}, {"ticket", 20.00}}},
    {{27, 39}, {{"coach", 225}, {"meal", 13.00}, {"ticket", 0.00}}}  
};

// Task 1 - Work out the total cost of the outing
std::pair<double, double> calculateCost(int numSeniors) {
    if (numSeniors < MIN_SENIORS || numSeniors > MAX_SENIORS) {
        std::cout << "Invalid number of seniors. The outing cannot proceed." << std::endl;
        return std::make_pair(-1, -1);
    }

    int carersNeeded = MIN_CARERS + (numSeniors > ADDITIONAL_CARERS_THRESHOLD ? 1 : 0);

    std::unordered_map<std::string, double> costRange;
    for (const auto& entry : costRanges) {
        if (entry.first.first <= numSeniors && numSeniors <= entry.first.second) {
            costRange = entry.second;
            break;
        }
    }

    double totalCost = costRange["coach"] + (carersNeeded * costRanges[{12, 16}]["coach"]);
    double costPerPerson = totalCost / (numSeniors + carersNeeded);

    return std::make_pair(totalCost, costPerPerson);
}

// Task 2 - Record who is going on the outing and how much has been paid
double recordOutingParticipants(int numSeniors, double totalCost, double costPerPerson) {
    std::unordered_map<std::string, double> participants;

    for (int i = 0; i < numSeniors + MIN_CARERS; ++i) {
        std::string name;
        double amountPaid;

        std::cout << "Enter the name of participant " << i + 1 << ": ";
        std::cin >> name;
        std::cout << "Enter the amount paid by " << name << ": $";
        std::cin >> amountPaid;

        participants[name] = amountPaid;
    }

    int extraPeople;
    std::cout << "Enter the number of extra people (if any): ";
    std::cin >> extraPeople;

    for (int i = 0; i < extraPeople; ++i) {
        std::string name;
        double amountPaid;

        std::cout << "Enter the name of extra participant " << i + 1 << ": ";
        std::cin >> name;
        std::cout << "Enter the amount paid by " << name << ": $";
        std::cin >> amountPaid;

        participants[name] = amountPaid;
    }

    double totalMoneyCollected = 0;
    for (const auto& entry : participants) {
        totalMoneyCollected += entry.second;
    }

    std::cout << "\nList of people on the outing:" << std::endl;
    for (const auto& entry : participants) {
        std::cout << entry.first << ": $" << entry.second << std::endl;
    }

    return totalMoneyCollected;
}

// Task 3 - Identify the break-even point or profit
void calculateProfitOrBreakEven(double estimatedCost, double totalMoneyCollected) {
    if (totalMoneyCollected >= estimatedCost) {
        double profit = totalMoneyCollected - estimatedCost;
        std::cout << "\nThe outing made a profit of $" << profit << "." << std::endl;
    } else {
        double loss = estimatedCost - totalMoneyCollected;
        std::cout << "\nThe outing broke even. There was a loss of $" << loss << "." << std::endl;
    }
}


int main() {
    int numSeniors;

    std::cout << "Enter the number of senior citizens interested in the outing: ";
    std::cin >> numSeniors;

    auto costResults = calculateCost(numSeniors);
    if (costResults.first != -1) {
        double totalCost = costResults.first;
        double costPerPerson = costResults.second;

        std::cout << "\nTotal cost for the outing: $" << totalCost << std::endl;
        std::cout << "Cost per person: $" << costPerPerson << std::endl;

        double totalMoneyCollected = recordOutingParticipants(numSeniors, totalCost, costPerPerson);

        calculateProfitOrBreakEven(totalCost, totalMoneyCollected);
    }

    return 0;
}
