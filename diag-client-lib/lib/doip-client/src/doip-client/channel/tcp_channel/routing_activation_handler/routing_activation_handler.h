/* Diagnostic Client library
* Copyright (C) 2024  Avijit Dey
*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef DOIP_CLIENT_CHANNEL_TCP_CHANNEL_ROUTING_ACTIVATION_HANDLER_ROUTING_ACTIVATION_HANDLER_H_
#define DOIP_CLIENT_CHANNEL_TCP_CHANNEL_ROUTING_ACTIVATION_HANDLER_ROUTING_ACTIVATION_HANDLER_H_

#include <memory>

#include "doip-client/message/doip_message.h"
#include "doip-client/sockets/tcp_socket_handler.h"
#include "uds_transport-layer-api/protocol_mgr.h"
#include "uds_transport-layer-api/uds_message.h"

namespace doip_client {
namespace channel {
namespace tcp_channel {
// Forward declaration
class DoipTcpChannel;

namespace routing_activation_handler {
/**
 * @brief       Class used as a handler to process routing activation messages
 */
class RoutingActivationHandler final {
 public:
  /**
  * @brief  Type alias for Tcp message pointer
  */
  using TcpMessagePtr = sockets::TcpSocketHandler::MessagePtr;

  /**
  * @brief  Type alias for Tcp message
  */
  using TcpMessage = sockets::TcpSocketHandler::Message;

  /**
 * @brief  Type alias for Doip message
 */
  using DoipMessage = message::DoipMessage;

 public:
  /**
  * @brief         Constructs an instance of RoutingActivationHandler
  * @param[in]     tcp_socket_handler
  *                The reference to socket handler
  */
  explicit RoutingActivationHandler(sockets::TcpSocketHandler &tcp_socket_handler);

  /**
  * @brief         Destruct an instance of RoutingActivationHandler
  */
  ~RoutingActivationHandler();

  /**
  * @brief        Function to start the handler
  */
  void Start() const;

  /**
  * @brief        Function to stop the handler
  * @details      This will reset all the internal handler back to default state
  */
  void Stop() const;

  /**
  * @brief        Function to reset the handler
  * @details      This will reset all the internal handler back to default state
  */
  void Reset() const;

  /**
  * @brief       Function to process received routing activation response
  * @param[in]   doip_payload
  *              The doip message received
  */
  void ProcessDoIPRoutingActivationResponse(DoipMessage &doip_payload) const noexcept;

  /**
  * @brief       Function to handle sending of routing activation request
  * @param[in]   routing_activation_request
  *              The routing activation request
  * @return      Transmission result
  */
  auto HandleRoutingActivationRequest(
      uds_transport::UdsMessageConstPtr routing_activation_request) noexcept
      -> uds_transport::UdsTransportProtocolMgr::ConnectionResult;

  /**
  * @brief       Check if routing activation is active for this handler
  * @return      True if activated, otherwise False
  */
  auto IsRoutingActivated() noexcept -> bool;

 private:
  /**
  * @brief       Function to send routing activation request
  * @param[in]   routing_activation_request
  *              The routing activation request
  * @return      Transmission result
  */
  auto SendRoutingActivationRequest(uds_transport::UdsMessageConstPtr routing_activation_request)
      const noexcept -> uds_transport::UdsTransportProtocolMgr::TransmissionResult;

 private:
  /**
  * @brief  Forward declaration Handler implementation
  */
  class RoutingActivationHandlerImpl;

  /**
  * @brief  Stores the Handler implementation
  */
  std::unique_ptr<RoutingActivationHandlerImpl> handler_impl_;
};

}  // namespace routing_activation_handler
}  // namespace tcp_channel
}  // namespace channel
}  // namespace doip_client
#endif  //DOIP_CLIENT_CHANNEL_TCP_CHANNEL_ROUTING_ACTIVATION_HANDLER_ROUTING_ACTIVATION_HANDLER_H_