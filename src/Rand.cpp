#include "Rand.hpp"

static constexpr uint64_t DEFAULT_STATE[] = {
    0x94f046e6344f7d3e,
    0xcbfccafb5642219e,
    0xf7a2e0032d38ba63,
    0xbbdbc05d6e9a4639
};

namespace rtx {

Xoshiro256SS::Xoshiro256SS(uint64_t s0, uint64_t s1, uint64_t s2, uint64_t s3)
    : s{ s0, s1, s2, s3 }
{

}

uint64_t Xoshiro256SS::next()
{
    const uint64_t result = rotl(s[1] * 5, 7) * 9;

    const uint64_t t = s[1] << 17;

    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];

    s[2] ^= t;

    s[3] = rotl(s[3], 45);

    return result;
}

void Xoshiro256SS::jump()
{
    static constexpr uint64_t JUMP[] = {
        0x180ec6d33cfd0aba,
        0xd5a61266f0c9392c,
        0xa9582618e03fc9aa,
        0x39abdc4529b1661c
    };

    uint64_t s0 = 0;
    uint64_t s1 = 0;
    uint64_t s2 = 0;
    uint64_t s3 = 0;
    for (unsigned i = 0; i < sizeof JUMP / sizeof *JUMP; i++)
        for (int b = 0; b < 64; b++) {
            if (JUMP[i] & UINT64_C(1) << b) {
                s0 ^= s[0];
                s1 ^= s[1];
                s2 ^= s[2];
                s3 ^= s[3];
            }
            next();
        }

    s[0] = s0;
    s[1] = s1;
    s[2] = s2;
    s[3] = s3;
}

void Xoshiro256SS::long_jump() {
    static constexpr uint64_t LONG_JUMP[] = {
        0x76e15d3efefdcbbf,
        0xc5004e441c522fb3,
        0x77710069854ee241,
        0x39109bb02acbe635
    };

    uint64_t s0 = 0;
    uint64_t s1 = 0;
    uint64_t s2 = 0;
    uint64_t s3 = 0;
    for (unsigned i = 0; i < sizeof LONG_JUMP / sizeof *LONG_JUMP; i++)
        for (int b = 0; b < 64; b++) {
            if (LONG_JUMP[i] & UINT64_C(1) << b) {
                s0 ^= s[0];
                s1 ^= s[1];
                s2 ^= s[2];
                s3 ^= s[3];
            }
            next();
        }

    s[0] = s0;
    s[1] = s1;
    s[2] = s2;
    s[3] = s3;
}

bool Xoshiro256SS::operator==(const Xoshiro256SS& rhs) const
{
    return s[0] == rhs.s[0] &&
           s[1] == rhs.s[1] &&
           s[2] == rhs.s[2] &&
           s[3] == rhs.s[3];
}

bool Xoshiro256SS::operator!=(const Xoshiro256SS& rhs) const
{
    return !(*this == rhs);
}

Rand::Rand()
{
    seed();
}

Rand::Rand(const T t)
{
    seed(t);
}

void Rand::seed()
{
    s[0] = DEFAULT_STATE[0];
    s[1] = DEFAULT_STATE[1];
    s[2] = DEFAULT_STATE[2];
    s[3] = DEFAULT_STATE[3];
}

void Rand::seed(const T t)
{
    s[0] = t;
    s[1] = DEFAULT_STATE[1];
    s[2] = DEFAULT_STATE[2];
    s[3] = DEFAULT_STATE[3];
}

Rand::T Rand::operator()()
{
    return next();
}

void Rand::discard(const unsigned long long z)
{
    for (unsigned long long i = 0; i < z; ++i) {
        (*this)();
    }
}

bool Rand::operator==(const Rand& rhs) const
{
    return static_cast<const Xoshiro256SS&>(*this) == rhs;
}

bool Rand::operator!=(const Rand& rhs) const
{
    return !(*this == rhs);
}

}  // namespace rtx

