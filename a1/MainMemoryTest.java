package arch.sm213.machine.student;

import machine.AbstractMainMemory;
import org.junit.Test;

import static org.junit.Assert.*;

public class MainMemoryTest {
    private MainMemory m;

    @BeforeEach
    public void clearMemory() {
        m = = new MainMemory(128);
    }

    @Test
    public void testSetGet() throws AbstractMainMemory.InvalidAddressException {
    //set
    int address1 = 4;
    int address2 = 16;
    int address3 = 20;
    int address4 = 32;
    m.set(address1, new byte[]{(byte) 0x12, (byte) 0x34, (byte) 0x56, (byte) 0x78});
    m.set(address2, new byte[]{(byte) 0xFF, (byte) 0xFF, (byte) 0xFF, (byte) 0xFF});
    m.set(address3, new byte[]{(byte) 0x88, (byte) 0x88, (byte) 0x56, (byte) 0x78});
    m.set(address4, new byte[]{(byte) 0x00, (byte) 0x34, (byte) 0x56, (byte) 0x0F});
    //get
    byte arr1[] = m.get(4,4);
    byte arr2[] = m.get(16,4);
    byte arr3[] = m.get(20,4);
    byte arr4[] = m.get(32,4);
    assertEquals(arr1[0],(byte)0x12);
    assertEquals(arr2[1],(byte)0xFF);
    assertEquals(arr3[2],(byte)0x56);
    assertEquals(arr4[3],(byte)0x0F);
    }

    @Test
    public void testAlignment() throws AbstractMainMemory.InvalidAddressException {
        assertTrue(m.isAccessAligned(2,2));
        assertTrue(m.isAccessAligned(4,2));
        assertTrue(m.isAccessAligned(4,4));
        assertTrue(m.isAccessAligned(8,8));
        assertFalse(m.isAccessAligned(2,3));
        assertFalse(m.isAccessAligned(5,3));
        assertFalse(m.isAccessAligned(8,3));
        assertFalse(m.isAccessAligned(1,2));
    }

    @Test
    public void testConversion() throws AbstractMainMemory.InvalidAddressException{
        //byte to int
        int num1 = m.bytesToInteger((byte)0x12,(byte)0x34,(byte)0x56,(byte)0x78);
        int num2 = m.bytesToInteger((byte)0xFF,(byte)0x84,(byte)0x00,(byte)0x78);
        int num3 = m.bytesToInteger((byte)0x00,(byte)0x80,(byte)0x56,(byte)0x00);
        int num4 = m.bytesToInteger((byte)0xFF,(byte)0x34,(byte)0x56,(byte)0x78);
        assertEquals(num1, 0x12345678);
        assertEquals(num2, 0xFF840078);
        assertEquals(num3, 0x805600);
        assertNotEquals(num4, 0x12345678);
        //int to byte
        byte arr[] = m.integerToBytes(num2);
        assertEquals((byte)0xFF, arr[0]);
        assertEquals((byte)0x84, arr[1]);
        assertEquals((byte)0x00, arr[2]);
        assertEquals((byte)0x78, arr[3]);
        assertNotEquals((byte)0x7F, arr[0]);
        assertNotEquals((byte)0x08, arr[1]);
        assertNotEquals((byte)0x01, arr[2]);
        assertNotEquals((byte)0x77, arr[3]);
    }

}
