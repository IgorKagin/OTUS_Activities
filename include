#ifndef IP_FILTER_H
#define IP_FILTER_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>

using std::cout;
using std::endl;
using std::cin;
using std::fstream;
using std::string;

class CException:
  public std::exception
{
public:
  CException() = default;
  CException( const CException & ) = default;

  CException( CException && ) = delete;
  CException& operator= ( const CException & ) = delete;
  CException& operator= ( CException && ) = delete;

  explicit CException( const char* const );
  const char *what() const noexcept;

private:
  const char *const message{ "Error" };
};

struct EmptyVector :CException
{
  EmptyVector();
};


class IPHandler final
{
public:
  IPHandler( const std::vector<std::vector<std::string>>& ipPool );
  IPHandler(const IPHandler &) = delete;
  IPHandler& operator=( const IPHandler & ) = delete;
  IPHandler& operator=( IPHandler &&) = delete;
  IPHandler( IPHandler && ) = delete;

  // Сортировка и вывод IP адресов
  void SortIP();

  // Вывод адреса, начинающегося с введённого пользователем/содержащий значения
  void PrintIp( const unsigned& arg, const bool& any ) const noexcept;
 
  // Вывод адресов, начинающихся с введенных пользователем двух составляющих
  void PrintIp( const unsigned& arg1, const unsigned& arg2 ) const noexcept;

  // Вывод адресов, начинающихся с введенных пользователем трёх составляющих
  void PrintIp( const unsigned& arg1, const unsigned& arg2, const unsigned& arg3 ) const noexcept;

  // Вывод адресов, равных введённому пользователем
  void PrintIp( const unsigned& arg, const unsigned& arg1, const unsigned& arg2, const unsigned& arg3 ) const noexcept;
  
protected:
  // Вывод
  void Printer( const std::vector<unsigned>& vector ) const noexcept;

  // Получить IP адрес в целочисленном типе
  unsigned GetIp( const std::vector<std::string>& splitted ) const noexcept;

  // Заполнить вектор векторов целочисленного представления IP адресов
  // Вывести отсортированные IP адреса
  void Writer() noexcept;

private:
  std::vector<std::vector<unsigned>> m_unsignedPool;  //!  Вектор векторов целочисленного представления IP адресов
  std::vector<std::vector<std::string>> m_ipPool;     //!  Вектор векторов строк IP адресов
  std::vector<unsigned> m_pool;                       //!  Вектор целочисленного представления IP адресов
};

#endif // IP_FILTER_H
