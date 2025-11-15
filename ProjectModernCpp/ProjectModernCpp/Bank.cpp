module bank;

Bank::Bank()
{
	m_coins[0] = 12;
	m_coins[1] = 6;
	m_coins[3] = 7;
}
void Bank::pay1()
{
	m_coins[0]++;
}
void Bank::pay3()
{
	m_coins[1]++;
}
void Bank::pay6()
{
	m_coins[2]++;
}
bool Bank::take(uint8_t value)
{

}