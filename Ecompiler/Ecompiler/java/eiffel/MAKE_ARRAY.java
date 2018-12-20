package eiffel;

public class MAKE_ARRAY extends rtl.ANY {
	private int[] a;

    public MAKE_ARRAY()
	{
		io.put_string("Make array!");
		self().a = new int[17];
		io.new_line();
		io.put_integer(a.length);
		String[] b;
		b = new String[13];
		b[4] = "my String";
		io.new_line();
		io.put_integer(b.length);
		io.new_line();
		io.put_string(b[4]);
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
