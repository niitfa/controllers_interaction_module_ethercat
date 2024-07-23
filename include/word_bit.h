#ifndef WORDBIT_H
#define WORDBIT_H

class WordBit
{
public:
	static uint8_t Read(const int64_t* const data, uint8_t bit_position)
	{
		int64_t buff = *data;
		return (buff >> bit_position) & 0x01;
	}	
	static void Write(int64_t* const data, uint8_t bit_position, uint8_t bit_value)
	{
		if (bit_value)
			*data |= ((int64_t)1 << (bit_position));
		else
			*data &= ~((int64_t)1 << (bit_position));
	}
};

#endif
