//   Copyright: Copyright (C) 2005, Jan Ringos, http://Tringi.Mx-3.cz
//   Version: 1.1
//
//  Copyright (c) 2014 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/config.hpp>

#if defined(HPX_HAVE_UINT128)
#include <hpx/hpx_fwd.hpp>
#include <hpx/util/numerics/uint128.hpp>

#include <memory>
#include <cmath>
#include <algorithm>

#include <hpx/util/portable_binary_iarchive.hpp>
#include <hpx/util/portable_binary_oarchive.hpp>

#include <boost/serialization/serialization.hpp>

// IMPLEMENTATION

namespace hpx { namespace util { namespace numerics
{
    const char * uint128::toString (unsigned int radix) const throw () {
        if (!*this) return "0";
        if (radix < 2 || radix > 37) return "(invalid radix)";

        static char sz [256];
        memset (sz, 0, 256);

        uint128 r;
        uint128 ii = *this;
        int i = 255;

        while (!!ii && i) {
            ii = ii.div (radix, r);
            sz [--i] = r.toUint () + ((r.toUint () > 9) ? 'A' - 10 : '0');
        };

        return &sz [i];
    };

    uint128::uint128 (const char * sz) throw ()
        : lo (0u), hi (0u) {

        if (!sz) return;
        if (!sz [0]) return;

        unsigned int radix = 10;
        unsigned int i = 0;
        bool minus = false;

        if (sz [i] == '-') {
            ++i;
            minus = true;
        };

        if (sz [i] == '0') {
            radix = 8;
            ++i;
            if (sz [i] == 'x') {
                radix = 16;
                ++i;
            };
        };

        for (; i < strlen (sz); ++i) {
            unsigned int n = 0;
            if (sz [i] >= '0' && sz [i] <= (std::min)(('0' + (int)radix), (int)'9'))
                n = sz [i] - '0';
            else if (sz [i] >= 'a' && sz [i] <= 'a' + (int) radix - 10)
                n = sz [i] - 'a' + 10;
            else if (sz [i] >= 'A' && sz [i] <= 'A' + (int) radix - 10)
                n = sz [i] - 'A' + 10;
            else
                break;

            (*this) *= radix;
            (*this) += n;
        };

        if (minus)
            *this = 0u - *this;

        return;
    };

    uint128::uint128 (const float a) throw ()
        : lo ((unsigned __int64) fmodf (a, 18446744073709551616.0f)),
          hi ((unsigned __int64) (a / 18446744073709551616.0f)) {};

    uint128::uint128 (const double & a) throw ()
        : lo ((unsigned __int64) fmod (a, 18446744073709551616.0)),
          hi ((unsigned __int64) (a / 18446744073709551616.0)) {};

    uint128::uint128 (const long double & a) throw ()
        : lo ((unsigned __int64) fmodl (a, 18446744073709551616.0l)),
          hi ((unsigned __int64) (a / 18446744073709551616.0l)) {};

    float uint128::toFloat () const throw () {
        return (float) this->hi * 18446744073709551616.0f
             + (float) this->lo;
    };

    double uint128::toDouble () const throw () {
        return (double) this->hi * 18446744073709551616.0
             + (double) this->lo;
    };

    long double uint128::toLongDouble () const throw () {
        return (long double) this->hi * 18446744073709551616.0l
             + (long double) this->lo;
    };

    uint128 uint128::operator - () const throw () {
        if (!this->hi && !this->lo)
            // number is 0, just return 0
            return *this;

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4146)
#endif
        // non 0 number
        return uint128 (-this->lo, ~this->hi);
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
    };

    uint128 uint128::operator ~ () const throw () {
        return uint128 (~this->lo, ~this->hi);
    };

    uint128 & uint128::operator ++ () {
        ++this->lo;
        if (!this->lo)
            ++this->hi;

        return *this;
    };

    uint128 & uint128::operator -- () {
        if (!this->lo)
            --this->hi;
        --this->lo;

        return *this;
    };

    uint128 uint128::operator ++ (int) {
        uint128 b = *this;
        ++ *this;

        return b;
    };

    uint128 uint128::operator -- (int) {
        uint128 b = *this;
        -- *this;

        return b;
    };

    uint128 & uint128::operator += (const uint128 & b) throw () {
        unsigned __int64 old_lo = this->lo;

        this->lo += b.lo;
        this->hi += b.hi + (this->lo < old_lo);

        return *this;
    };

    uint128 & uint128::operator *= (const uint128 & b) throw () {
        if (!b)
            return *this = 0u;
        if (b == 1u)
            return *this;

        uint128 a = *this;
        uint128 t = b;

        this->lo = 0ull;
        this->hi = 0ull;

        for (unsigned int i = 0; i < 128; ++i) {
            if (t.lo & 1)
                *this += a << i;

            t >>= 1;
        };

        return *this;
    };


    uint128 uint128::div (const uint128 & ds, uint128 & remainder) const throw () {
        if (!ds)
            return 1u / (unsigned int) ds.lo;

        uint128 dd = *this;

        // only remainder
        if (ds > dd) {
            remainder = *this;
            return 0ull;
        };

        uint128 r = 0ull;
        uint128 q = 0ull;
    //    while (dd >= ds) { dd -= ds; q += 1; }; // extreme slow version

        unsigned int b = 127;
        while (r < ds) {
            r <<= 1;
            if (dd.bit (b--))
                r.lo |= 1;
        };
        ++b;

        while (true)
            if (r < ds) {
                if (!(b--)) break;

                r <<= 1;
                if (dd.bit (b))
                    r.lo |= 1;

            } else {
                r -= ds;
                q.bit (b, true);
            };

        remainder = r;
        return q;
    };

    bool uint128::bit (unsigned int n) const throw () {
        n &= 0x7F;

        if (n < 64)
            return (this->lo & (1ull << n)) ? true : false;

        return (this->hi & (1ull << (n - 64))) ? true : false;
    };

    void uint128::bit (unsigned int n, bool val) throw () {
        n &= 0x7F;

        if (val) {
            if (n < 64) this->lo |= (1ull << n);
                   else this->hi |= (1ull << (n - 64));
        } else {
            if (n < 64) this->lo &= ~(1ull << n);
                   else this->hi &= ~(1ull << (n - 64));
        };
    };


    uint128 & uint128::operator >>= (unsigned int n) throw () {
        n &= 0x7F;

        if (n > 63) {
            n -= 64;
            this->lo = this->hi;
            this->hi = 0ull;
        };

        if (n) {
            // shift low qword
            this->lo >>= n;

            // get lower N bits of high qword
            unsigned __int64 mask = 0ull;
            for (unsigned int i = 0; i < n; ++i)
                mask |= (1ll << i);

            // and add them to low qword
            this->lo |= (this->hi & mask) << (64 - n);

            // and finally shift also high qword
            this->hi >>= n;
        };

        return *this;
    };

    uint128 & uint128::operator <<= (unsigned int n) throw () {
        n &= 0x7F;

        if (n > 63) {
            n -= 64;
            this->hi = this->lo;
            this->lo = 0ull;
        };

        if (n) {
            // shift high qword
            this->hi <<= n;

            // get higher N bits of low qword
            unsigned __int64 mask = 0ull;
            for (unsigned int i = 0; i < n; ++i)
                mask |= (1ll << (63 - i));

            // and add them to high qword
            this->hi |= (this->lo & mask) >> (64 - n);

            // and finally shift also low qword
            this->lo <<= n;
        };

        return *this;
    };

    bool uint128::operator ! () const throw () {
        return !(this->hi || this->lo);
    };

    uint128 & uint128::operator |= (const uint128 & b) throw () {
        this->hi |= b.hi;
        this->lo |= b.lo;

        return *this;
    };

    uint128 & uint128::operator &= (const uint128 & b) throw () {
        this->hi &= b.hi;
        this->lo &= b.lo;

        return *this;
    };

    uint128 & uint128::operator ^= (const uint128 & b) throw () {
        this->hi ^= b.hi;
        this->lo ^= b.lo;

        return *this;
    };

    bool operator <  (const uint128 & a, const uint128 & b) throw () {
        return (a.hi == b.hi) ? (a.lo < b.lo) : (a.hi < b.hi);
    };

    bool operator == (const uint128 & a, const uint128 & b) throw () {
        return a.hi == b.hi && a.lo == b.lo;
    };
    bool operator && (const uint128 & a, const uint128 & b) throw () {
        return (a.hi || a.lo) && (b.hi || b.lo);
    };
    bool operator || (const uint128 & a, const uint128 & b) throw () {
        return (a.hi || a.lo) || (b.hi || b.lo);
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Archive>
    void uint128::serialize(Archive& ar, unsigned int version)
    {
        ar & lo & hi;
    }

    template void uint128::serialize<util::portable_binary_oarchive>(
        util::portable_binary_oarchive& ar, const unsigned int version);
    template void uint128::serialize<util::portable_binary_iarchive>(
        util::portable_binary_iarchive& ar, const unsigned int version);
}}}

#endif
