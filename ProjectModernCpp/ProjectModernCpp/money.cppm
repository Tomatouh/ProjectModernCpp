export module money;
import resource;
class Money : public Resource
{
private:
	uint8_t m_value;
public:
	Money();
	bool add(const uint8_t& value);
	bool subtract(const uint8_t& value);
	uint8_t getValue() const;

};
