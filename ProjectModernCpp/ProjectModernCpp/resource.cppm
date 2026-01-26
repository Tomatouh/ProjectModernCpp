export module resource;
import <cstdint>;
export class Resource
{
public:
	virtual void add() = 0;
	virtual uint8_t getValue() = 0;
};