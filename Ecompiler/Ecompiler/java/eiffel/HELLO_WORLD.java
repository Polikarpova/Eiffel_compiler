package eiffel;

/**
 *
 * @author Пользователь
 */
public class HELLO_WORLD extends rtl.ANY {
    public HELLO_WORLD()
	{
		make();
	}

    public void make() // вообще, нужно переименовать метод в `<init>` и совместить с конструктором!
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
