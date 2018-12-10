package eiffel;

/**
 *
 * @author Пользователь
 */
public class HELLO_WORLD extends rtl.ANY {
    public HELLO_WORLD()
	{
		
	}

    public void make()
	{
		io.put_string("Hello world!");
		// System.out.print("Hello world!");
	}
	
	public static void main(java.lang.String args[])
	{
		(new HELLO_WORLD()).make();
		// CREATE My_VAr.make
	}
}
