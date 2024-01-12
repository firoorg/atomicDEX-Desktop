/******************************************************************************
 * Copyright © 2013-2024 The Komodo Platform Developers.                      *
 *                                                                            *
 * See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at                  *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                                            *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * Komodo Platform software, including this file may be copied, modified,     *
 * propagated or distributed except according to the terms contained in the   *
 * LICENSE file                                                               *
 *                                                                            *
 * Removal or modification of this copyright notice is prohibited.            *
 *                                                                            *
 ******************************************************************************/

#pragma once

//! Dependencies Headers
#include <meta/sequence/list.hpp> ///< doom::meta::list

//! SDK Headers
#include "antara/gaming/event/quit.game.hpp"             ///< event::quit_game
#include "antara/gaming/event/start.game.hpp"            ///< event::start_game

namespace antara::gaming::event
{
    using events_list = doom::meta::list<quit_game, start_game>;
}