/*  Copyright (C) 2014-2017 FastoGT. All right reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:

        * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the following disclaimer
    in the documentation and/or other materials provided with the
    distribution.
        * Neither the name of FastoGT. nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <common/protocols/json_rpc/json_rpc_response.h>

namespace common {
namespace protocols {
namespace json_rpc {

JsonRPCResponse::JsonRPCResponse() : id(), message(), error() {}

JsonRPCResponse JsonRPCResponse::MakeErrorInvalidJson() {
  JsonRPCError err;
  err.code = JSON_RPC_PARSE_ERROR;
  err.message = "Parse error";
  JsonRPCResponse resp;
  resp.id = null_json_rpc_id;
  resp.error = err;
  CHECK(resp.IsValid() && resp.IsError()) << "JsonRPCResponse should be valid.";
  return resp;
}

JsonRPCResponse JsonRPCResponse::MakeErrorInvalidRequest() {
  JsonRPCError err;
  err.code = JSON_RPC_INVALID_REQUEST;
  err.message = "Invalid Request";
  JsonRPCResponse resp;
  resp.id = null_json_rpc_id;
  resp.error = err;
  CHECK(resp.IsValid() && resp.IsError()) << "JsonRPCResponse should be valid.";
  return resp;
}

JsonRPCResponse JsonRPCResponse::MakeError(json_rpc_id jid, JsonRPCError error) {
  JsonRPCResponse resp;
  resp.id = jid;
  resp.error = error;
  CHECK(resp.IsValid() && resp.IsError()) << "JsonRPCResponse should be valid.";
  return resp;
}

JsonRPCResponse JsonRPCResponse::MakeMessage(json_rpc_id jid, JsonRPCMessage msg) {
  JsonRPCResponse resp;
  resp.id = jid;
  resp.message = msg;
  CHECK(resp.IsValid() && resp.IsMessage()) << "JsonRPCResponse should be valid.";
  return resp;
}

bool JsonRPCResponse::IsError() const {
  if (!id) {
    return false;
  }

  if (message) {
    return false;
  }

  if (error) {
    return true;
  }

  return false;
}

bool JsonRPCResponse::IsMessage() const {
  if (!id) {
    return false;
  }

  if (error) {
    return false;
  }

  if (message) {
    return true;
  }

  return false;
}

bool JsonRPCResponse::IsValid() const {
  if (!id) {
    return false;
  }

  if (error && message) {
    return false;
  }

  return true;
}

}  // namespace json_rpc
}  // namespace protocols
}  // namespace common
