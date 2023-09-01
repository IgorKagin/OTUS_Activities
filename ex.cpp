/////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <type_traits>
#include <list>
#include <tuple>

void Printer( const std::vector<uint8_t>& vector )
{
  for ( uint8_t i = 0; i < vector.size(); ++i )
  {
    if ( i != 0 )
      cout << ".";
    std::wcout << vector.at(i); 
  }
  cout << endl;
}

template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
void printIP(const T& x) 
{
  const auto countOfBytes = sizeof( T );
  uint8_t offset = 56;
  const uint8_t step_offset = 8;
  //std::vector<uint8_t> temp;  
  uint8_t temp;
  for ( uint8_t i = 0; i < countOfBytes; ++i )
  {
    if ( i != 0 )
      cout << ".";
    //temp.push_back( ( x >> offset ) & 0xFF );
    temp = ( x >> offset ) & 0xFF;
    std::wcout << temp;
    offset -= step_offset;
  }
  cout << endl;
  //Printer( temp );
}

template<typename T, std::enable_if_t<std::is_same_v<T,std::string>, bool> = true>
void printIP( const T& x ) 
{
  cout << x << endl;
}

template<template<typename, typename> typename T, typename Type, typename Allocator = std::allocator<Type>, 
                  std::enable_if_t<std::is_same_v<T<Type, Allocator>, std::vector<Type>> || std::is_same_v<T<Type, Allocator>, std::list<Type>>, bool> = true >
void printIP( const T<Type, Allocator>& container )
{
  //cout << "hi, container" << endl;

  for ( auto iter = std::begin( container ); iter != std::end( container ); ++iter )
  {
    if ( iter != std::begin( container ) )
      cout << ".";
    cout << *iter;
  }
  cout << endl;
}

//template<template<typename...> typename T, typename ...ValueTypes, 
//              std::enable_if_t<std::is_same_v<T<ValueTypes...>, std::tuple<ValueTypes...>>, bool> = true>
//void printIP( const T<ValueTypes...>& x )
//{
//  cout << "tuple" << endl;
//}
//template<template<typename...> typename T, typename ...ValueTypes,
//  std::enable_if_t<std::is_same_v<T<ValueTypes...>, std::tuple<ValueTypes...>> && std::is_same_v<std::tuple_element_t<0, T<ValueTypes...>>, std::tuple_element_t<1, T<ValueTypes...>>>, bool> = true>
//  void printIP( const T<ValueTypes...>& x )
//{
//  cout << "tuple" << endl;
//}


template< size_t N, typename ...ValueTypes>
struct is_all
{
  //assert( N > 0 );
  using myTuple = std::tuple<ValueTypes... >;
  static const bool value = std::is_same_v<std::tuple_element_t<0, myTuple>, std::tuple_element_t<1, myTuple>> && is_all<N - 2, ValueTypes...>::value;
};

template<typename ...ValueTypes>
struct is_all<0, ValueTypes...>
{
  static const bool value = true;
};

template<template<typename...> typename T, typename ...ValueTypes,
  std::enable_if_t<std::is_same_v<T<ValueTypes...>, std::tuple<ValueTypes...>> && is_all<std::tuple_size<T<ValueTypes...>>::value, ValueTypes...>::value, bool > = true >/*&& is_all<4, ValueTypes...>::value>*/
  void printIP( const T<ValueTypes...>& tuple )
{
  //static constexpr size_t k = 0;
  //constexpr const size_t size = std::tuple_size<T<ValueTypes...>>::value;

  ////static constexpr const std::vector<size_t> x = { 0,1,2,3 };
  //for ( size_t i = 0; i < size; ++i )
  //{
  //  //print_tuple< size, decltype( tuple )>( tuple );
  //}
  //cout <<  endl;
  cout << std::get<0>( tuple ) << ".";
  cout << std::get<1>( tuple ) << ".";
  cout << std::get<2>( tuple ) << ".";
  cout << std::get<3>( tuple ) << endl;
  cout << endl;
}


//std::tuple_element_t<std::tuple_size<T<ValueTypes...>>, T<ValueTypes...>>>
//std::tuple_element_t<1, T<ValueTypes...>>
//std::is_same_v<std::tuple_element_t<0, T<ValueTypes...>>, std::tuple_element_t<std::tuple_size<T<ValueTypes...>>::value-1, T<ValueTypes...>>>
int main( int argc, char const*argv[] )
{
  {
    printIP( int8_t{ -1 } ); // 255
    printIP( int16_t{ 0 } ); // 0.0
    printIP( int32_t{ 2130706433 } ); // 127.0.0.1
    printIP( int64_t{ 8875824491850138409 } ); // 123.45.67.89.101.112.131.41
    printIP( std::string{"Hello, World!"} ); // Hello, World!
    printIP( std::vector<int>{ 100, 200, 300, 400 } ); // 100.200.300.400
    printIP( std::list<short>{ 400, 300, 200, 100 } ); // 400.300.200.100 
    printIP( std::make_tuple( 123, 456, 789, 0 )); // 123.456.789.0 
    //auto check( is_all<std::tuple<int,int>(4,2),4>::value );
  }
}
