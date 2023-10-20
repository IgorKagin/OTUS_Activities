#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <bitset>
#include <map>

struct Token{};
struct GEO{};
//namespace GEO
//{
//
//}
namespace IoTDev 
{
  class Radio1
  {
    /*
    */
    std::vector<Token> m_token;//std::vector<Radio2>
    std::vector<IoT> m_iots;//
  public:
    
    void connect()
    {

    }

    void disconnect()
    {

    }

    std::vector<Token> exchange( GEO &)
    {
      return m_token;
    }
  };

  class Radio2
  {
    /*
    */
    //std::vector<IoT> m_iots;
  public:
    void propogate( Token& )
    {

    }

    void process( Token& )
    {

    }
  };

  class Sensor
  {
    Token input;
  public:
    Token read()
    {
      return input;
    }
  };

  class Actuator
  {
    Token output;
  public:
    void write( Token&& arg )
    {
      output = arg;
    }
  };

  class IoT
  {
    GEO geo; //geo::Geo
    std::unique_ptr<Actuator> m_actuator;
    std::unique_ptr<Sensor>   m_sensor;
    std::unique_ptr<Radio1>   m_radio1;
    //std::vector<Token>      m_listData;
  public:
    IoT( std::unique_ptr<Radio1>& radio1):m_radio1(std::move( radio1 ))
    {
      m_sensor   = std::make_unique<Sensor>();
      m_actuator = std::make_unique<Actuator>();
    }

    void sync()
    {
      /*
      connect()
      disconnect()
      m_listData = m_radio1.exchange(geo)
      if(m_listData != empty)
          IoT::propogate(m_sensor)?
      */
      //
    }

    void propogate( Sensor&& )
    {

    }

    void process( Token&& )
    {

    }
  };
}



void main()
{
  {
   // Посл-ть вызовов:
  /*
  Radio1 radio{};

  */
   // IoT::sync(),
   // IoT::propogate()?
    using namespace IoTDev;
    std::unique_ptr<Radio1> radio1 = std::make_unique<Radio1>();
    IoT iot( radio1 );
    iot.sync();
   
  }
}
