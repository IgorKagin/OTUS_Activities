#include "ip_filter.h"

CException::CException( const char* const  message ) :
  message{ message }
{
}

const char *CException::what() const noexcept
{
  return message;
} 

EmptyVector::EmptyVector() :
  CException{ "Vector is empty" }
{
}


IPHandler::IPHandler( const std::vector<std::vector<std::string>>& ipPool ): m_ipPool( std::move(ipPool) )
{};

// Сортировка и вывод IP адресов
void IPHandler::SortIP()
{
  // Проверка на пустой вектор
  if ( m_ipPool.empty() )
  {
    throw EmptyVector();
  }

  //  Заполнение вектора целочисленного представления IP адресов
  for ( const auto& vector : m_ipPool )
  {
    m_pool.push_back( GetIp( vector ) );
  }

  std::sort( m_pool.begin(), m_pool.end(), std::greater<unsigned>() );

  Writer();
}


// Вывод адреса, начинающегося с введённого пользователем/содержащий значения
void IPHandler::PrintIp( const unsigned& arg, const bool& any ) const noexcept 
{
  // Проверка на пустой вектор
  if ( m_unsignedPool.empty() )
  {
    throw EmptyVector();
  }

  cout << "-----IP-----" << endl;
  for ( const auto& vector : m_unsignedPool )
  {
    if ( any )
    {
      for ( const auto& el : vector )
      {
        if ( arg == el )
        {
          Printer( vector );
          break;
        }
      }
    }
    else
    {
      if ( vector.at( 0 ) == arg )
      {
        Printer( vector );
      }
    }
  }
}

// Вывод адресов, начинающихся с введенных пользователем двух составляющих
void IPHandler::PrintIp( const unsigned& arg1, const unsigned& arg2 ) const noexcept
{
  // Проверка на пустой вектор
  if ( m_unsignedPool.empty() )
  {
    throw EmptyVector();
  }

  cout << "-----IP-----" << endl;
  for ( const auto& vector : m_unsignedPool )
  {
    if ( vector.at( 0 ) == arg1 & vector.at( 1 ) == arg2 )
    {
      Printer( vector );
    }
  }
}

// Вывод адресов, начинающихся с введенных пользователем трёх составляющих
void IPHandler::PrintIp( const unsigned& arg1, const unsigned& arg2, const unsigned& arg3 ) const noexcept
{
  // Проверка на пустой вектор
  if ( m_unsignedPool.empty() )
  {
    throw EmptyVector();
  }

  cout << "-----IP-----" << endl;
  for ( const auto& vector : m_unsignedPool )
  {
    if ( vector.at( 0 ) == arg1 & vector.at( 1 ) == arg2 & vector.at( 2 ) == arg3 )
    {
      Printer( vector );
    }
  }
}

// Вывод адресов, равных введённому пользователем
void IPHandler::PrintIp( const unsigned& arg, const unsigned& arg1, const unsigned& arg2, const unsigned& arg3 ) const noexcept
{
  // Проверка на пустой вектор
  if ( m_unsignedPool.empty() )
  {
    throw EmptyVector();
  }

  cout << "-----IP-----" << endl;
  for ( const auto& vector : m_unsignedPool )
  {
    if ( vector.at( 0 ) == arg & vector.at( 1 ) == arg1 & vector.at( 2 ) == arg2 & vector.at( 3 ) == arg3 )
    {
      Printer( vector );
    }
  }
}

// Вывод
void IPHandler::Printer( const std::vector<unsigned>& vector ) const noexcept
{
  cout << vector.at( 0 ) << "." << vector.at( 1 ) << "." << vector.at( 2 ) << "."
    << vector.at( 3 ) << endl;
}

// Получить IP адрес в целочисленном типе
unsigned IPHandler::GetIp( const std::vector<std::string>& splitted ) const noexcept
{
  const unsigned part_4 = std::stoi( splitted[ 0 ] );
  const unsigned part_3 = std::stoi( splitted[ 1 ] );
  const unsigned part_2 = std::stoi( splitted[ 2 ] );
  const unsigned part_1 = std::stoi( splitted[ 3 ] );

  return part_4 << 24 | part_3 << 16 | part_2 << 8 | part_1;
}

// Заполнить вектор векторов целочисленного представления IP адресов
  // Вывести отсортированные IP адреса
void IPHandler::Writer() noexcept
{
  unsigned part_1{};
  unsigned part_2{};
  unsigned part_3{};
  unsigned part_4{};

  cout << "-----Sorted IP-----" << endl;

  for ( const auto& el : m_pool )
  {
    part_1 = ( ( el >> 24 ) & 0xFF );
    part_2 = ( ( el >> 16 ) & 0xFF );
    part_3 = ( ( el >> 8 ) & 0xFF );
    part_4 = ( el & 0xFF );

    const std::vector<unsigned> temp{ part_1 ,part_2 ,part_3 ,part_4 };
    Printer( temp );

    m_unsignedPool.emplace_back( std::move( temp ) );
  }
}
