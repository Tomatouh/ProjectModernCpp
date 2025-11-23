export module peon;

export class Peon final {
private:
	int const static startPos = 0;

    int pos = startPos;


public:
    void incrementPos() noexcept { ++pos; }
    void decrementPos() noexcept { --pos; }
    Peon() = default;
    explicit Peon(int initialPos) noexcept : pos(initialPos) {}

    [[nodiscard]] int getPos() const noexcept { return pos; }
    void setPos(int newPos) noexcept { pos = newPos; }


};