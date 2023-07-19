#include "ip_filter.h"

// Разделить IP адрес на составные части
std::vector<std::string> split( const std::string& str, const char d )
{
  std::vector<std::string> splittedIp;
  std::string::size_type start = 0;
  std::string::size_type stop = str.find_first_of( d );

  while ( stop != std::string::npos )
  {
    splittedIp.push_back( str.substr( start, stop - start ) );

    start = stop + 1;
    stop = str.find_first_of( d, start );
  }
  splittedIp.push_back( str.substr( start ) );

  return splittedIp;
}


int main( int, char ** )
{
  try
  {
    std::vector<std::vector<std::string>> ipPool;   //!  Вектор векторов строк IP адресов
    string row;

    while ( getline( std::cin, row ) )
    {
      const std::vector<std::string> temp = split( row, '\t' );   //!  Временный вектор для вычисления
      ipPool.emplace_back( std::move( split( temp.at( 0 ), '.' ) ) );
    }

    {
      //std::vector<std::vector<std::string>> ipPool;
      IPHandler handler{ ipPool };
      handler.SortIP();
      // Вывод IP адресов, начинающихся с 1
      {
        const unsigned firstPart = { 1 };
        const bool any = false;
        handler.PrintIp( firstPart, any );
      }

      // Вывод IP адресов, начинающихся с 46 и 70
      {
        const unsigned firstPart = { 46 };
        const unsigned secondPart = { 70 };
        handler.PrintIp( firstPart, secondPart );
      }

      //  Вывод IP адресов, содержащих 46 в любом месте
      {
        const unsigned part = { 46 };
        const bool any = true;
        handler.PrintIp( part, any );
      }
    }
  }
  catch ( const CException& e )
  {
    std::cerr << e.what() << endl;
  }
  catch ( ... )
  {
    std::cerr << "Unknown error" << endl;
  }

  return 0;
}
