
/* Copyright (C) 1999-2018 by The D Language Foundation, All Rights Reserved
 * All Rights Reserved, written by Walter Bright
 * http://www.digitalmars.com
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 * https://github.com/dlang/dmd/blob/master/src/dmd/root/object.h
 */

#pragma once

#define POSIX (__linux__ || __APPLE__ || __FreeBSD__ || __OpenBSD__ || __DragonFly__ || __sun)

#include "dcompat.h"
#include <stddef.h>

typedef size_t hash_t;

struct OutBuffer;

enum DYNCAST
{
    DYNCAST_OBJECT,
    DYNCAST_EXPRESSION,
    DYNCAST_DSYMBOL,
    DYNCAST_TYPE,
    DYNCAST_IDENTIFIER,
    DYNCAST_TUPLE,
    DYNCAST_PARAMETER,
    DYNCAST_STATEMENT,
    DYNCAST_TEMPLATEPARAMETER
};

/*
 * Root of our class library.
 */
class RootObject
{
public:
    RootObject() { }

    virtual bool equals(RootObject *o);

    /**
     * Return <0, ==0, or >0 if this is less than, equal to, or greater than obj.
     * Useful for sorting Objects.
     */
    virtual int compare(RootObject *obj);

    /**
     * Pretty-print an Object. Useful for debugging the old-fashioned way.
     */
    virtual const char *toChars();
    /// This function is `extern(D)` and should not be called from C++,
    /// as the ABI does not match on some platforms
    virtual DArray<const char> toString();
    virtual void toBuffer(OutBuffer *buf);

    /**
     * Used as a replacement for dynamic_cast. Returns a unique number
     * defined by the library user. For Object, the return value is 0.
     */
    virtual int dyncast() const;
};
