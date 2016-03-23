package org.jocl.blast;
import static org.junit.Assert.assertTrue;

import org.junit.Test;

/**
 * Basic test of the bindings of the CLBlast class
 */
public class JOCLBlastBasicBindingTest
{
    public static void main(String[] args)
    {
        JOCLBlastBasicBindingTest test = new JOCLBlastBasicBindingTest();
        test.testJOCLBlast();
    }

    @Test
    public void testJOCLBlast()
    {
        assertTrue(BasicBindingTest.testBinding(CLBlast.class));
    }


}