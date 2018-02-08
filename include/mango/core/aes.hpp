/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2018 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#include "configure.hpp"
#include "memory.hpp"

namespace mango
{

    // -----------------------------------------------------------------------
    // AES cryptographic functions
    // -----------------------------------------------------------------------

    // WARNING! The AES block size is 128 bits (16 bytes) and all input
    // and output buffer lengths must be multiple of 16 bytes.
    // These functions will not handle incomplete blocks.
    //
    // The key sizes are:
    // AES128: 16 bytes (128 bits)
    // AES192: 24 bytes (192 bits)
    // AES256: 32 bytes (256 bits)
    //
    // The iv is always 16 bytes (AES block size)
    //
    // ccm_encrypt() requirements:
    // - the mac_length must be 4, 6, 8, 10, 12, 14, or 16
    // - output.size must be input.size + mac_length
    //
    // Hardware acceleration support:
    // ECB: Intel AES-NI
    // CBC: Intel AES-NI
    // CTR: none
    // CCM: none

    class AES
    {
    private:
        struct KeyScheduleAES* m_schedule;
        int m_bits;

    public:
        AES(const u8* key, int bits);
        ~AES();

        void ecb_encrypt(u8* output, const u8* input, size_t length);
        void ecb_decrypt(u8* output, const u8* input, size_t length);

        void cbc_encrypt(u8* output, const u8* input, size_t length, const u8* iv);
        void cbc_decrypt(u8* output, const u8* input, size_t length, const u8* iv);

        void ctr_encrypt(u8* output, const u8* input, size_t length, const u8* iv);
        void ctr_decrypt(u8* output, const u8* input, size_t length, const u8* iv);

        void ccm_encrypt(Memory output, Memory input, Memory associated, Memory nonce, int mac_length);
        void ccm_decrypt(Memory output, Memory input, Memory associated, Memory nonce, int mac_length);
    };

} // namespace mango