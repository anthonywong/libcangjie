/*
 * Copyright (C) 2012  Wan Leung Wong <me at wanleung dot com>
 *
 * This file is part of libcangjie.
 *
 * libcangjie is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libcangjie is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libcangjie.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <vector>
#include <db_cxx.h>
#include "chchar.h"

#define CANGJIE_SIMPLIFIED    0x00000001
#define CANGJIE_TRADITIONAL   0x00000002
#define CANGJIE_COMMON        0x00000003 // < tick SIMPLIFIED + TRADITIONAL = COMMON
#define CANGJIE_CJK           0x00000004 // < for tick only 
#define CANGJIE_ALL_CJK       0x00000007 // COMMON + CANGJIE_CJK  = CANGJIE_ALL_CJK

typedef enum {
    CangJie_Version_Type_3 = 1,
    CangJie_Version_Type_5,
} CangJie_Version_Type;

class CangJie {
    public:
        CangJie (CangJie_Version_Type version, uint32_t flags);
        ~CangJie() { close(); }
        std::vector<ChChar> getCharacters (std::string code);
        bool isCangJieInputKey (char c);
        std::string getFullWidthChar(char key);
        std::string translateInputKeyToCangJie(char key);

    private:
        DbEnv *cangjie_env_;
        Db* cangjie_db_;
        Db* wordfreq_;
        Db* classicfreq_;
        Db* tc_db_;
        Db* sc_db_;
        CangJie_Version_Type cangjie_version_;
        uint32_t cangjie_flags_;
        std::vector<ChChar> getCharactersRange (std::string begin, std::string ending);
        //std::vector<ChChar> sortbyfreq (std::vector<ChChar> result);
        void assign_freq(std::vector<ChChar> &result);

        uint32_t getType(std::string chr);

        CangJie() : cangjie_env_(0) {}
        void close();
};
