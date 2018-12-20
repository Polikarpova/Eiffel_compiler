package rtl;

/**
 *
 * @author Пользователь
 */
public class ANY extends java.lang.Object {
    
    public ANY()
	{
		io = new CONSOLEIO();
	}
	
    public CONSOLEIO io;
    
    public boolean _1_NotE(boolean left) {
        return !left;
    }
}
