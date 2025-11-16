export module peon;

export class peon final {
private:
	int const static startPos = 0;
	int const static winPosP2 = -9;
	int const static winPosP1 = 9;
    int pos = startPos;

    void incrementPos() noexcept { ++pos; }
    void decrementPos() noexcept { --pos; }

public:
    peon() = default;
    explicit peon(int initialPos) noexcept : pos(initialPos) {}

    [[nodiscard]] int getPos() const noexcept { return pos; }
    void setPos(int newPos) noexcept { pos = newPos; }

    void move(int steps, bool player) noexcept(false);
    void checkZone() noexcept;
};