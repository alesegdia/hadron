#pragma once

#include <algorithm>
#include <vector>

namespace hadron {


template <typename T>
void RemoveByValue( std::vector<T>& v, T value )
{
    v.erase( std::remove( v.begin(), v.end(), value ), v.end() );
}


}
