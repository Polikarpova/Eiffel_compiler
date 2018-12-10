package eiffel;

/**
 *
 * @author Пользователь
 */
public class HELLO_WORLD {
    public HELLO_WORLD()
	{
		
	}

    public void make()
	{
		rtl.Io.put_string("Hello world!");
		// System.out.print("Hello world!");
	}
	
	public static void main(java.lang.String args[])
	{
		(new HELLO_WORLD()).make();
		// CREATE My_VAr.make
	}
}
