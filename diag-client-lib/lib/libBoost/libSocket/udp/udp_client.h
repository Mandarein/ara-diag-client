/* MANDAREIN Diagnostic Client library
 * Copyright (C) 2022  Avijit Dey
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef UDP_H
#define UDP_H

// includes
#include "udp_types.h"

namespace libBoost {
namespace libSocket {
namespace udp {

using UdpSocket         = boost::asio::ip::udp;
using UdpIpAddress      = boost::asio::ip::address;
using UdpErrorCodeType  = boost::system::error_code;

/*
 @ Class Name        : Create Udp Socket
 @ Class Description : Class used to create a udp socket for handling transmission
                       and reception of udp message from driver
*/
class createUdpSocket {
public:
  // Udp function template used for reception
  using UdpHandlerRead = std::function<void(UdpMessagePtr)>;

  // Port Type
  enum class PortType : std::uint8_t {
      kUdp_Broadcast = 0,
      kUdp_Unicast
  };
public:  
  // ctor
  createUdpSocket(
    Boost_String& local_ip_address, 
    uint16_t local_port_num, 
    PortType port_type, 
    UdpHandlerRead udp_handler_read);
  
  // dtor
  virtual ~createUdpSocket();
  
  // Function to Open the socket
  bool Open();
  
  // Transmit
  bool Transmit(UdpMessageConstPtr udp_message);
  
  // Function to destroy the socket
  bool Destroy();
private:
  // local Ip address
  Boost_String local_ip_address_;
  
  // local port number
  uint16_t local_port_num_;
   
  // udp socket
  std::unique_ptr<UdpSocket::socket> udp_socket_;
  
  // end points
  UdpSocket::endpoint remote_endpoint_;
  
  // port type - broadcast / unicast
  PortType port_type_;
  
  // Handler invoked during read operation
  UdpHandlerRead udp_handler_read_;
  
  // Rxbuffer
  uint8_t rxbuffer_[kDoipUdpResSize];

  // boost io context 
  boost::asio::io_context io_context_;
private:
  // function to handle read
  void HandleMessage(const UdpErrorCodeType &error, std::size_t bytes_recvd);
};

} // udp
} // libSocket
} // libBoost

#endif // UDP_H
