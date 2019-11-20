// based on
// Copyright (c) 2018 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/CppCon2018
//

#include "shared_state.hpp"
#include "websocket_session.hpp"

shared_state::
shared_state(std::function<std::shared_ptr<std::string const> (const void*)> websocketMessageHandler)
    : websocketMessageHandler(websocketMessageHandler)
{
}

std::shared_ptr<std::string const> shared_state::handleWebsocketMessage(const void * data)
{
    return websocketMessageHandler(data);
}
