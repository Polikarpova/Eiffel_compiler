package eiffel;

/**
 *
 * @author ������������
 */
public class HELLO_WORLD extends rtl.ANY {
    public HELLO_WORLD()
	{
		make();
	}

    public void make() // ������, ����� ������������� ����� � `<init>` � ���������� � �������������!
	{
		io.put_string("Hello world!");
		// System.out.print("Hello world!");
	}
	
	public static void main(java.lang.String args[])
	{
		new HELLO_WORLD();
		// CREATE My_VAr.make
	}
}
