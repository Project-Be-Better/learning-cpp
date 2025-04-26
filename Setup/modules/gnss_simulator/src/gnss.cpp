#include "gnss.h"

namespace gnss
{
    GNSS::GNSS() : lat_{0.0}, lon_{0.0} {}

    GNSS::GNSS(double lat, double lon) : lat_{lat}, lon_{lon} {}

    void GNSS::simulate()
    {
        lat_ += DELTA;
        lon_ += DELTA;
    }

    double GNSS::latitude() const noexcept
    {
        return lat_;
    }

    double GNSS::longitude() const noexcept
    {
        return lon_;
    }
}