package rtl;

/**
 *
 * @author Пользователь
 */
public class ANY extends java.lang.Object {
    
    public ANY()
	{
		io = new CONSOLEIO();
                $helper = new Helper();
	}
	
    public CONSOLEIO io;
    public Helper $helper;
}
