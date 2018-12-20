package eiffel;

public class MAKE_ARRAY extends rtl.ANY {
	private int[] a;

    public MAKE_ARRAY()
	{
		io.put_string("Make array!");
		self().a = new int[17];
		io.new_line();
		io.put_integer(a.length);
		// Object[] b;
		// b = new Object[13];
		// io.new_line();
		// io.put_integer(b.length);
	}
	
	public MAKE_ARRAY self()
	{
		return this;
	}
	
	public static void main(java.lang.String args[])
	{
		new MAKE_ARRAY();
		// CREATE My_VAr.make
	}
}
