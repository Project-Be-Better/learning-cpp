#pragma once

/**
 * The GNSS module
 */
namespace gnss
{
    /**
     * Holds a coordinate and moves it by a fixed delta on each simulate() call
     */
    class GNSS
    {
    public:
        GNSS();                            // Constructs at (0,0)
        GNSS(double lat, double lon);      // Constructs at (lat, lon)
        ~GNSS() = default;                 // Defaulted Destructor
        void simulate();                   // Advance the position by a small fixed amount
        double latitude() const noexcept;  // Getter for current latitude
        double longitude() const noexcept; // Getter for current longitude

    private:
        double lat_;                            // current latitide
        double lon_;                            // current longitude
        static constexpr double DELTA = 0.0001; // Step size for simulate
    };
}