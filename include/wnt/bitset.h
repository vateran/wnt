#pragma once
#include <array>
#include <bitset>
namespace wnt
{

template <size_t BITS>
class bitset : public std::bitset<BITS>
{
private:
    typedef unsigned int BASE_TYPE;
    enum
    {
        CHUNK_SIZE = sizeof(BASE_TYPE) * 8,
        CHUNK_NUM = ((BITS - 1) / CHUNK_SIZE) + 1,
    };

public:
    std::array<BASE_TYPE, CHUNK_NUM> to_ulong_array() const
    {
        std::array<BASE_TYPE, CHUNK_NUM> ret = {0,};
        
		for (size_t pos=0;pos<BITS;++pos)
        {
			if (this->test(pos))
            {
                size_t chunk_index = pos / CHUNK_SIZE;
                size_t in_pos = pos % CHUNK_SIZE;
                BASE_TYPE bit_value = 1 << in_pos;

                ret[chunk_index] |= bit_value;
            }
        }

        return ret;
    }

};

}

