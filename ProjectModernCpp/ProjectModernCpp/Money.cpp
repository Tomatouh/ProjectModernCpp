#include "Money.h"
Money::Money()
{
	value = 0;
}
void Money::add1()
{
	value++;
}
void Money::add3()
{
	value+=3;
}
void Money::add6()
{
	value+=6;
}
uint8_t Money::getValue() const
{
	return value;
}
//test