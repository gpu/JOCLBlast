/*
 * JOCLBlast - Java bindings for CLBlast
 *
 * Copyright (c) 2016 Marco Hutter - http://www.jocl.org
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
package org.jocl.blast;

/**
 * Precision scoped enum (values in bits)
 */
public class Precision
{
    public static final int kHalf = 16;
    public static final int kSingle = 32;
    public static final int kDouble = 64;
    public static final int kComplexSingle = 3232;
    public static final int kComplexDouble = 6464;

    /**
     * Private constructor to prevent instantiation
     */
    private Precision()
    {
        // Private constructor to prevent instantiation
    }

    /**
     * Returns a string representation of the given constant
     *
     * @return A string representation of the given constant
     */
    public static String stringFor(int n)
    {
        switch (n)
        {
            case kHalf: return "kHalf";
            case kSingle: return "kSingle";
            case kDouble: return "kDouble";
            case kComplexSingle: return "kComplexSingle";
            case kComplexDouble: return "kComplexDouble";
        }
        return "INVALID Precision: "+n;
    }
}

