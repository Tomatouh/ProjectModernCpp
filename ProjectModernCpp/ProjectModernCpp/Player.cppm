
export module Player;

import <string>;
import <map>;
import <vector>;
import <iostream>;

export enum class ResourceType { Wood, Stone, Clay, Glass, Papyrus, None };
using CostMap = std::map<ResourceType, int>;

export class Player {
public:
    explicit Player(std::string name) : name_(std::move(name)), coins_(7) {}

    const std::string& name() const noexcept { return name_; }
    int coins() const noexcept { return coins_; }

    void addCoins(int n) noexcept { coins_ += n; }
    bool spendCoins(int n) noexcept {
        if (n > coins_) return false;
        coins_ -= n;
        return true;
    }

    void addProducedResource(ResourceType r, int amount = 1) noexcept {
        production_[r] += amount;
    }

    int produced(ResourceType r) const noexcept {
        if (auto it = production_.find(r); it != production_.end())
            return it->second;
        return 0;
    }

    void showStatus(std::ostream& os = std::cout) const {
        os << "Player " << name_ << " | coins=" << coins_ << "\n";
        for (auto& [res, qty] : production_)
            os << "  - " << static_cast<int>(res) << " : " << qty << "\n";
    }

private:
    std::string name_;
    int coins_{ 0 };
    std::map<ResourceType, int> production_;
};

