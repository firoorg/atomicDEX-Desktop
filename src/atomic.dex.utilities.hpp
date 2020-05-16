#pragma once

//! PCH Headers
#include "atomic.dex.pch.hpp"

#include <QCryptographicHash>
#include <QString>

inline std::string
dex_sha256(const std::string& str)
{
    QString res = QString(QCryptographicHash::hash((str.c_str()),QCryptographicHash::Keccak_256).toHex());
    return res.toStdString();
}

inline void to_eth_checksum(std::string& address)
{
    address = address.substr(2);
    auto hex_str           = dex_sha256(address);
    auto final_eth_address = std::string("0x");

    for (std::string::size_type i = 0; i < address.size(); i++)
    {
        std::string actual(1, hex_str[i]);
        try
        {
            auto        value = std::stoi(actual, nullptr, 16);
            if (value >= 8)
            {
                final_eth_address += toupper(address[i]);
            } else {
                final_eth_address += address[i];
            }
        }
        catch (const std::invalid_argument& e)
        {
            final_eth_address += address[i];
        }
    }
    address = final_eth_address;
}

struct timed_waiter
{
    void
    interrupt()
    {
        auto l      = lock();
        interrupted = true;
        cv.notify_one();
    }

    template <class Rep, class Period>
    bool
    wait_for(std::chrono::duration<Rep, Period> how_long) const
    {
        auto l = lock();
        return cv.wait_for(l, how_long, [&] { return interrupted; });
    }

  private:
    std::unique_lock<std::mutex>
    lock() const
    {
        return std::unique_lock<std::mutex>(m, std::try_to_lock);
    }

    mutable std::mutex              m;
    mutable std::condition_variable cv;
    bool                            interrupted = false;
};


namespace atomic_dex::utils
{
    struct my_json_sax : nlohmann::json_sax<nlohmann::json>
    {
        bool
        null() override
        {
            return true;
        }

        bool
        boolean([[maybe_unused]] bool val) override
        {
            return true;
        }

        bool
        number_integer([[maybe_unused]] number_integer_t val) override
        {
            return true;
        };

        bool
        number_unsigned([[maybe_unused]] number_unsigned_t val) override
        {
            return true;
        };

        bool
        number_float([[maybe_unused]] number_float_t val, [[maybe_unused]] const string_t& s) override
        {
            this->float_as_string = s;
            return true;
        }

        bool
        string([[maybe_unused]] string_t& val) override
        {
            return true;
        }

        bool
        start_object([[maybe_unused]] std::size_t elements) override
        {
            return true;
        }

        bool
        key([[maybe_unused]] string_t& val) override
        {
            return true;
        }

        bool
        end_object() override
        {
            return true;
        }

        bool
        start_array([[maybe_unused]] std::size_t elements) override
        {
            return true;
        }

        bool
        end_array() override
        {
            return true;
        }

        bool
        parse_error(
            [[maybe_unused]] std::size_t position, [[maybe_unused]] const std::string& last_token,
            [[maybe_unused]] const nlohmann::detail::exception& ex) override
        {
            return false;
        };

        std::string float_as_string;
    };
} // namespace atomic_dex::utils