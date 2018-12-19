package eiffel;

public class MAKE_ARRAY extends rtl.ANY {
    public MAKE_ARRAY()
	{
		io.put_string("Make array!");
		int[] a;
		a = new int[17];
		io.new_line();
		io.put_integer(a.length);
	}
	
	public static void main(java.lang.String args[])
	{
		new MAKE_ARRAY();
		// CREATE My_VAr.make
	}
}
