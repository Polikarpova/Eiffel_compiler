package Rtl;

/**
 *
 * @author Пользователь
 */
public class CONSOLEIO {


	// writing to stdout
    public void put_string( String v ) {
        System.out.print(v);
    }
    public void put_integer( int v) {
        System.out.print(v);
    }
    public void put_real( double v) {
        System.out.print(v);
    }
    public void put_boolean( boolean v) {
        System.out.print(v ? "True" : "False");
    }
    public void new_line() {
        System.out.println();
    }
}
