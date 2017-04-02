#pragma once

#include <algorithm>

namespace hadron {


namespace util
{

template <typename T>
void remove_by_value( std::vector<T>& v, T value )
{
    v.erase( std::remove( v.begin(), v.end(), value ), v.end() );
}


}

}
